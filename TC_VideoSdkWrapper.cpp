#include "TC_VideoSdkWrapper.h"
#include "TC_Methods.h"
#include "TC_Events.h"

#include <QDebug>
#include <QNetworkReply>
#include <QNetworkProxy>
#include <QAuthenticator>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

#include <chrono>

const QString TC_VideoSdkWrapper::_absentPin = "";
const QString TC_VideoSdkWrapper::_absentTwinName = "";
const QString TC_VideoSdkWrapper::_defaultIp = "127.0.0.1"; // assume applications running on the same machine
const TC_VideoSdkWrapper::PortType TC_VideoSdkWrapper::_defaultApachePort = 80;

// common API fields
const QString TC_VideoSdkWrapper::_methodFieldName = QStringLiteral("method");
const QString TC_VideoSdkWrapper::_methodFieldEventValue = QStringLiteral("event");
const QString TC_VideoSdkWrapper::_eventFieldName = QStringLiteral("event");
const QString TC_VideoSdkWrapper::_resultFieldName = QStringLiteral("result");
const QString TC_VideoSdkWrapper::_errorFieldName = QStringLiteral("error");

// Some of the values are taken from the specification (according to https://docs.trueconf.com/videosdk/).
// Other - have reasons, described below.
namespace
{
    using namespace std::chrono_literals;

    // config.json things
    const auto _configFileName = QStringLiteral("config.json");
    const auto _configObjectName = QStringLiteral("config");
    const auto _websocketObjectName = QStringLiteral("websocket");
    const auto _httpObjectName = QStringLiteral("http");
    const auto _portValue = QStringLiteral("port");
    const auto _gettingConfigUrl = "http://%1:%2/public/%3/" + _configFileName;

    // websocket things
    const auto _webSocketUrl = QStringLiteral("ws://%1:%2");

    // timeouts
    constexpr auto _gettingConfigAttemptInterval = 10s; // value taken experimentally and seems ok. Feel free to change it according to your needs
    constexpr auto _connectingToWebsocketsAttemptInterval = 10s; // value taken experimentally and seems ok. Feel free to change it according to your needs
    constexpr auto _authorizingAttemptInterval = 10s; // value taken experimentally and seems ok. Feel free to change it according to your needs

    // API fields for authorization (https://docs.trueconf.com/videosdk/commands/auth)
    const auto _authMethodValue = QStringLiteral("auth");
    const auto _authTypeFieldName = QStringLiteral("type");
    const auto _authTypeSecuredValue = QStringLiteral("secured");
    const auto _authTypeUnsecuredValue = QStringLiteral("unsecured");
    const auto _authCredendtialsFieldName = QStringLiteral("credentials");
}


TC_VideoSdkWrapper::TC_VideoSdkWrapper(QObject* parent)
    : QObject(parent)
    , m_methods(std::make_shared<TC_Methods>(this))
    , m_events(std::make_shared<TC_Events>(this))
{
    connect(&m_networkAccessManager, &QNetworkAccessManager::authenticationRequired, this, [this](QNetworkReply* /* reply */, QAuthenticator* /* authenticator */){
        onConfigDownloadFailed("authenticationRequired");
    });
    connect(&m_networkAccessManager, &QNetworkAccessManager::encrypted, this, [this](QNetworkReply* /* reply */){
        onConfigDownloadFailed("encrypted");
    });
    connect(&m_networkAccessManager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, [this](QNetworkReply* /* reply */, QSslPreSharedKeyAuthenticator* /* authenticator */){
        onConfigDownloadFailed("preSharedKeyAuthenticationRequired");
    });
    connect(&m_networkAccessManager, &QNetworkAccessManager::proxyAuthenticationRequired, this, [this](const QNetworkProxy& /* proxy */, QAuthenticator* /* authenticator */){
        onConfigDownloadFailed("proxyAuthenticationRequired");
    });
    connect(&m_networkAccessManager, &QNetworkAccessManager::sslErrors, this, [this](QNetworkReply* /* reply */, const QList<QSslError>& errors){
        QString errorsStr;
        for (const auto& error : errors)
        {
            if (!errorsStr.isEmpty())
            {
                errorsStr.append(", ");
            }
            errorsStr.append(error.errorString());
        }
        onConfigDownloadFailed(QString("sslErrors: %1").arg(errorsStr));
    });
    connect(&m_networkAccessManager, &QNetworkAccessManager::finished, this, &TC_VideoSdkWrapper::onConfigDownloadFinished);

    connect(&m_webSocket, &QWebSocket::connected, this, &TC_VideoSdkWrapper::onWebSocketConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &TC_VideoSdkWrapper::onWebSocketDisconnected);
    connect(&m_webSocket, qOverload<QAbstractSocket::SocketError>(&QWebSocket::error), this, [this](QAbstractSocket::SocketError error){
        onConnectingToWebSocketFailed(QString("QAbstractSocket::SocketError - %1)").arg(QString::number(error)));
    });
    connect(&m_webSocket, &QWebSocket::preSharedKeyAuthenticationRequired, this, [this](QSslPreSharedKeyAuthenticator* /* authenticator */){
        onConnectingToWebSocketFailed("preSharedKeyAuthenticationRequired");
    });
    connect(&m_webSocket, &QWebSocket::proxyAuthenticationRequired, this, [this](const QNetworkProxy& /* proxy */, QAuthenticator* /* authenticator */){
        onConnectingToWebSocketFailed("proxyAuthenticationRequired");
    });
    connect(&m_webSocket, &QWebSocket::sslErrors, this, [this](const QList<QSslError>& errors){
        QString errorsStr;
        for (const auto& error : errors)
        {
            if (!errorsStr.isEmpty())
            {
                errorsStr.append(", ");
            }
            errorsStr.append(error.errorString());
        }
        onConnectingToWebSocketFailed(QString("sslErrors: %1").arg(errorsStr));
    });
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &TC_VideoSdkWrapper::onWebSocketMessageReceived);
}

TC_VideoSdkWrapper::~TC_VideoSdkWrapper()
{
    m_timer.stop();
    m_timer.disconnect();
    m_webSocket.disconnect();
    m_networkAccessManager.disconnect();
}

std::shared_ptr<TC_Methods> TC_VideoSdkWrapper::methods()
{
    return m_methods;
}

std::shared_ptr<TC_Events> TC_VideoSdkWrapper::events()
{
    return m_events;
}

bool TC_VideoSdkWrapper::parseConfig(const QString& json, PortType& outWebsocketsPort, PortType& outHttpPort, QString& outErrStr) const
{
    // Example of the _configFileName (according to https://docs.trueconf.com/videosdk/)
    // {
    //     "config": {
    //         "websocket": {
    //             "hostname": null,
    //             "port": 8765
    //         },
    //          "http": {
    //             "hostname": null,
    //             "port": 8766
    //         }
    // }

    const QJsonDocument doc = QJsonDocument::fromJson(json.toUtf8());
    if (doc.isNull() || !doc.isObject())
    {
        outErrStr = "Invalid JSON format";
        return false;
    }

    const QJsonObject rootObj = doc.object();
    QJsonObject configObj = rootObj.value(_configObjectName).toObject();
    if (configObj.isEmpty())
    {
        outErrStr = QString("No '%1' object in JSON").arg(_configObjectName);
        return false;
    }

    const auto parsePort = [&outErrStr](const QJsonObject& obj, const QString& key) -> PortType {
        if (!obj.contains(key) || !obj[key].isObject())
        {
            outErrStr = QString("Missing or invalid '%1' object").arg(key);
            return 0;
        }
        const QJsonObject subObj = obj[key].toObject();
        if (!subObj.contains(_portValue) || !subObj[_portValue].isDouble()) {
            outErrStr = QString("Missing or invalid 'port' in '%1'").arg(key);
            return 0;
        }
        return static_cast<PortType>(subObj[_portValue].toInt());
    };

    outWebsocketsPort = parsePort(configObj, _websocketObjectName);
    if (!outErrStr.isEmpty())
    {
        return false;
    }

    outHttpPort = parsePort(configObj, _httpObjectName);
    if (!outErrStr.isEmpty())
    {
        return false;
    }

    return true;
}

QString TC_VideoSdkWrapper::generateConfigFileUrl(const QString& ip, const PortType port, const QString& twinName) const
{
    return _gettingConfigUrl.arg(ip, QString::number(port), _absentTwinName == twinName ? "default" : twinName);
}

QString TC_VideoSdkWrapper::stateToString(const State state) const
{
    switch (state)
    {
        case State::None: return "State::None";
        case State::GettingConfig: return "State::GettingConfig";
        case State::ConnectingToWebSockets: return "State::ConnectingToWebSockets";
        case State::Authorizing: return "State::Authorizing";
        case State::ConnectedAndAuthorized: return "State::ConnectedAndAuthorized";
        default:
        {
            Q_ASSERT_X(false, __FUNCTION__, "unsupported state");
            qWarning() << "Trying to start when State in not None";
            return "State::None";
        }
    }
}

void TC_VideoSdkWrapper::setNewState(const State newState)
{
    if (m_currentState == newState)
    {
            return;
    }

    qInfo() << QString("TC_VideoSdkWrapper::setNewState: new state is set - %1").arg(stateToString(newState));
    m_currentState = newState;
    Q_EMIT currentStateChanged(m_currentState);
}

void TC_VideoSdkWrapper::start(const QString& ip, const PortType apachePort, const QString& pin, const QString& twinName)
{
    QMutexLocker lock(&m_currentStateMutex);

    qInfo() << QString("TC_VideoSdkWrapper::start: ip - %1, apachePort - %2, pin - %3, twinName - %4").arg(ip, QString::number(apachePort), pin, twinName);

    if (State::None != m_currentState)
    {
        qWarning() << "TC_VideoSdkWrapper::start: trying to start when State in not None";
        return;
    }

    m_ip = ip;
    m_apachePort = apachePort;
    m_pin = pin;
    m_twinName = twinName;

    goToGettingConfigState();
}

void TC_VideoSdkWrapper::goToGettingConfigState()
{
    qInfo() << QString("TC_VideoSdkWrapper::goToGettingConfigState: trying to get %1 file").arg(_configFileName);

    m_timer.stop();
    m_timer.disconnect();
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TC_VideoSdkWrapper::makeGettingConfigRequest);

    setNewState(State::GettingConfig);

    makeGettingConfigRequest();
}

void TC_VideoSdkWrapper::makeGettingConfigRequest()
{
    const QUrl requestUrl(generateConfigFileUrl(m_ip, m_apachePort, m_twinName));
    qInfo() << QString("TC_VideoSdkWrapper::makeGettingConfigRequest: making requst for %1 to %2").arg(_configFileName, requestUrl.toString());
    m_networkAccessManager.get(QNetworkRequest(requestUrl));
}

void TC_VideoSdkWrapper::onConfigDownloadFailed(const QString& errorStr)
{
    QMutexLocker lock(&m_currentStateMutex);

    QString infoStr = QString("TC_VideoSdkWrapper::onConfigDownloadFailed: error - %1").arg(errorStr);

    if (State::GettingConfig != m_currentState)
    {
        qWarning() << infoStr.append(". Current state is not GettingConfig, but %1, so we will not make futher %2 requests").arg(stateToString(m_currentState), _configFileName);
        return;
    }

    qInfo() << infoStr.append(". Current state is GettingConfig, so we will retry getting %1 after %2sec").arg(_configFileName, QString::number(std::chrono::seconds(_gettingConfigAttemptInterval).count()));

    m_timer.start(_gettingConfigAttemptInterval);
}

void TC_VideoSdkWrapper::onGettingConfigAttemptTimeout()
{
    QMutexLocker lock(&m_currentStateMutex);

    if (State::GettingConfig != m_currentState)
    {
        qWarning() << QString("TC_VideoSdkWrapper::onGettingConfigAttemptTimeout: current state is not GettingConfig, but %1, so we will not execute futher logic").arg(stateToString(m_currentState));
        return;
    }

    qInfo() << QString("TC_VideoSdkWrapper::onGettingConfigAttemptTimeout: timeout reached, making new request for %1").arg(_configFileName);

    makeGettingConfigRequest();
}

void TC_VideoSdkWrapper::onConfigDownloadFinished(QNetworkReply* reply)
{
    QMutexLocker lock(&m_currentStateMutex);

    reply->deleteLater();

    if (QNetworkReply::NoError != reply->error())
    {
        onConfigDownloadFailed(reply->errorString());
        return;
    }

    Q_ASSERT_X(State::GettingConfig == m_currentState, __FUNCTION__, "function called with state, not designed to be used here");
    QString parsingConfigErrStr;
    const auto receivedReplyStr = reply->readAll();
    QString infoStr = QString("TC_VideoSdkWrapper::onConfigDownloadFinished: received reply - %1").arg(receivedReplyStr.constData());

    if (!parseConfig(receivedReplyStr, m_wsPort, m_httpPort, parsingConfigErrStr))
    {
        qInfo() << infoStr.append(", couldn't parse %1, error - %2").arg(_configFileName, parsingConfigErrStr);
        lock.unlock();
        onConfigDownloadFailed(parsingConfigErrStr);
        return;
    }
    qInfo() << infoStr.append(QString(", %1 successfully parsed: wsPort - %2, httpPort - %3").arg(_configFileName, QString::number(m_wsPort), QString::number(m_httpPort)));

    lock.unlock();
    goToConnectingToWebSocketsState();
}

void TC_VideoSdkWrapper::goToConnectingToWebSocketsState()
{
    qInfo() << QString("TC_VideoSdkWrapper::goToConnectingToWebSocketsState: we will try to connect to websockets");

    m_timer.stop();
    m_timer.disconnect();
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TC_VideoSdkWrapper::tryConnectToWebsocket);

    setNewState(State::ConnectingToWebSockets);

    tryConnectToWebsocket();
}

void TC_VideoSdkWrapper::onWebSocketConnected()
{
    QMutexLocker lock(&m_currentStateMutex);

    Q_ASSERT_X(State::ConnectingToWebSockets == m_currentState, __FUNCTION__, "function called with state, not designed to be used here");

    qInfo() << "TC_VideoSdkWrapper::onWebSocketConnected: successfully connected to websockets, now we need to authorize";

    lock.unlock();

    goToAuthorizingState();
}

void TC_VideoSdkWrapper::onWebSocketDisconnected()
{
    QMutexLocker lock(&m_currentStateMutex);

    QString infoStr = QString("TC_VideoSdkWrapper::onWebSocketDisconnected: websocket disconnected");

    if (m_currentState < State::ConnectingToWebSockets)
    {
        qWarning() << infoStr.append(". Current state is less than ConnectingToWebSockets (is %1), so we will not make futher websocket requests").arg(stateToString(m_currentState));
        return;
    }

    qInfo() << infoStr.append(". Current state is ConnectingToWebSockets or greater, so we will retry websocket opening");

    lock.unlock();
    goToConnectingToWebSocketsState();
}

void TC_VideoSdkWrapper::onConnectingToWebSocketFailed(const QString& errorStr)
{
    QMutexLocker lock(&m_currentStateMutex);

    QString infoStr = QString("TC_VideoSdkWrapper::onConnectingToWebSocketFailed: error - %1").arg(errorStr);

    if (State::ConnectingToWebSockets != m_currentState)
    {
        qWarning() << infoStr.append(". Current state is not ConnectingToWebSockets, but %1, so we will not make futher websocket opening requests").arg(stateToString(m_currentState));
        return;
    }

    qInfo() << infoStr.append(QString(". Current state is ConnectingToWebSockets, so we will retry websocket opening after %1sec").arg(QString::number(std::chrono::seconds(_connectingToWebsocketsAttemptInterval).count())));

    m_timer.start(_connectingToWebsocketsAttemptInterval);
}

void TC_VideoSdkWrapper::onWebSocketMessageReceived(const QString& message)
{
    Q_EMIT textMessageReceived(message);

    QString infoStr = QString("TC_VideoSdkWrapper::onWebSocketMessageReceived: received message - %1").arg((message));
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());
    if (doc.isNull() || !doc.isObject()) {
        infoStr.append(". But we couldn't parse this JSON");
        qWarning() << infoStr;
        return;
    }

    QJsonObject jsonObj = doc.object();

    if (!jsonObj.contains(_methodFieldName) || !jsonObj.value(_methodFieldName).isString())
    {
        infoStr.append(QString(". But '%1' field is missing or not a string").arg(_methodFieldName));
        qWarning() << infoStr;
        return;
    }

    const QString methodValue = jsonObj.value(_methodFieldName).toString();
    if (_methodFieldEventValue == methodValue)
    {
        if (!jsonObj.contains(methodValue) || !jsonObj.value(methodValue).isString())
        {
            infoStr.append(QString(". This message - event, but '%1' parameter is not persent or not string type, so we will not continue futher processing").arg(_methodFieldEventValue));
            qWarning() << infoStr;
            return;
        }

        infoStr.append(". This message - event and will be processed as notification");
        qInfo() << infoStr;

        processNotification(jsonObj.value(_eventFieldName).toString(), jsonObj);
    }
    else
    {
        infoStr.append(". This message - command answer and will be processed as reply to some command request");
        qInfo() << infoStr;
        processCommandAnswer(methodValue, jsonObj);
    }
}

void TC_VideoSdkWrapper::tryConnectToWebsocket()
{
    const QUrl requestUrl(_webSocketUrl.arg(m_ip, QString::number(m_wsPort)));
    qInfo() << QString("TC_VideoSdkWrapper::tryConnectToWebsocket: making requst for websocket opening to %1").arg(requestUrl.toString());
    m_webSocket.open(requestUrl);
}

void TC_VideoSdkWrapper::goToAuthorizingState()
{
    QString infoStr("TC_VideoSdkWrapper::goToAuthorizingState: we will try to authorize now for having ability to use API");
    if (m_pin.isEmpty())
    {
        infoStr.append(". Unsecured type will be used");
    }
    else
    {
        infoStr.append(QString(". Secured type will be used (with pin %1)").arg(m_pin));
    }

    qInfo() << infoStr;

    m_timer.stop();
    m_timer.disconnect();
    m_timer.setSingleShot(true);
    connect(&m_timer, &QTimer::timeout, this, &TC_VideoSdkWrapper::makeAuthorizingRequest);

    setNewState(State::Authorizing);

    makeAuthorizingRequest();
}

void TC_VideoSdkWrapper::onAuthorizationSuccess()
{
    qInfo() << "TC_VideoSdkWrapper::onAuthorizationSuccess: we successfully authorized";
    goToConnectedAndAuthorized();
}

void TC_VideoSdkWrapper::onAuthorizationFailure(const QString& errorStr)
{
    QMutexLocker lock(&m_currentStateMutex);

    QString infoStr = QString("TC_VideoSdkWrapper::onAuthorizationFailure: error - %1").arg(errorStr);

    if (State::Authorizing != m_currentState)
    {
        qWarning() << infoStr.append(". Current state is not Authorizing, but %1, so we will not make futher authorizing requests").arg(stateToString(m_currentState));
        return;
    }

    qInfo() << infoStr.append(QString(". Current state is Authorizing, so we will retry authorize after %1sec").arg(QString::number(std::chrono::seconds(_authorizingAttemptInterval).count())));

    m_timer.start(_authorizingAttemptInterval);
}

void TC_VideoSdkWrapper::makeAuthorizingRequest()
{
    QString infoStr("TC_VideoSdkWrapper::makeAuthorizingRequest: making authorization request");
    QVariantMap authRequestParams;
    authRequestParams[_methodFieldName] = _authMethodValue;
    if (m_pin.isEmpty())
    {
        authRequestParams[_authTypeFieldName] = _authTypeUnsecuredValue;
        infoStr.append(QString(" with '%1' type").arg(_authTypeUnsecuredValue));
    }
    else
    {
        authRequestParams[_authTypeFieldName] = _authTypeSecuredValue;
        authRequestParams[_authCredendtialsFieldName] = m_pin;

        infoStr.append(QString(" with '%1' type, '%2' is '%3'").arg(_authTypeSecuredValue, _authCredendtialsFieldName, m_pin));
    }

    qInfo() << infoStr;
    send(authRequestParams);
}

void TC_VideoSdkWrapper::send(const QString& textMessage)
{
    m_webSocket.sendTextMessage(textMessage);
}

void TC_VideoSdkWrapper::send(const QVariantMap& dataInVariantMap)
{
    send(QString(QJsonDocument(QJsonObject::fromVariantMap(dataInVariantMap)).toJson(QJsonDocument::Compact)));
}

void TC_VideoSdkWrapper::processNotification(const QString& eventName, const QJsonObject& eventJson)
{
    qInfo() << QString("TC_VideoSdkWrapper::processNotification: %1").arg(eventName);
    Q_EMIT notificationReceived(eventName, eventJson);
}

void TC_VideoSdkWrapper::processCommandAnswer(const QString& commandName, const QJsonObject& commandAnswerJson)
{
    QString infoStr = QString("TC_VideoSdkWrapper::processCommandAnswer: %1").arg(commandName);

    Q_EMIT commandAnswerReceived(commandName, commandAnswerJson);

    if (!commandAnswerJson.contains(_resultFieldName) || !commandAnswerJson.value(_resultFieldName).isBool())
    {
        infoStr.append(QString(". But '%1' field is missing or not a bool, so we will do nothing").arg(_resultFieldName));
        qWarning() << infoStr;
        return;
    }

    if (_authMethodValue != commandName)
    {
        infoStr.append(QString(". This is not reply for '%1' command, so we will do nothing").arg(_authMethodValue));
        qInfo() << infoStr;
        return;
    }

    if (State::Authorizing != m_currentState)
    {
        infoStr.append(QString(". This is a reply for '%1' command and current state is not Authorizing, but %2, so we will do nothing").arg(_authMethodValue, stateToString(m_currentState)));
        qInfo() << infoStr;
        return;
    }

    qInfo() << infoStr;

    if (commandAnswerJson.value(_resultFieldName).toBool())
    {
        onAuthorizationSuccess();
    }
    else
    {
        QString errorStr;
        if (!commandAnswerJson.contains(_errorFieldName) || !commandAnswerJson.value(_errorFieldName).isString())
        {
            errorStr = "couldn't get error reason";
        }
        else
        {
            errorStr = commandAnswerJson.value(_errorFieldName).toString();
        }
        onAuthorizationFailure(errorStr);
    }
}

void TC_VideoSdkWrapper::goToConnectedAndAuthorized()
{
    qInfo() << "TC_VideoSdkWrapper::goToConnectedAndAuthorized: now we have ability to use complete API";

    m_timer.stop();
    m_timer.disconnect();

    setNewState(State::ConnectedAndAuthorized);
}

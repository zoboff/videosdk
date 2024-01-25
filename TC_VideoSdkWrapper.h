#ifndef TC_VIDEO_SDK_WRAPPER_H
#define TC_VIDEO_SDK_WRAPPER_H

#include <QObject>
#include <QMutex>
#include <QNetworkAccessManager>
#include <QTimer>
#include <QWebSocket>

class TC_Methods;
class TC_Events;


class TC_VideoSdkWrapper : public QObject
{
    Q_OBJECT

public:
    explicit TC_VideoSdkWrapper(QObject* parent = nullptr);
    TC_VideoSdkWrapper(const TC_VideoSdkWrapper& other) = delete;
    TC_VideoSdkWrapper& operator=(const TC_VideoSdkWrapper& other) = delete;
    TC_VideoSdkWrapper(TC_VideoSdkWrapper&& other) = delete;
    TC_VideoSdkWrapper& operator=(TC_VideoSdkWrapper&& other) = delete;
    virtual ~TC_VideoSdkWrapper() override;

    using PortType = uint16_t;

    enum class State
    {
        None = 0,
        GettingConfig,
        ConnectingToWebSockets,
        Authorizing,
        ConnectedAndAuthorized
    };

    static const QString _absentPin;
    static const QString _absentTwinName;
    static const QString _defaultIp;
    static const PortType _defaultApachePort;

    // common API fields
    static const QString _methodFieldName;
    static const QString _methodFieldEventValue;
    static const QString _eventFieldName;
    static const QString _resultFieldName;
    static const QString _errorFieldName;

    std::shared_ptr<TC_Methods> methods();
    std::shared_ptr<TC_Events> events();

    void start(const QString& ip, const PortType apachePort = _defaultApachePort, const QString& pin = _absentPin, const QString& twinName = _absentTwinName);
    void send(const QString& textMessage);
    void send(const QVariantMap& dataInVariantMap);

    Q_SIGNAL void currentStateChanged(State state);
    Q_SIGNAL void textMessageReceived(const QString& message);
    Q_SIGNAL void notificationReceived(const QString& eventName, const QJsonObject& eventJson);
    Q_SIGNAL void commandAnswerReceived(const QString& commandName, const QJsonObject& commandAnswerJson);

protected:
    std::shared_ptr<TC_Methods> m_methods;
    std::shared_ptr<TC_Events> m_events;
    State m_currentState{ State::None };
    QMutex m_currentStateMutex;
    QString m_ip;
    QString m_pin;
    QString m_twinName;
    PortType m_apachePort;
    PortType m_wsPort;
    PortType m_httpPort;
    QNetworkAccessManager m_networkAccessManager;
    QTimer m_timer;
    QWebSocket m_webSocket;

    void setNewState(const State newState);
    QString stateToString(const State state) const;
    QString generateConfigFileUrl(const QString& ip, const PortType port, const QString& twinName) const;
    bool parseConfig(const QString& json, PortType& outWebsocketsPort, PortType& outHttpPort, QString& outErrStr) const;
    void processNotification(const QString& eventName, const QJsonObject& eventJson);
    void processCommandAnswer(const QString& commandName, const QJsonObject& commandAnswerJson);

    // State::GettingConfig things
    void goToGettingConfigState();
    Q_SLOT void onConfigDownloadFinished(QNetworkReply* reply);
    void onConfigDownloadFailed(const QString& errorStr);
    void onGettingConfigAttemptTimeout();
    void makeGettingConfigRequest();

    // State::ConnectingToWebSockets
    void goToConnectingToWebSocketsState();
    void onWebSocketConnected();
    void onWebSocketDisconnected();
    void onConnectingToWebSocketFailed(const QString& errorStr);
    void onWebSocketMessageReceived(const QString& message);
    void tryConnectToWebsocket();

    // State::Authorizing
    void goToAuthorizingState();
    void onAuthorizationSuccess();
    void onAuthorizationFailure(const QString& errorStr);
    void makeAuthorizingRequest();

    // State::ConnectedAndAuthorized
    void goToConnectedAndAuthorized();
};

#endif /* TC_VIDEO_SDK_WRAPPER_H */

#include "videosdk.h"
#include <QRandomGenerator>
#include <QNetworkReply>

VideoSDK::VideoSDK(QObject *parent): QObject(parent)
{
    m_methods = new CMethods(this);
    m_events = new CEvents(this);
    /* Create & init the QWebSocket */
    QString name = "VideoSDK to API websocket " + QString::number(QRandomGenerator::global()->generate());
    m_socket = new QWebSocket(name, QWebSocketProtocol::VersionLatest, this);
    m_socket->setObjectName(name);

    QObject::connect(m_socket, SIGNAL(connected()), this, SLOT(onSocketConnected()));
    QObject::connect(m_socket, SIGNAL(disconnected()), this, SLOT(onSocketDisconnected()));
    QObject::connect(m_socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onSocketError(QAbstractSocket::SocketError)));
    QObject::connect(m_socket, SIGNAL(destroyed(QObject*)), this, SLOT(onSocketDestroyed(QObject*)));
    QObject::connect(m_socket, SIGNAL(textMessageReceived(QString)), this, SLOT(onSocketReceived(QString)));

    /* Queue processing timer  */
    QObject::connect(&m_timer, SIGNAL(timeout()), this, SLOT(queue_processing()));

    connect(&m_networkAccessMgr, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(onFileDownloaded(QNetworkReply*)));
}

VideoSDK::~VideoSDK()
{
    close_session();
    delete m_events;
    delete m_methods;
}

void VideoSDK::open_session(const QString &host, const int port, const QString &pin)
{
    m_host = host;
    m_port = port;
    m_pin = pin; //needed later for auth

    if(pin.isNull() && started()) {
        auth();
    }
    else {

        setCurrentState(State::connect);

        QUrl urlOfConfigJsonFile { QStringLiteral("http://%1:%2/public/default/config.json").arg(m_host).arg(m_port) };
        qDebug() << "Trying to get config file...";

        QNetworkRequest request(urlOfConfigJsonFile);
        m_networkAccessMgr.get(request);
    }
}

void VideoSDK::close_session()
{
    qDebug() << "Closing session...";
    m_socket->close();
    clear_queue();
}

void VideoSDK::openWebsocketSession(const QString &host, const int port)
{
    assert((port > -1) && (port < 10000)); //precondition

    QUrl url = QUrl(QString("ws://%1:%2").arg(host).arg(port));
    qDebug() << "\nTrying connect websocket url:" << url.toString() << "...";
    m_socket->open(url);

    /* Start a send texts processing */
    m_timer.start(QUEUE_INTERVAL);

    /* Wait for ... */
    WaitSessionThread* wait_thread = new WaitSessionThread(this);
    wait_thread->start();
    wait_thread->wait(WAIT_FOR_SESSION);
}

CMethods *VideoSDK::Methods()
{
    return m_methods;
}

CEvents *VideoSDK::Events()
{
    return m_events;
}

/* Connect to TrueConf Server

Parameters
----------
    server: str
        Server address. For example, IP address;
    port: int
        Port. Default port is 4307.
*/
void VideoSDK::connectToServer(const QString &server, const int port)
{
    /* {"method": "connectToServer", "server": server, "port": port} */
    QString command = "{\"method\": \"connectToServer\", \"server\": \"" + server + "\", \"port\": " + QString::number(port) + "}";
    API_send(command);
}

/*
 * Connect to TrueConf Online service
*/
void VideoSDK::connectToService()
{
    /* command = {"method": "connectToService"} */
    QString command = "{\"method\": \"connectToService\"}";
    API_send(command);
}

/*
 * Login user to TrueConf Server
*/
void VideoSDK::login(const QString &callId, const QString &password)
{
    /* command = {"method": "login", "login": callId, "password": password, "encryptPassword": true} */
    QString command = "{\"method\": \"login\", \"login\": \"" + callId + "\", \"password\": \"" + password+ "\", \"encryptPassword\": true}";
    API_send(command);
}

/*
 * Logout current user
*/
void VideoSDK::logout()
{
    /* command = {"method": "logout"} */
    QString command = "{\"method\": \"logout\"}";
    API_send(command);
}

/*
 * Make a call
*/
void VideoSDK::call(const QString &peerId)
{
    if(!started()) {
        open_session(m_host, m_port, m_pin);
    }
    /* command = {"method": "call", "peerId": peerId} */
    QString command = "{\"method\": \"call\", \"peerId\": \"" + peerId +"\"}";
    API_send(command);
}

/*
 * Reject an incoming call or invitation to the conference \
*/
void VideoSDK::reject()
{
    QString command = R"({"method": "accept"})";
    API_send(command);
}

/*
 * Accept an incoming call or invitation to the conference
*/
void VideoSDK::accept()
{
    QString command = R"({"method": "accept"})";
    API_send(command);
}

/*
 * End a call or a conference
*/
void VideoSDK::hangUp(const bool forAll)
{
    QString command;

    if(forAll)
        command = R"({"method": "hangUp", "forAll": true})";
    else
        command = R"({"method": "hangUp", "forAll": false})";

    API_send(command);
}

/*
 * Move a participant's video to an any other display.
 * Available in the conference only.
*/
void VideoSDK::moveVideoSlotToMonitor(const QString &callId, int monitorIndex)
{
    /* command = {"method": "moveVideoSlotToMonitor", "callId": callId, "monitorIndex": monitorIndex} */
    QString command = "{\"method\": \"moveVideoSlotToMonitor\", \"callId\": \"" + callId + "\", \"monitorIndex\": \"" + QString::number(monitorIndex) + "\"}";
    API_send(command);
}

/*
 * Send a text command to a remote client (application)
*/
void VideoSDK::sendCommand(QString &peerId, QString &cmd)
{
    /* {"method": "sendCommand", "peerId": peerId, "command": command} */
    QString command = "\{\"method\": \"sendCommand\", \"peerId\": \"" + peerId + "\", \"command\": \"" + cmd + "\"}";
    API_send(command);
}

/*
 * Set a new position to the active PTS camera
*/
void VideoSDK::setPanPos(int pos)
{
    /* {"method": "setPanPos", "pos": pos} */
    QString command = "{\"method\": \"setPanPos\", \"pos\":" + QString::number(pos) + "}";
    API_send(command);
}

/*
 * Set a new position to the active PTS camera
*/
void VideoSDK::setTiltPos(int pos)
{
    /* {"method": "setPanPos", "pos": pos} */
    QString command = "{\"method\": \"setTiltPos\", \"pos\":" + QString::number(pos) + "}";
    API_send(command);
}

/*
 * Set a new position to the active PTS camera
*/
void VideoSDK::setZoomPos(int pos)
{
    /* {"method": "setPanPos", "pos": pos} */
    QString command = "{\"method\": \"setZoomPos\", \"pos\":" + QString::number(pos) + "}";
    API_send(command);
}

void VideoSDK::changeWindowState(WindowState windowState, bool stayOnTop)
{
    QString command = "{\"method\": \"changeWindowState\", \"windowState\":" + QString::number(windowState) + ", \"stayOnTop\":" + QVariant(stayOnTop).toString() + "}";
    API_send(command);
}

void VideoSDK::onSocketConnected()
{
    qDebug() << "WebSocket '" + m_socket->origin() + "' connected" << endl;
    auth();
}

void VideoSDK::onSocketDisconnected()
{
    setCurrentState(State::none);

    qDebug() << "WebSocket '" + m_socket->origin() + "' disconnected" << endl;

    if(m_started) {
        emit closed();
    }

    /* Stop queue sending */
    m_timer.stop();
    /* Close the socket */
    m_socket->close();

    m_started = false;
}

void VideoSDK::onSocketError(QAbstractSocket::SocketError err)
{
    /* Emit signal */
    if(m_socket)
        emit error(m_socket->errorString());
    else if(err == QAbstractSocket::SocketError::ConnectionRefusedError)
        emit error("Connection Refused Error");
    else
        emit error("WebSocket closed. Error: " + QString::number(err));
}

void VideoSDK::auth()
{
    QString command;

    if(!m_pin.isEmpty()) {
        command = "{\"method\": \"auth\", \"type\": \"secured\", \"credentials\": \"" + m_pin + "\"}";
    }
    else if(!m_pin.isNull()) {
        command = "{\"method\": \"auth\", \"type\": \"unsecured\"}";
    }
    else {
        command = "{\"method\": \"auth\", \"role\": \"user\"}";
    }
    /* Only here send() */
    API_send_direct(command);
}

bool VideoSDK::processIncoming(const QString &data)
{
    bool processed = false;

    QJsonParseError err;
    QJsonDocument json_doc = QJsonDocument::fromJson(data.toUtf8(), &err);
    QJsonObject json_obj = json_doc.object();

    /* { "method": ..., "result": ... }; */
    if(err.error == QJsonParseError::NoError && json_obj.contains(OBJ_METHOD))
    {
        /* { "method": "auth", "result": true }; */
        if(json_obj[OBJ_METHOD] == V_AUTH && json_obj.contains(OBJ_RESULT) && json_obj[OBJ_RESULT].toBool() == true)
        {
            m_started = true;

            /* Emit signal */
            //todo: this is naming hell: 'started' has actually semantics of 'authorized at least as admin'
            //and moreover we emit here 'opened' (wth?) signal.
            //So 'opened' means 'started' and means 'authorized' at the same time! Shouldn't we change this situation?
            emit opened();
            setCurrentState(State::normal);

            processed = true; // <--- processed

            /* Now */
            now_ready();
        }
        /* { "method": "auth", "resultCode": 3, "result": false }; */
        if(json_obj[OBJ_METHOD] == V_AUTH
                && json_obj.contains(OBJ_RESULT_CODE) && json_obj[OBJ_RESULT_CODE].toInt() == 3
                && json_obj.contains(OBJ_ERROR)
                && json_obj.contains(OBJ_RESULT) && json_obj[OBJ_RESULT].toBool() == false)
        {
            m_started = false;
            QString err = QString(json_obj[OBJ_ERROR].toString());

            /* Emit signal */
            setCurrentState(State::login);

            processed = true; // <--- processed

            /* Now */
            on_error(err);
        }
        /* {"method":"getAppState","requestId":"","embeddedHttpPort":8766,"appState":3,"desktopSharing":{"running":false},"broadcastPicture":{"running":false},"audioCaptureTest":false,"result":true} */
        else if(json_obj[OBJ_METHOD].toString() == V_GET_APP_STATE && json_obj.contains(OBJ_APP_STATE))
        {
            int stateReceived = json_obj[OBJ_APP_STATE].toInt(0);
            qDebug() << "SdkState now: " << stateToText(state());
            qDebug() << "AppState returned for getAppState request: " << stateToText(State(stateReceived)) << endl;
            setCurrentState(stateReceived, true);

            processed = true; // <--- processed
        }
        /* {"method":"event", "event": ..., ...}" */
        else if(json_obj.contains(OBJ_METHOD) && json_obj.contains(OBJ_EVENT)
                && json_obj[OBJ_METHOD].toString() == OBJ_EVENT)
        {
            processIncomingEvent(json_obj[OBJ_EVENT].toString(), json_obj);

            processed = true; // <--- processed
        }
        /* === ERROR ============================================= */
        /* { "error": ... } */
        else if(json_obj.contains(OBJ_ERROR))
        {
            QString err = QString(json_obj[OBJ_ERROR].toString());

            processed = true; // <--- processed

            /* Now */
            on_error(err);
        }
    }
    /* === ERROR ============================================= */
    else if(err.error != QJsonParseError::NoError)
    {
        QString sErr = "processIncoming(): " + err.errorString();

        /* Emit signal */
        emit error(QString(sErr));

        /* Now */
        on_error(sErr);
    }

    return processed;
    // auto j = {"appState": None, "method": "getAppState", "result": None};
}

void VideoSDK::processIncomingEvent(const QString &event, const QJsonObject &json_obj)
{

    /* {"event": "appStateChanged", "appState": None} */
    if(event == V_APP_STATE_CHANGED && json_obj.contains(OBJ_APP_STATE))
    {
        const int stateReceived = json_obj[OBJ_APP_STATE].toInt(0);
        setCurrentState(stateReceived, true);
    }
    else
    {

    }

    emit socketReceivedEvent(event, json_obj);
}

/*
 * Request an application state
*/
void VideoSDK::requestAppState()
{
    QString command = "{\"method\": \"getAppState\"}";
    API_send(command);
}

/*
 * Request the settings list
*/
void VideoSDK::requestSettings()
{
    QString command = "{\"method\": \"getSettings\"}";
    API_send(command);
}

/*
 * Request the system information
*/
void VideoSDK::requestSystemInfo()
{
    QString command = "{\"method\": \"getSystemInfo\"}";
    API_send(command);
}

/*
 * Request the information about monitors
*/
void VideoSDK::requestMonitorsInfo()
{
    QString command = "{\"method\": \"getMonitorsInfo\"}";
    API_send(command);
}

void VideoSDK::requestConferenceParticipants()
{
    QString command = R"({"method": "getConferenceParticipants"})";
    API_send(command);
}

/*
 * When ready
*/
void VideoSDK::now_ready()
{
    qDebug() << ":now_ready" << endl ;
    requestAppState();
    requestSettings();
    requestSystemInfo();
    requestMonitorsInfo();
}

/*
 * When error
*/
void VideoSDK::on_error(const QString &e)
{
    /* Emit signal */
    emit error(QString(e));

    qDebug() << ":now_error" << endl;
    qDebug() << " error: " << e << endl;
}

/*
 * When warning
*/
void VideoSDK::on_warning(const QString &w) //todo: rename all such methods and correct codestyle
{
    /* Emit signal */
    emit warning(QString(w));

    //todo: qWarning() ?
    qDebug() << ":now_warning" << endl;
    qDebug() << " warning: " << w << endl;
}

State VideoSDK::state() const
{
    return m_state;
}

void VideoSDK::setCurrentState(int state, bool emitDeprecated)
{
    if(State(state) != m_state) {
        m_state = State(state);
        qDebug() << "Changing SdkState to: " << stateToText(State(state)) << endl;
        /* Emit signal */
        if(emitDeprecated) { emit change_state(m_state); } //deprecated
        emit stateChanged(m_state);
    }
}

bool VideoSDK::started() const
{
    return m_started;
}

QString VideoSDK::stateToText(const State state)
{
    switch(state)
    {
        case State::none: return "No connection to the server and TrueConf Room does nothing";
        case State::connect: return "Tries to connect to the server";
        case State::login: return "You need to login";
        case State::normal: return "Connected to the server and logged in";
        case State::wait: return "Pending: either it calls somebody or somebody calls it";
        case State::conference: return "In the conference";
        case State::close: return "Finishing the conference";
        default: return "Unknown state";
    }
}

/*
 * This is the main method to send commands to websocket API
*/
void VideoSDK::API_send(const QString &data)
{
    QMutexLocker locker(&m_mutex);
    m_queue.append(new QString(data));

    //todo: prepend endl or just '\n' when needed instead of append! Everywhere.
    qDebug() << "API_send data: "<< data << "Queue length:" << m_queue.length() << endl;
}

void VideoSDK::clear_queue()
{
    QMutexLocker locker(&m_mutex);
    m_queue.clear();
    qDebug() << "Clear queue" << endl;
}

int VideoSDK::API_send_direct(const QString &data)
{
    int res = m_socket->sendTextMessage(data);
    if(res <= 0)
        qDebug() << "Send error! " << endl << "Data: " << data << endl;
    else
        qDebug() << "Send Ok: " << data << endl;

    return res;
}

/*
 * QTimer::timeout signal processing
*/
void VideoSDK::queue_processing()
{
    /* LOCK */
    QMutexLocker locker(&m_mutex);

    if(!started())
    {
        return;
    }

    if(m_queue.length() > 0)
    {
        QString s {*m_queue[0]};

        /* Send data to Video SDK */
        if(API_send_direct(s) > 0)
        {
            /* If the data was successfully sent  */
            m_queue.removeAt(0);
            qDebug() << "Queue length:" << m_queue.length() << endl;
        }
    }
}

void VideoSDK::onFileDownloaded(QNetworkReply *nwReply)
{
    if(nwReply->error() != QNetworkReply::NoError) {
        qDebug() << "Network reply error:" << nwReply->error();
    }

    m_downloadedData = nwReply->readAll();
    nwReply->deleteLater();

    if(nwReply->url().toString().endsWith("config.json")) {

        QString errTxt;
        if(parseConfigJsonFileData(m_downloadedData, &errTxt)) {
            openWebsocketSession(m_host, m_configWebsocketPort);
        }
        else {
            int defaultWebsocketPort = (m_port == DEFAULT_VIDEOSDK_PORT) ? DEFAULT_WEBSOCKET_PORT_FOR_VIDEOSDK : 0;
            defaultWebsocketPort = (m_port == DEFAULT_ROOM_PORT) ? DEFAULT_WEBSOCKET_PORT_FOR_ROOM : defaultWebsocketPort;
            const QString errMsg =
                    QStringLiteral("Unable to load config file%1").arg(errTxt.isEmpty() ? QString() : QString(" (%1)").arg(errTxt));

            if(defaultWebsocketPort) {
                qWarning() << qPrintable(errMsg);
                qWarning() << "Trying default websocket port:" << defaultWebsocketPort;
                openWebsocketSession(m_host, defaultWebsocketPort);
            }
            else {
                on_error(errMsg);
            }
        }
    }
}

bool VideoSDK::parseConfigJsonFileData(const QByteArray& cfgJsonData, QString *errTxt)
{
    bool success = false;
    if(errTxt) { errTxt->clear(); }

    auto configJsonDocument = QJsonDocument::fromJson(cfgJsonData);

    if(!configJsonDocument.isNull()) { //json is valid
        qDebug() << "Config file is successfully read, searching for settings...";

        m_configHttpPort = configJsonDocument["config"]["http"]["port"].toDouble();
        m_configWebsocketPort = configJsonDocument["config"]["websocket"]["port"].toDouble();
        qDebug() << "Config file http-port:" << m_configHttpPort;
        qDebug() << "Config file websocket-port:" << m_configWebsocketPort;

        success = (m_configHttpPort && m_configWebsocketPort);
        if(!success && errTxt) { *errTxt = QStringLiteral("Missing or wrong json key(s)/value(s)"); }
    }
    else {
        //qDebug() << "Config file is invalid!";
        if(errTxt) {
            *errTxt = cfgJsonData.isEmpty() ? QStringLiteral("File is empty/missing")
                                            : QStringLiteral("File has invalid json content");
        }

        //uncomment for debug
//        qDebug() << "\nDownloaded byte array:" << cfgJsonData;
//        if(cfgJsonData.size() > 2) {
//            qDebug() << "\n0:" << cfgJsonData[0] << "\n1:" <<cfgJsonData[1];
//        }
    }

    return success;
}

void VideoSDK::setPrintUnprocessedDataEnabled(bool enabled)
{
    m_printUnprocessedDataEnabled = enabled;
    on_warning(QStringLiteral("Displaying of unprocessed websocket data is currently disabled! "
                              "You may reenable it by calling 'setPrintUnprocessedDataEnabled()'"));
}

/*
 * Signal textMessageReceived() from QWebSocket* m_socket
*/
void VideoSDK::onSocketReceived(const QString &data)
{
    // Emit
    emit socketReceived(data);

    // Process
    if(!processIncoming(data) && m_printUnprocessedDataEnabled)
        qDebug() << "Data Unprocessed:" << data << endl;
}

/*
 * Signal destroyed(QObject) from QWebSocket* m_socket
*/
void VideoSDK::onSocketDestroyed(QObject *obj)
{
    qDebug() << "WebSocket '" + obj->objectName() + "' destroyed" << endl;
}


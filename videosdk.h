#ifndef VIDEOSDK_H
#define VIDEOSDK_H

#include <QObject>
#include <QWebSocket>
#include <QNetworkAccessManager>
#include <QDebug>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringLiteral>
#include <QMutex>
#include <QList>
#include <QTimer>
#include <QThread>
#include "methods.h"
#include "events.h"

#define QUEUE_INTERVAL 50
#define WAIT_INTERVAL 50
#define WAIT_COUNT 20
#define WAIT_FOR_SESSION 3000

#define OBJ_METHOD "method"
#define OBJ_EVENT "event"
#define OBJ_TYPE  "type"
#define OBJ_REQUEST_ID "requestId"
#define OBJ_RESULT_CODE "resultCode"
#define OBJ_ERROR "error"
#define OBJ_RESULT "result"
#define OBJ_CREDENTIALS "credentials"
#define OBJ_tokenForHttpServer "tokenForHttpServer"
#define OBJ_APP_STATE "appState"

#define V_AUTH "auth"
#define V_SECURED "secured"
#define V_GET_APP_STATE "getAppState"
#define V_APP_STATE_CHANGED "appStateChanged"

#define DEFAULT_ROOM_PORT 2525
#define DEFAULT_VIDEOSDK_PORT 8080

#define DEFAULT_WEBSOCKET_PORT_FOR_ROOM 8765
#define DEFAULT_HTTP_PORT_FOR_ROOM 8766
#define DEFAULT_WEBSOCKET_PORT_FOR_VIDEOSDK 8767
#define DEFAULT_HTTP_PORT_FOR_VIDEOSDK = 8768

enum State
{
    none = 0,       // No connection to the server and TrueConf Room does nothing
    connect = 1,    // Tries to connect to the server
    login = 2,      // you need to login
    normal = 3,     // Connected to the server and logged in
    wait = 4,       // Pending: either it calls somebody or somebody calls it
    conference = 5, // In the conference
    close = 6       // Finishing the conference
};

enum WindowState
{
    minimized = 1,
    maximized = 2
};

typedef struct SocketData {
    QString tokenForHttpServer;
} SocketData;

class VideoSDK : public QObject
{
    Q_OBJECT

    friend CMethods;
    friend CEvents;
public:
    explicit VideoSDK(QObject *parent = 0);
    ~VideoSDK();

public:
    bool started() const;
    static QString stateToText(const State state);

public:
    void open_session(const QString &host, const int port = 80, const QString &pin = nullptr);
    void close_session();
    CMethods* Methods();
    CEvents* Events();
    void connectToServer(const QString& server, const int port = 4307);
    void connectToService();
    void login(const QString& callId, const QString& password);
    void logout();
    void call(const QString &peerId);
    void reject();
    void accept();
    void hangUp(const bool forAll = false);
    void moveVideoSlotToMonitor(const QString& callId, int monitorIndex);
    void sendCommand(QString& peerId, QString& cmd);
    void setPanPos(int pos);
    void setTiltPos(int pos);
    void setZoomPos(int pos);
    void changeWindowState(WindowState windowState, bool stayOnTop);
    State state() const;
    void API_send(const QString &data);
    void setPrintUnprocessedDataEnabled(bool enabled);

protected:
    void send_command(const QString &data);
    void clear_queue();
    void on_error(const QString &e);
    void on_warning(const QString &w); //todo: rename all such methods and correct codestyle
    void auth();
    bool processIncoming(const QString& data);
    void processIncomingEvent(const QString &event, const QJsonObject &json_obj);
    /* Requests */
    void requestAppState();
    void requestSettings();
    void requestSystemInfo();
    void requestMonitorsInfo();
    void requestConferenceParticipants();

private:
    int API_send_direct(const QString &data);
    void openWebsocketSession(const QString &host, const int port);
    bool parseConfigJsonFileData(const QByteArray &cfgJsonData, QString *errTxt = nullptr);
    void now_ready();

    //'emitDeprecated' == true lets old code using 'change_state(State)' signal work as it was before this commit
    //todo: remove 'emitDeprecated' upon removing deprecated signal 'change_state(State)' from all code
    void setCurrentState(int state, bool emitDeprecated = false);

signals:
    void opened();
    void closed();
    void error(QString text);
    void warning(QString text);
    [[deprecated("Use stateChanged(State) instead.")]]
    void change_state(State state);
    void stateChanged(State state);
    void socketReceived(QString data);
    void socketReceivedEvent(const QString &name, const QJsonObject &json_obj);

private:
    QMutex m_mutex;
    bool m_started = false;
    QString m_host;
    QString m_pin;
    int m_port{0};
    int m_configHttpPort{0};
    int m_configWebsocketPort{0};
    QWebSocket* m_socket = nullptr;
    SocketData m_socketData;
    QList<QString*> m_queue;
    QTimer m_timer;
    State m_state = State(0);
    CMethods* m_methods;
    CEvents* m_events;
    QNetworkAccessManager m_networkAccessMgr;
    QByteArray m_downloadedData;
    bool m_printUnprocessedDataEnabled{true};

private slots:
    void onSocketConnected();
    void onSocketDisconnected();
    void onSocketError(QAbstractSocket::SocketError err);
    void onSocketReceived(const QString &data);
    void onSocketDestroyed(QObject *obj = nullptr);
    /* For QTimer::quit signal */
    void queue_processing();

    void onFileDownloaded(QNetworkReply* nwReply);
};

class WaitSessionThread : public QThread
{
    Q_OBJECT
private:
    VideoSDK *m_sdk;
    QMutex m_mutex;

public:
    explicit WaitSessionThread(VideoSDK *sdk): QThread(sdk)
    {
        m_sdk = sdk;
    };

    ~WaitSessionThread()
    {
        qDebug() << "WaitSessionThread destroyed" << endl;
    }

protected :
    void run()
    {
        int count = 0;
        while(count++ < WAIT_COUNT)
        {
            {
                QMutexLocker locker(&m_mutex);

                if(m_sdk->started())
                    return;
            }
            QThread::msleep(WAIT_INTERVAL);
        }
    }
};

#endif // VIDEOSDK_H

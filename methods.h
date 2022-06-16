#ifndef METHODS_H
#define METHODS_H

#include <QObject>

class VideoSDK;

class CMethods {

public:
    CMethods(VideoSDK *sdk);

private:
    VideoSDK *m_sdk;

/* All Video SDK API methods */
public:

    /*!
    * Make p2p call
    *
    * @param[in] peerId A unique user ID (TrueConfID)
    */
    void call(const QString &peerId);

    /*!
    *Accept the call. The command is run immediately and the result of execution is received at once.
    *
    *Response example
    *----------
    *{"event" : "commandExecution", "accept" : "ok"}
    */
    void accept();

    /*!
    *End a call or a conference. The command is used when the conference has already been created.
    *hangUp() format is used during a video call. During group conferences both formats are used.
    *By using hangUp(False) format, you leave the conference, but other participants remain in the conference.
    *By using hangUp(True) the conference ends for all the participants.
    *Positive response ("ok") means the command has been accepted for execution but has not been run executed yet.
    *Execution result will be received separately via notification.
    *
    *@param[in] forAll
    *True - conference ends for all the participants;
    *False - you leave the conference, but other participants remain in the conference.
    *
    */
    void hangUp(bool forAll);

    ///Login to TrueConf server
    void login(const QString &callId, const QString &password);

    ///Log out the current user
    void logout();

    /*!
    *Connect to TrueConf Server
    *
    *@param[in] server Server address. For example, IP address;
    *@param[in] port Port. Default port is 4307.
    */
    void connectToServer(const QString &server, int port);

    void sendCommand(const QString &peerId, const QString &command);

    void showMainWindow(bool maximized, bool stayOnTop);

    ///The command allows to reject incoming call or invitation to the conference
    void reject();

    /*!
    *Reject user’s request to join your conference
    *
    *@param[in] peerId unique user ID
    */
    void rejectPeer(const QString &peerId);

    /*!
    *Accept a request from the user to participate in your conference
    *
    *@param[in] peerId unique user ID
    */
    void acceptPeer(const QString &peerId);

    /*!
    *Create a conference with specified parameters and participants
    *
    *@param[in] title Title
    *@param[in] confType Conference type.
    *Must be follow values:
    *   "symmetric" - symmetric
    *   "asymmetric" - assymetric
    *   "role" - role-based
    *@param[in] autoAccept An indicator which gives permission to automatically accept participants into the conference
    *@param[in] inviteList List of strings with unique user identifiers (TrueConf ID) to whom an invitation to the conference will be sent
    */
    void createConference(const QString &title, const QString &confType, bool autoAccept, const QList<QString>& inviteList);

    ///Requesting the list of hardware.
    void getHardware();

    /*!
    *Accept incoming files
    *
    *@param[in] id request ID
    */
    void acceptFile(int id);

    ///Accept an incoming request to the podium
    void acceptInvitationToPodium();

    /*!
    *Allow remote camera control
    *
    *@param[in] callId User ID (TrueConf ID)
    */
    void acceptRequestCameraControl(const QString &callId);

    /*!
    *Allow the user to enter the podium
    *
    *@param[in] peerId User ID (TrueConf ID)
    */
    void acceptRequestToPodium(const QString &peerId);

    /*!
    *Add a new slide to SlideShow
    *
    *@param[in] fileId File ID in http-server
    */
    void addSlide(int fileId);

    /*!
    *Add a user to address book
    *
    *@param[in] peerId User ID (TrueConf ID)
    *@param[in] peerDn Display name
    */
    void addToAbook(const QString &peerId, const QString &peerDn);

    /*!
    *Add the user to a group in the address book
    *
    *@param[in] groupId Group ID
    *@param[in] peerId User ID (TrueConf ID)
    */
    void addToGroup(int groupId, const QString &peerId);

    /*!
    *Allow video recording for a user
    *
    *@param[in] peerId User ID (TrueConf ID)
    */
    void allowRecord(const QString &peerId);

    /*!
    *Add user to block list
    *
    *@param[in] peerId User ID (TrueConf ID)
    */
    void block(const QString &peerId);

    /*!
    *Move the main window to the specified monitor
    *
    *@param[in] monitorIndex The specified monitor's index
    */
    void changeCurrentMonitor(int monitorIndex);

    ///Change the current matrix (layout) type.
    void changeVideoMatrixType(int matrixType);

    /*!
    *Change the state of the main application window.
    *
    *@param[in] windowState Window state
    *@param[in] stayOnTop
    */
    void changeWindowState(int windowState, bool stayOnTop);

    /*!
    *Clear a user's chat history
    *
    *@param[in] id User ID (TrueConf ID)
    */
    void chatClear(const QString &id);

    ///Clear call history
    void clearCallHistory();

    ///Clear file sharing history and delete files
    void clearFileTransfer();

    ///Clear all tokens
    void clearTokens();

    ///Connect to trueconf.com service
    void connectToService();

    ///Create a users group in address book
    void createGroup(const QString &name);

    /*!
    *Create an NDI source from a conference participant
    *
    *@param[in] deviceId User ID (TrueConf ID)
    *@example @code sdk.createNDIDevice("user1@some.server") @endcode
    */
    void createNDIDevice(const QString &deviceId);

    /*!
    *Delete a data container
    *
    *@param[in] containerName Container name
    */
    void deleteData(const QString &containerName);

    /*!
    *Delete a file from the file sharing history
    *
    *@param[in] fileId File ID
    */
    void deleteFileTransferFile(int fileId);

    /*!
    *Delete NDI source
    *
    *@param[in] deviceId User ID (TrueConf ID)
    *@example
    *@code sdk.deleteNDIDevice("user1@some.server") @endcode
    */
    void deleteNDIDevice(const QString &deviceId);

    /*!
    *Deny recording audio stream and video stream
    *
    *@param[in] peerId User ID (TrueConf ID)
    */
    void denyRecord(const QString &peerId);

    /*!
    *Enable or disable audio receiving from user - "peerId"
    *
    *@param[in] peerId User ID (TrueConf ID)
    *@param[in] enable
    */
    void enableAudioReceiving(const QString &peerId, bool enable);

    /*!
    *Enable or disable video receiving from user - "peerId"
    *
    *@param[in] peerId User ID (TrueConf ID)
    *@param[in] enable
    *@example
    *@code
    // Switching video off from user "user1@some.server"
       sdk.enableVideoReceiving("user1@some.server", False)
    @endcode
    */
    void enableVideoReceiving(const QString &peerId, bool enable);

    /*!
    *Transform the current videocall to a group conference
    *
    *@param title Conference title
    *@param inviteList Invited list
    *@example @code sdk.expandCallToMulti(title="New group conference", inviteList=["user1@some.server", "user2@some.server", "user3@some.server"]) @endcode
    */
    void expandCallToMulti(const QString& title, const QList<QString>& inviteList);

    /*!
    *Fire a custom event
    *
    *@param[in] data Any data string
    *@example @code sdk.fireMyEvent("power off") @endcode
    */
    void fireMyEvent(const QString &data);

    ///Request the address book
    void getAbook();

    ///Request names of all data containers
    void getAllUserContainersNames();

    ///Request information about the current sound playback device
    void getAppSndDev();

    ///Request the application state
    void getAppState();
};


#endif // METHODS_H

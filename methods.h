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
    *:True - conference ends for all the participants;
    *False - you leave the conference, but other participants remain in the conference.
    *
    */
    void hangUp(bool forAll);

    /*!
    *Login to TrueConf server
    */
    void login(const QString &callId, const QString &password);

    /*!
    *Log out the current user
    */
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

    /*!
    *The command allows to reject incoming call or invitation to the conference
    */
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

    /*!
    *Requesting the list of hardware.
    */
    void getHardware();

    /*!
    *Accept incoming files
    *
    *@param[in] id request ID
    */
    void acceptFile(int id);

    /*!
    *Accept an incoming request to the podium
    */
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

    /*!
    *Change the current matrix (layout) type.
    */
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

    /*!
    *Clear call history
    */
    void clearCallHistory();

    /*!
    *Clear file sharing history and delete files
    */
    void clearFileTransfer();

    /*!
    *Clear all tokens
    */
    void clearTokens();

    /*!
    *Connect to trueconf.com service
    */
    void connectToService();

    /*!
    *Create a users group in address book
    */
    void createGroup(const QString &name);

    /*!
    *Create an NDI source from a conference participant
    *
    *@param[in] deviceId User ID (TrueConf ID)
    *
    *Example
    *@code sdk.createNDIDevice("user1@some.server") @endcode

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
    *
    *Example
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
    *
    *Example
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
    *
    *Example
    *@code sdk.expandCallToMulti(title="New group conference", inviteList=["user1@some.server", "user2@some.server", "user3@some.server"]) @endcode
    */
    void expandCallToMulti(const QString& title, const QList<QString>& inviteList);

    /*!
    *Fire a custom event
    *
    *@param[in] data Any data string
    *
    *Example
    *@code sdk.fireMyEvent("power off") @endcode
    */
    void fireMyEvent(const QString &data);


    /*!
    *Request the address book
    */
    void getAbook();

    /*!
    *Request names of all data containers
    */
    void getAllUserContainersNames();

    /*!
    *Request information about the current sound playback device
    */
    void getAppSndDev();

    /*!
    *Request the application state
    */
    void getAppState();

    void activateLicense(const QString& key);

    void auth(const QString& role, const QString& type = "", const QString& credentials = "");

    void getAudioDelayDetectorInfo();

    void getAudioMute();

    void getAudioReceivingLevel(const QString& peerId);

    void getAuthInfo();

    void getAvailableServersList();

    void getBackground();

    void getBanList();

    void getBroadcastPicture();

    void getBroadcastSelfie();

    void getCallHistory(int count);

    void getChatLastMessages(const QString& id, int beginNumber, int count);

    void getConferenceParticipants();

    void getConferences();

    void getConnected();

    void getContactDetails(const QString& peerId);

    void getCreatedNDIDevices();

    void getCrop();

    void getCurrentUserProfileUrl();

    void getDisplayNameById(const QString& peerId);

    void getFileInfo(int id);

    void getFileList();

    void getFileRequests();

    void getFileTransferAvailability();

    void getFileTransferInfo();

    void getFileUploads();

    void getGroups();

    void getHardwareKey();

    void getHttpServerSettings();

    void getHttpServerState();

    void getIncomingCameraControlRequests();

    void getInfoWidgetsState();

    void getLastCallsViewTime();

    void getLastSelectedConference();

    void getLastUsedServersList(int count);

    void getLicenseServerStatus();

    void getLicenseType();

    void getListOfChats();

    void getLogin();

    void getLogo();

    void getMaxConfTitleLength();

    void getMicMute();

    void getModes();

    void getMonitorsInfo();

    void getNDIState();

    void getOutgoingBitrate();

    void getOutgoingCameraControlRequests();

    void getOutputSelfVideoRotateAngle();

    void getProperties();

    void getPtzControls();

    void getRemotelyControlledCameras();

    void getRenderInfo();

    void getScheduler();

    void getServerDomain();

    void getSettings();

    void getSlideShowCache();

    void getSlideShowInfo();

    void getSystemInfo();

    void getTariffRestrictions();

    void getTokenForHttpServer();

    void getTrueConfRoomProKey();

    void getVideoMatrix();

    void getVideoMute();

    void getWebManagerUrl();

    void gotoPodium();

    void hideVideoSlot(const QString& callId);

    void inviteToConference(const QString& peerId);

    void inviteToPodium(const QString& peerId);

    void kickFromPodium(const QString& peerId);

    void kickPeer(const QString& peerId);

    void leavePodium();

    void loadData(const QString& containerName);

    void moveVideoSlotToMonitor(const QString& callId, int monitorIndex);

    void productRegistrationOffline(int fileId);

    void ptzDown();

    void ptzLeft();

    void ptzRight();

    void ptzStop();

    void ptzUp();

    void ptzZoomDec();

    void ptzZoomInc();

    void rebootSystem();

    void rejectFile(int id);

    void rejectInvitationToPodium();

    void rejectRequestCameraControl(const QString& callId);

    void rejectRequestToPodium(const QString& peerId);

    void remotelyControlledCameraPtzDown(const QString& cameraOwnerCallId);

    void remotelyControlledCameraPtzLeft(const QString& cameraOwnerCallId);

    void remotelyControlledCameraPtzRight(const QString& cameraOwnerCallId);

    void remotelyControlledCameraPtzUp(const QString& cameraOwnerCallId);

    void remotelyControlledCameraPtzZoomDec(const QString& cameraOwnerCallId);

    void remotelyControlledCameraPtzZoomInc(const QString& cameraOwnerCallId);

    void removeAllSlides(bool removeFromServer);

    void removeFromAbook(const QString& peerId);

    void removeFromGroup(int groupId, const QString& peerId);

    void removeFromServersList(const QString& serverName);

    void removeGroup(int groupId);

    void removeImageFromCachingQueue(int groupId);

    void removeSlide(int idx, bool removeFromServer);

    void removeVideoSlotFromMonitor(int monitorIndex);

    void renameGroup(int groupId, const QString& newName);

    void renameInAbook(const QString& peerId, const QString& peerDn);

    void requestParticipantCameraControl(const QString& callId);

    void restoreWindow();

    void saveData(const QString& containerName, const QString& data, const QString& flags);

    void sendConferenceFile(int fileId);

    void sendFile(int fileId, const QString& peerId);

    void sendGroupMessage(const QString& message);

    void sendMessage(const QString& peerId, const QString& message);

    void setAppSndDev(const QString& name, const QString& description);

    void setAudioCapturer(const QString& name, const QString& description);

    void setAudioMute(bool mute);

    void setAudioReceivingLevel(const QString& peerId, int level);

    void setAudioRenderer(const QString& name, const QString& description);

    void setAuthParams(const QString& userType, const QString& authType, const QString& authValue);

    void setBackground(int fileId);

    void setBroadcastSelfie(bool enabled, int fps);

    void setCrop(bool enable);

    void setDefaultBackground();

    void setDefaultLogo();

    void setHttpServerSettings(const QMap<QString, int>& settings);

    void setLastCallsViewed();

    void setLogo(int fileId, int mode);

    void setMicMute(bool mute);

    void setModeratorRole(const QString& peerId, bool moderator);

    void setModes(const QString& pin, const QString& mode);

    void setNDIState(bool enabled);

    void setOutputSelfVideoRotateAngle(int rotateAngle);

    void setPanPos(int pos);

    void setPtzDefaults();

    void setSettings(const QString& settings);

    void setSlidePosition(int fromIdx, int toIdx);

    void setTiltPos(int pos);

    void setUsedApiVersion(const QString& version);

    void setVideoCapturer(const QString& name, const QString& description);

    void setVideoMute(bool mute);

    void setZoomPos(int pos);

    void showFirstSlide();

    void showLastSlide();

    void showNextSlide();

    void showPrevSlide();

    void showSlide(int idx);

    void showVideoSlot(const QString& callId);

    void shutdown(bool forAll);

    void shutdownSystem();

    void sortSlides();

    void startAudioDelayDetectorTest();

    void startBroadcastPicture(int fileId);

    void startCapture(int captureId);

    void startHttpServer();

    void startRemark();

    void startSlideShow(const QString& title, int startingIdx);

    void stopAudioDelayDetectorTest();

    void stopBroadcastPicture();

    void stopCachingAllImages();

    void stopCapture();

    void stopHttpServer();

    void stopSlideShow();

    void swapVideoSlots(const QString& callId1, const QString& callId2);

    void switchVideoFlow();

    void switchVideoFlow(const QString& callId, bool mainCamera);

    void testAudioCapturerStart();

    void testAudioCapturerStop();

    void testAudioRenderer();

    void toneDial(const QString& symbol, const QString& callId);

    void turnRemoteCamera(const QString& peerId, bool on);

    void turnRemoteMic(const QString& peerId, bool on);

    void turnRemoteSpeaker(const QString& peerId, bool on);

    void unblock(const QString& peerId);
};


#endif // METHODS_H

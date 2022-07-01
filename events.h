#ifndef CEVENTS_H
#define CEVENTS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class VideoSDK;

class CEvents: public QObject
{
    Q_OBJECT
public:
    explicit CEvents(VideoSDK *sdk);

private:
    VideoSDK *m_sdk;

private slots:
    void socketReceivedEvent(const QString &name, const QJsonObject &json_obj);

signals:
    void abReceivedAfterLogin(const QJsonObject &responce);
    void allSlidesCachingStopped(const QJsonObject &responce);
    void allSlidesRemoved(const QJsonObject &responce);
    void appSndDevChanged(const QJsonObject &responce);
    void appStateChanged(const QJsonObject &responce);
    void appUpdateAvailable(const QJsonObject &responce);
    void audioCapturerMute(const QJsonObject &responce);
    void audioDelayDetectorTestStateChanged(const QJsonObject &responce);
    void audioRendererMute(const QJsonObject &responce);
    void authorizationNeeded(const QJsonObject &responce);
    void availableServersListLoaded(const QJsonObject &responce);
    void backgroundImageChanged(const QJsonObject &responce);
    void blurChanged(const QJsonObject &responce);
    void broadcastPictureStateChanged(const QJsonObject &responce);
    void broadcastSelfieChanged(const QJsonObject &responce);
    void callHistoryCleared(const QJsonObject &responce);
    void cameraStateChangedByConferenceOwner(const QJsonObject &responce);
    void chatMessageSent(const QJsonObject &responce);
    void cmdChatClear(const QJsonObject &responce);
    void commandReceived(const QJsonObject &responce);
    void commandSent(const QJsonObject &responce);
    void conferenceCreated(const QJsonObject &responce);
    void conferenceDeleted(const QJsonObject &responce);
    void conferenceList(const QJsonObject &responce);
    void contactBlocked(const QJsonObject &responce);
    void contactsAdded(const QJsonObject &responce);
    void contactsDeleted(const QJsonObject &responce);
    void contactsRenamed(const QJsonObject &responce);
    void contactUnblocked(const QJsonObject &responce);
    void cropChanged(const QJsonObject &responce);
    void currentSlideIndexChanged(const QJsonObject &responce);
    void currentUserDisplayNameChanged(const QJsonObject &responce);
    void currentUserProfileUrlChanged(const QJsonObject &responce);
    void customLogoUsageChanged(const QJsonObject &responce);
    void dataDeleted(const QJsonObject &responce);
    void dataSaved(const QJsonObject &responce);
    void detailsInfo(const QJsonObject &responce);
    void deviceModesDone(const QJsonObject &responce);
    void deviceStatusReceived(const QJsonObject &responce);
    void downloadProgress(const QJsonObject &responce);
    void dsStarted(const QJsonObject &responce);
    void dsStopped(const QJsonObject &responce);
    void enableAudioReceivingChanged(const QJsonObject &responce);
    void enableVideoReceivingChanged(const QJsonObject &responce);
    void extraVideoFlowNotify(const QJsonObject &responce);
    void fileAccepted(const QJsonObject &responce);
    void fileConferenceSent(const QJsonObject &responce);
    void fileDownloadingProgress(const QJsonObject &responce);
    void fileRejected(const QJsonObject &responce);
    void fileSent(const QJsonObject &responce);
    void fileStatus(const QJsonObject &responce);
    void fileTransferAvailable(const QJsonObject &responce);
    void fileTransferCleared(const QJsonObject &responce);
    void fileTransferFileDeleted(const QJsonObject &responce);
    void fileTransferPinChanged(const QJsonObject &responce);
    void fileUploadingProgress(const QJsonObject &responce);
    void groupChatMessageSent(const QJsonObject &responce);
    void groupsAdded(const QJsonObject &responce);
    void groupsRemoved(const QJsonObject &responce);
    void groupsRenamed(const QJsonObject &responce);
    void hangUpPressed(const QJsonObject &responce);
    void hardwareChanged(const QJsonObject &responce);
    void hookOffPressed(const QJsonObject &responce);
    void httpServerSettingChanged(const QJsonObject &responce);
    void httpServerStateChanged(const QJsonObject &responce);
    void imageAddedToCachingQueue(const QJsonObject &responce);
    void imageRemovedFromCachingQueue(const QJsonObject &responce);
    void incomingChatMessage(const QJsonObject &responce);
    void incomingGroupChatMessage(const QJsonObject &responce);
    void incomingPodiumInvitationRemoved(const QJsonObject &responce);
    void incomingRequestCameraControlAccepted(const QJsonObject &responce);
    void incomingRequestCameraControlRejected(const QJsonObject &responce);
    void incomingRequestToPodiumAnswered(const QJsonObject &responce);
    void inviteReceived(const QJsonObject &responce);
    void inviteRequestSent(const QJsonObject &responce);
    void inviteSent(const QJsonObject &responce);
    void joinToConferenceLinkReceived(const QJsonObject &responce);
    void lastCallsViewed(const QJsonObject &responce);
    void licenseActivation(const QJsonObject &responce);
    void licenseStatusChanged(const QJsonObject &responce);
    void login(const QJsonObject &responce);
    void logoImageChanged(const QJsonObject &responce);
    void logout(const QJsonObject &responce);
    void micStateChangedByConferenceOwner(const QJsonObject &responce);
    void monitorsInfoUpdated(const QJsonObject &responce);
    void myEvent(const QJsonObject &responce);
    void mySlideShowStarted(const QJsonObject &responce);
    void mySlideShowStopped(const QJsonObject &responce);
    void mySlideShowTitleChanged(const QJsonObject &responce);
    void NDIDeviceCreated(const QJsonObject &responce);
    void NDIDeviceDeleted(const QJsonObject &responce);
    void NDIStateChanged(const QJsonObject &responce);
    void newParticipantInConference(const QJsonObject &responce);
    void outgoingBitrateChanged(const QJsonObject &responce);
    void outgoingRequestCameraControlAccepted(const QJsonObject &responce);
    void outgoingRequestCameraControlRejected(const QJsonObject &responce);
    void outputSelfVideoRotateAngleChanged(const QJsonObject &responce);
    void participantLeftConference(const QJsonObject &responce);
    void peerAccepted(const QJsonObject &responce);
    void propertiesUpdated(const QJsonObject &responce);
    void ptzControlsChanged(const QJsonObject &responce);
    void realtimeManagmentUrlAvailabilityChanged(const QJsonObject &responce);
    void receivedFileRequest(const QJsonObject &responce);
    void receiversInfoUpdated(const QJsonObject &responce);
    void recordRequest(const QJsonObject &responce);
    void recordRequestReply(const QJsonObject &responce);
    void rejectReceived(const QJsonObject &responce);
    void rejectSent(const QJsonObject &responce);
    void remarkCountDown(const QJsonObject &responce);
    void remotelyControlledCameraNotAvailableAnymore(const QJsonObject &responce);
    void requestCameraControlReceived(const QJsonObject &responce);
    void requestCameraControlSent(const QJsonObject &responce);
    void requestInviteReceived(const QJsonObject &responce);
    void roleEventOccured(const QJsonObject &responce);
    void serverConnected(const QJsonObject &responce);
    void serverDisconnected(const QJsonObject &responce);
    void settingsChanged(const QJsonObject &responce);
    void showCurrentUserWidget(const QJsonObject &responce);
    void showIncomingRequestWidget(const QJsonObject &responce);
    void showInfoConnect(const QJsonObject &responce);
    void showLogo(const QJsonObject &responce);
    void showTime(const QJsonObject &responce);
    void showUpcomingMeetings(const QJsonObject &responce);
    void slideAdded(const QJsonObject &responce);
    void slideCached(const QJsonObject &responce);
    void slideCachingStarted(const QJsonObject &responce);
    void slidePositionChanged(const QJsonObject &responce);
    void slideRemoved(const QJsonObject &responce);
    void slideShowAvailabilityChanged(const QJsonObject &responce);
    void slideShowCleared(const QJsonObject &responce);
    void slidesSorted(const QJsonObject &responce);
    void slideUploaded(const QJsonObject &responce);
    void stopCalling(const QJsonObject &responce);
    void systemRatingUpdated(const QJsonObject &responce);
    void tariffRestrictionsChanged(const QJsonObject &responce);
    void testAudioCapturerLevel(const QJsonObject &responce);
    void testAudioCapturerStateChanged(const QJsonObject &responce);
    void toneDial(const QJsonObject &responce);
    void updateAvatar(const QJsonObject &responce);
    void updateCameraInfo(const QJsonObject &responce);
    void updateFailed(const QJsonObject &responce);
    void userRecordingMeStatusChanged(const QJsonObject &responce);
    void usersAddedToGroups(const QJsonObject &responce);
    void usersRemovedFromGroups(const QJsonObject &responce);
    void usersStatusesChanged(const QJsonObject &responce);
    void videoCapturerMute(const QJsonObject &responce);
    void videoMatrixChanged(const QJsonObject &responce);
    void videoSlotMovedToMonitor(const QJsonObject &responce);
    void videoSlotRemovedFromMonitor(const QJsonObject &responce);
    void webManagerUrlChanged(const QJsonObject &responce);
    void windowStateChanged(const QJsonObject &responce);
};

#endif // CEVENTS_H

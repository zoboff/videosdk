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
    void abReceivedAfterLogin(const QJsonObject &response);
    void allSlidesCachingStopped(const QJsonObject &response);
    void allSlidesRemoved(const QJsonObject &response);
    void appSndDevChanged(const QJsonObject &response);
    void appStateChanged(const QJsonObject &response);
    void appUpdateAvailable(const QJsonObject &response);
    void audioCapturerMute(const QJsonObject &response);
    void audioDelayDetectorTestStateChanged(const QJsonObject &response);
    void audioRendererMute(const QJsonObject &response);
    void authorizationNeeded(const QJsonObject &response);
    void availableServersListLoaded(const QJsonObject &response);
    void backgroundImageChanged(const QJsonObject &response);
    void blurChanged(const QJsonObject &response);
    void broadcastPictureStateChanged(const QJsonObject &response);
    void broadcastSelfieChanged(const QJsonObject &response);
    void callHistoryCleared(const QJsonObject &response);
    void cameraStateChangedByConferenceOwner(const QJsonObject &response);
    void chatMessageSent(const QJsonObject &response);
    void cmdChatClear(const QJsonObject &response);
    void commandReceived(const QJsonObject &response);
    void commandSent(const QJsonObject &response);
    void conferenceCreated(const QJsonObject &response);
    void conferenceDeleted(const QJsonObject &response);
    void conferenceList(const QJsonObject &response);
    void contactBlocked(const QJsonObject &response);
    void contactsAdded(const QJsonObject &response);
    void contactsDeleted(const QJsonObject &response);
    void contactsRenamed(const QJsonObject &response);
    void contactUnblocked(const QJsonObject &response);
    void cropChanged(const QJsonObject &response);
    void currentSlideIndexChanged(const QJsonObject &response);
    void currentUserDisplayNameChanged(const QJsonObject &response);
    void currentUserProfileUrlChanged(const QJsonObject &response);
    void customLogoUsageChanged(const QJsonObject &response);
    void dataDeleted(const QJsonObject &response);
    void dataSaved(const QJsonObject &response);
    void detailsInfo(const QJsonObject &response);
    void deviceModesDone(const QJsonObject &response);
    void deviceStatusReceived(const QJsonObject &response);
    void downloadProgress(const QJsonObject &response);
    void dsStarted(const QJsonObject &response);
    void dsStopped(const QJsonObject &response);
    void enableAudioReceivingChanged(const QJsonObject &response);
    void enableVideoReceivingChanged(const QJsonObject &response);
    void extraVideoFlowNotify(const QJsonObject &response);
    void fileAccepted(const QJsonObject &response);
    void fileConferenceSent(const QJsonObject &response);
    void fileDeletedFromFileTransferHistory(const QJsonObject &response);
    void fileDownloadingProgress(const QJsonObject &response);
    void fileRequestStatusChanged(const QJsonObject &response);
    void fileRejected(const QJsonObject &response);
    void fileSent(const QJsonObject &response);
    void fileStatus(const QJsonObject &response);
    void fileTransferAvailabilityChanged(const QJsonObject &response);
    void fileTransferAvailable(const QJsonObject &response);
    void fileTransferCleared(const QJsonObject &response);
    void fileTransferFileDeleted(const QJsonObject &response);
    void fileTransferPinChanged(const QJsonObject &response);
    void fileTransferHistoryCleared(const QJsonObject &response);
    void fileUploadingProgress(const QJsonObject &response);
    void groupChatMessageSent(const QJsonObject &response);
    void groupsAdded(const QJsonObject &response);
    void groupsRemoved(const QJsonObject &response);
    void groupsRenamed(const QJsonObject &response);
    void hangUpPressed(const QJsonObject &response);
    void hardwareChanged(const QJsonObject &response);
    void hookOffPressed(const QJsonObject &response);
    void httpServerSettingChanged(const QJsonObject &response);
    void httpServerStateChanged(const QJsonObject &response);
    void imageAddedToCachingQueue(const QJsonObject &response);
    void imageRemovedFromCachingQueue(const QJsonObject &response);
    void incomingChatMessage(const QJsonObject &response);
    void incomingFileRequestAccepted(const QJsonObject &response);
    void incomingFileRequestDownloadingProgress(const QJsonObject &response);
    void incomingFileRequestRejected(const QJsonObject &response);
    void incomingGroupChatMessage(const QJsonObject &response);
    void incomingPodiumInvitationRemoved(const QJsonObject &response);
    void incomingRequestCameraControlAccepted(const QJsonObject &response);
    void incomingRequestCameraControlRejected(const QJsonObject &response);
    void incomingRequestToPodiumAnswered(const QJsonObject &response);
    void inviteReceived(const QJsonObject &response);
    void inviteRequestSent(const QJsonObject &response);
    void inviteSent(const QJsonObject &response);
    void joinToConferenceLinkReceived(const QJsonObject &response);
    void lastCallsViewed(const QJsonObject &response);
    void licenseActivation(const QJsonObject &response);
    void licenseStatusChanged(const QJsonObject &response);
    void login(const QJsonObject &response);
    void logoImageChanged(const QJsonObject &response);
    void logout(const QJsonObject &response);
    void micStateChangedByConferenceOwner(const QJsonObject &response);
    void monitorsInfoUpdated(const QJsonObject &response);
    void myEvent(const QJsonObject &response);
    void mySlideShowStarted(const QJsonObject &response);
    void mySlideShowStopped(const QJsonObject &response);
    void mySlideShowTitleChanged(const QJsonObject &response);
    void NDIDeviceCreated(const QJsonObject &response);
    void NDIDeviceDeleted(const QJsonObject &response);
    void NDIStateChanged(const QJsonObject &response);
    void newParticipantInConference(const QJsonObject &response);
    void outgoingBitrateChanged(const QJsonObject &response);
    void outgoingFileRequestSent(const QJsonObject &response);
    void outgoingFileRequestSentToConference(const QJsonObject &response);
    void outgoingFileRequestUploadingProgress(const QJsonObject &response);
    void outgoingRequestCameraControlAccepted(const QJsonObject &response);
    void outgoingRequestCameraControlRejected(const QJsonObject &response);
    void outputSelfVideoRotateAngleChanged(const QJsonObject &response);
    void participantLeftConference(const QJsonObject &response);
    void peerAccepted(const QJsonObject &response);
    void propertiesUpdated(const QJsonObject &response);
    void ptzControlsChanged(const QJsonObject &response);
    void realtimeManagmentUrlAvailabilityChanged(const QJsonObject &response);
    void receivedFileRequest(const QJsonObject &response);
    void receiversInfoUpdated(const QJsonObject &response);
    void recordRequest(const QJsonObject &response);
    void recordRequestReply(const QJsonObject &response);
    void rejectReceived(const QJsonObject &response);
    void rejectSent(const QJsonObject &response);
    void remarkCountDown(const QJsonObject &response);
    void remotelyControlledCameraNotAvailableAnymore(const QJsonObject &response);
    void requestCameraControlReceived(const QJsonObject &response);
    void requestCameraControlSent(const QJsonObject &response);
    void requestInviteReceived(const QJsonObject &response);
    void roleEventOccured(const QJsonObject &response);
    void serverConnected(const QJsonObject &response);
    void serverDisconnected(const QJsonObject &response);
    void settingsChanged(const QJsonObject &response);
    void showCurrentUserWidget(const QJsonObject &response);
    void showIncomingRequestWidget(const QJsonObject &response);
    void showInfoConnect(const QJsonObject &response);
    void showLogo(const QJsonObject &response);
    void showTime(const QJsonObject &response);
    void showUpcomingMeetings(const QJsonObject &response);
    void slideAdded(const QJsonObject &response);
    void slideCached(const QJsonObject &response);
    void slideCachingStarted(const QJsonObject &response);
    void slidePositionChanged(const QJsonObject &response);
    void slideRemoved(const QJsonObject &response);
    void slideShowAvailabilityChanged(const QJsonObject &response);
    void slideShowCleared(const QJsonObject &response);
    void slidesSorted(const QJsonObject &response);
    void slideUploaded(const QJsonObject &response);
    void stopCalling(const QJsonObject &response);
    void systemRatingUpdated(const QJsonObject &response);
    void tariffRestrictionsChanged(const QJsonObject &response);
    void testAudioCapturerLevel(const QJsonObject &response);
    void testAudioCapturerStateChanged(const QJsonObject &response);
    void toneDial(const QJsonObject &response);
    void updateAvatar(const QJsonObject &response);
    void updateCameraInfo(const QJsonObject &response);
    void updateFailed(const QJsonObject &response);
    void userRecordingMeStatusChanged(const QJsonObject &response);
    void usersAddedToGroups(const QJsonObject &response);
    void usersRemovedFromGroups(const QJsonObject &response);
    void usersStatusesChanged(const QJsonObject &response);
    void videoCapturerMute(const QJsonObject &response);
    void videoMatrixChanged(const QJsonObject &response);
    void videoSlotMovedToMonitor(const QJsonObject &response);
    void videoSlotRemovedFromMonitor(const QJsonObject &response);
    void webManagerUrlChanged(const QJsonObject &response);
    void windowStateChanged(const QJsonObject &response);
};

#endif // CEVENTS_H

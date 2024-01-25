#ifndef TC_EVENTS_H
#define TC_EVENTS_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>

class TC_VideoSdkWrapper;


class TC_Events : public QObject
{
    Q_OBJECT

public:
    explicit TC_Events(TC_VideoSdkWrapper* videoSdkWrapper, QObject* parent = nullptr);
    TC_Events() = delete;
    TC_Events(const TC_Events& other) = delete;
    TC_Events& operator=(const TC_Events& other) = delete;
    TC_Events(TC_Events&& other) = delete;
    TC_Events& operator=(TC_Events&& other) = delete;
    virtual ~TC_Events() override;

    Q_SIGNAL void unsupportedEvent(const QString& eventName, const QJsonObject& eventJsonObj);
    Q_SIGNAL void NDIDeviceCreated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void NDIDeviceDeleted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void NDIStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void abReceivedAfterLogin(const QJsonObject& eventJsonObj);
    Q_SIGNAL void allSlidesCachingStopped(const QJsonObject& eventJsonObj);
    Q_SIGNAL void allSlidesRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void appSndDevChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void appStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void audioCapturerMute(const QJsonObject& eventJsonObj);
    Q_SIGNAL void audioDelayDetectorTestStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void audioRendererMute(const QJsonObject& eventJsonObj);
    Q_SIGNAL void authorizationNeeded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void authorizationParametersChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void availableServersListLoaded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void backgroundImageChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void blurChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void broadcastPictureStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void broadcastSelfieChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void callHistoryCleared(const QJsonObject& eventJsonObj);
    Q_SIGNAL void cameraStateChangedByConferenceOwner(const QJsonObject& eventJsonObj);
    Q_SIGNAL void chatMessageSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void chatRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void comPortChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void commandReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void commandSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void conferenceCreated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void conferenceDeleted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void conferenceList(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactBlocked(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactUnblocked(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactsAdded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactsDeleted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactsRenamed(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contactsSearched(const QJsonObject& eventJsonObj);
    Q_SIGNAL void contentSharingStoppedByConferenceLeader(const QJsonObject& eventJsonObj);
    Q_SIGNAL void cropChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void currentSlideIndexChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void currentUserDisplayNameChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void currentUserProfileUrlChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void customLogoUsageChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void dataDeleted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void dataSaved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void detailsInfo(const QJsonObject& eventJsonObj);
    Q_SIGNAL void deviceModesDone(const QJsonObject& eventJsonObj);
    Q_SIGNAL void deviceStatusReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void dsStarted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void dsStopped(const QJsonObject& eventJsonObj);
    Q_SIGNAL void enableAudioReceivingChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void enableVideoReceivingChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void extraVideoFlowNotify(const QJsonObject& eventJsonObj);
    Q_SIGNAL void fileDeletedFromFileTransferHistory(const QJsonObject& eventJsonObj);
    Q_SIGNAL void fileRequestStatusChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void fileTransferAvailabilityChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void fileTransferHistoryCleared(const QJsonObject& eventJsonObj);
    Q_SIGNAL void groupChatMessageSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void groupsAdded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void groupsRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void groupsRenamed(const QJsonObject& eventJsonObj);
    Q_SIGNAL void hardwareChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void httpServerSettingChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void httpServerStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void imageAddedToCachingQueue(const QJsonObject& eventJsonObj);
    Q_SIGNAL void imageRemovedFromCachingQueue(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingChatMessage(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingFileRequestAccepted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingFileRequestDownloadingProgress(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingFileRequestRejected(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingGroupChatMessage(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingPodiumInvitationRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingRequestCameraControlAccepted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingRequestCameraControlRejected(const QJsonObject& eventJsonObj);
    Q_SIGNAL void incomingRequestToPodiumAnswered(const QJsonObject& eventJsonObj);
    Q_SIGNAL void inviteReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void inviteRequestSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void inviteSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void joinToConferenceLinkReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void lastCallsViewed(const QJsonObject& eventJsonObj);
    Q_SIGNAL void licenseActivation(const QJsonObject& eventJsonObj);
    Q_SIGNAL void licenseStatusChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void login(const QJsonObject& eventJsonObj);
    Q_SIGNAL void logoImageChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void logout(const QJsonObject& eventJsonObj);
    Q_SIGNAL void micStateChangedByConferenceOwner(const QJsonObject& eventJsonObj);
    Q_SIGNAL void monitorsInfoUpdated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void myEvent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void mySlideShowStarted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void mySlideShowStopped(const QJsonObject& eventJsonObj);
    Q_SIGNAL void mySlideShowTitleChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void myStateInWaitingRoomChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void newParticipantInConference(const QJsonObject& eventJsonObj);
    Q_SIGNAL void noiseSuppressionChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingBitrateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingFileRequestSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingFileRequestSentToConference(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingFileRequestUploadingProgress(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingRequestCameraControlAccepted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outgoingRequestCameraControlRejected(const QJsonObject& eventJsonObj);
    Q_SIGNAL void outputSelfVideoRotateAngleChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void participantLeftConference(const QJsonObject& eventJsonObj);
    Q_SIGNAL void participantPresenceInWaitingRoomChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void peerAccepted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void propertiesUpdated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void ptzControlsChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void realtimeManagmentUrlChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void receivedFileRequest(const QJsonObject& eventJsonObj);
    Q_SIGNAL void receiversInfoUpdated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void recordRequest(const QJsonObject& eventJsonObj);
    Q_SIGNAL void recordRequestReply(const QJsonObject& eventJsonObj);
    Q_SIGNAL void rejectReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void rejectSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void remarkCountDown(const QJsonObject& eventJsonObj);
    Q_SIGNAL void remotelyControlledCameraNotAvailableAnymore(const QJsonObject& eventJsonObj);
    Q_SIGNAL void replaceBackgroundChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void requestCameraControlReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void requestCameraControlSent(const QJsonObject& eventJsonObj);
    Q_SIGNAL void requestInviteReceived(const QJsonObject& eventJsonObj);
    Q_SIGNAL void roleEventOccured(const QJsonObject& eventJsonObj);
    Q_SIGNAL void serverConnected(const QJsonObject& eventJsonObj);
    Q_SIGNAL void serverDisconnected(const QJsonObject& eventJsonObj);
    Q_SIGNAL void settingsChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showCurrentUserWidget(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showIncomingRequestWidget(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showInfoConnect(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showLogo(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showTime(const QJsonObject& eventJsonObj);
    Q_SIGNAL void showUpcomingMeetings(const QJsonObject& eventJsonObj);
    Q_SIGNAL void sleepModeChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideAdded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideCached(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideCachingStarted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slidePositionChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideShowAvailabilityChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideShowCleared(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slideUploaded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slidesChunkSorted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void slidesSorted(const QJsonObject& eventJsonObj);
    Q_SIGNAL void smartMeetingModeChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void stopCalling(const QJsonObject& eventJsonObj);
    Q_SIGNAL void systemRatingUpdated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void tariffRestrictionsChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void testAudioCapturerLevel(const QJsonObject& eventJsonObj);
    Q_SIGNAL void testAudioCapturerStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void toneDial(const QJsonObject& eventJsonObj);
    Q_SIGNAL void updateAvatar(const QJsonObject& eventJsonObj);
    Q_SIGNAL void updateCameraInfo(const QJsonObject& eventJsonObj);
    Q_SIGNAL void userPinEventOccured(const QJsonObject& eventJsonObj);
    Q_SIGNAL void userRecordingMeStatusChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void usersAddedToGroups(const QJsonObject& eventJsonObj);
    Q_SIGNAL void usersRemovedFromGroups(const QJsonObject& eventJsonObj);
    Q_SIGNAL void usersStatusesChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoCapturerMute(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoCapturerPresetAdded(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoCapturerPresetApplied(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoCapturerPresetRemoved(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoCapturerPresetUpdated(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoMatrixChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoSlotMovedToMonitor(const QJsonObject& eventJsonObj);
    Q_SIGNAL void videoSlotRemovedFromMonitor(const QJsonObject& eventJsonObj);
    Q_SIGNAL void waitingRoomStateChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void webManagerUrlChanged(const QJsonObject& eventJsonObj);
    Q_SIGNAL void windowStateChanged(const QJsonObject& eventJsonObj);

protected:
    Q_SLOT void socketReceivedEvent(const QString& eventName, const QJsonObject& eventJsonObj);
};

#endif /* TC_EVENTS_H */

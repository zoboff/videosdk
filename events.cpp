#include "events.h"
#include "videosdk.h"
#include <qdebug.h>

CEvents::CEvents(VideoSDK *sdk)
{
    m_sdk = sdk;
    QObject::connect(m_sdk, SIGNAL(socketReceivedEvent(QString, QJsonObject)), this, SLOT(socketReceivedEvent(QString, QJsonObject)));
}

bool compare(const QString &str1, const QString &str2)
{
    return str1.compare(str2, Qt::CaseInsensitive) == 0;
}

void CEvents::socketReceivedEvent(const QString &name, const QJsonObject &json_obj)
{
    if(compare("abReceivedAfterLogin", name))
    {
        emit abReceivedAfterLogin(json_obj);
    }
    else if(compare("allSlidesCachingStopped", name))
    {
        emit allSlidesCachingStopped(json_obj);
    }
    else if(compare("allSlidesRemoved", name))
    {
        emit allSlidesRemoved(json_obj);
    }
    else if(compare("appSndDevChanged", name))
    {
        emit appSndDevChanged(json_obj);
    }
    else if(compare("appStateChanged", name))
    {
        emit appStateChanged(json_obj);
    }
    else if(compare("appUpdateAvailable", name))
    {
        emit appUpdateAvailable(json_obj);
    }
    else if(compare("audioCapturerMute", name))
    {
        emit audioCapturerMute(json_obj);
    }
    else if(compare("audioDelayDetectorTestStateChanged", name))
    {
        emit audioDelayDetectorTestStateChanged(json_obj);
    }
    else if(compare("audioRendererMute", name))
    {
        emit audioRendererMute(json_obj);
    }
    else if(compare("authorizationNeeded", name))
    {
        emit authorizationNeeded(json_obj);
    }
    else if(compare("availableServersListLoaded", name))
    {
        emit availableServersListLoaded(json_obj);
    }
    else if(compare("backgroundImageChanged", name))
    {
        emit backgroundImageChanged(json_obj);
    }
    else if(compare("blurChanged", name))
    {
        emit blurChanged(json_obj);
    }
    else if(compare("broadcastPictureStateChanged", name))
    {
        emit broadcastPictureStateChanged(json_obj);
    }
    else if(compare("broadcastSelfieChanged", name))
    {
        emit broadcastSelfieChanged(json_obj);
    }
    else if(compare("callHistoryCleared", name))
    {
        emit callHistoryCleared(json_obj);
    }
    else if(compare("cameraStateChangedByConferenceOwner", name))
    {
        emit cameraStateChangedByConferenceOwner(json_obj);
    }
    else if(compare("chatMessageSent", name))
    {
        emit chatMessageSent(json_obj);
    }
    else if(compare("cmdChatClear", name))
    {
        emit cmdChatClear(json_obj);
    }
    else if(compare("commandReceived", name))
    {
        emit commandReceived(json_obj);
    }
    else if(compare("commandSent", name))
    {
        emit commandSent(json_obj);
    }
    else if(compare("conferenceCreated", name))
    {
        emit conferenceCreated(json_obj);
    }
    else if(compare("conferenceDeleted", name))
    {
        emit conferenceDeleted(json_obj);
    }
    else if(compare("conferenceList", name))
    {
        emit conferenceList(json_obj);
    }
    else if(compare("contactBlocked", name))
    {
        emit contactBlocked(json_obj);
    }
    else if(compare("contactsAdded", name))
    {
        emit contactsAdded(json_obj);
    }
    else if(compare("contactsDeleted", name))
    {
        emit contactsDeleted(json_obj);
    }
    else if(compare("contactsRenamed", name))
    {
        emit contactsRenamed(json_obj);
    }
    else if(compare("contactUnblocked", name))
    {
        emit contactUnblocked(json_obj);
    }
    else if(compare("cropChanged", name))
    {
        emit cropChanged(json_obj);
    }
    else if(compare("currentSlideIndexChanged", name))
    {
        emit currentSlideIndexChanged(json_obj);
    }
    else if(compare("currentUserDisplayNameChanged", name))
    {
        emit currentUserDisplayNameChanged(json_obj);
    }
    else if(compare("currentUserProfileUrlChanged", name))
    {
        emit currentUserProfileUrlChanged(json_obj);
    }
    else if(compare("customLogoUsageChanged", name))
    {
        emit customLogoUsageChanged(json_obj);
    }
    else if(compare("dataDeleted", name))
    {
        emit dataDeleted(json_obj);
    }
    else if(compare("dataSaved", name))
    {
        emit dataSaved(json_obj);
    }
    else if(compare("detailsInfo", name))
    {
        emit detailsInfo(json_obj);
    }
    else if(compare("deviceModesDone", name))
    {
        emit deviceModesDone(json_obj);
    }
    else if(compare("deviceStatusReceived", name))
    {
        emit deviceStatusReceived(json_obj);
    }
    else if(compare("downloadProgress", name))
    {
        emit downloadProgress(json_obj);
    }
    else if(compare("dsStarted", name))
    {
        emit dsStarted(json_obj);
    }
    else if(compare("dsStopped", name))
    {
        emit dsStopped(json_obj);
    }
    else if(compare("enableAudioReceivingChanged", name))
    {
        emit enableAudioReceivingChanged(json_obj);
    }
    else if(compare("enableVideoReceivingChanged", name))
    {
        emit enableVideoReceivingChanged(json_obj);
    }
    else if(compare("extraVideoFlowNotify", name))
    {
        emit extraVideoFlowNotify(json_obj);
    }
    else if(compare("fileAccepted", name))
    {
        emit fileAccepted(json_obj);
    }
    else if(compare("fileConferenceSent", name))
    {
        emit fileConferenceSent(json_obj);
    }
    else if(compare("fileDownloadingProgress", name))
    {
        emit fileDownloadingProgress(json_obj);
    }
    else if(compare("fileRejected", name))
    {
        emit fileRejected(json_obj);
    }
    else if(compare("fileSent", name))
    {
        emit fileSent(json_obj);
    }
    else if(compare("fileStatus", name))
    {
        emit fileStatus(json_obj);
    }
    else if(compare("fileTransferAvailable", name))
    {
        emit fileTransferAvailable(json_obj);
    }
    else if(compare("fileTransferCleared", name))
    {
        emit fileTransferCleared(json_obj);
    }
    else if(compare("fileTransferFileDeleted", name))
    {
        emit fileTransferFileDeleted(json_obj);
    }
    else if(compare("fileTransferPinChanged", name))
    {
        emit fileTransferPinChanged(json_obj);
    }
    else if(compare("fileUploadingProgress", name))
    {
        emit fileUploadingProgress(json_obj);
    }
    else if(compare("groupChatMessageSent", name))
    {
        emit groupChatMessageSent(json_obj);
    }
    else if(compare("groupsAdded", name))
    {
        emit groupsAdded(json_obj);
    }
    else if(compare("groupsRemoved", name))
    {
        emit groupsRemoved(json_obj);
    }
    else if(compare("groupsRenamed", name))
    {
        emit groupsRenamed(json_obj);
    }
    else if(compare("hangUpPressed", name))
    {
        emit hangUpPressed(json_obj);
    }
    else if(compare("hardwareChanged", name))
    {
        emit hardwareChanged(json_obj);
    }
    else if(compare("hookOffPressed", name))
    {
        emit hookOffPressed(json_obj);
    }
    else if(compare("httpServerSettingChanged", name))
    {
        emit httpServerSettingChanged(json_obj);
    }
    else if(compare("httpServerStateChanged", name))
    {
        emit httpServerStateChanged(json_obj);
    }
    else if(compare("imageAddedToCachingQueue", name))
    {
        emit imageAddedToCachingQueue(json_obj);
    }
    else if(compare("imageRemovedFromCachingQueue", name))
    {
        emit imageRemovedFromCachingQueue(json_obj);
    }
    else if(compare("incomingChatMessage", name))
    {
        emit incomingChatMessage(json_obj);
    }
    else if(compare("incomingGroupChatMessage", name))
    {
        emit incomingGroupChatMessage(json_obj);
    }
    else if(compare("incomingPodiumInvitationRemoved", name))
    {
        emit incomingPodiumInvitationRemoved(json_obj);
    }
    else if(compare("incomingRequestCameraControlAccepted", name))
    {
        emit incomingRequestCameraControlAccepted(json_obj);
    }
    else if(compare("incomingRequestCameraControlRejected", name))
    {
        emit incomingRequestCameraControlRejected(json_obj);
    }
    else if(compare("incomingRequestToPodiumAnswered", name))
    {
        emit incomingRequestToPodiumAnswered(json_obj);
    }
    else if(compare("inviteReceived", name))
    {
        emit inviteReceived(json_obj);
    }
    else if(compare("inviteRequestSent", name))
    {
        emit inviteRequestSent(json_obj);
    }
    else if(compare("inviteSent", name))
    {
        emit inviteSent(json_obj);
    }
    else if(compare("joinToConferenceLinkReceived", name))
    {
        emit joinToConferenceLinkReceived(json_obj);
    }
    else if(compare("lastCallsViewed", name))
    {
        emit lastCallsViewed(json_obj);
    }
    else if(compare("licenseActivation", name))
    {
        emit licenseActivation(json_obj);
    }
    else if(compare("licenseStatusChanged", name))
    {
        emit licenseStatusChanged(json_obj);
    }
    else if(compare("login", name))
    {
        emit login(json_obj);
    }
    else if(compare("logoImageChanged", name))
    {
        emit logoImageChanged(json_obj);
    }
    else if(compare("logout", name))
    {
        emit logout(json_obj);
    }
    else if(compare("micStateChangedByConferenceOwner", name))
    {
        emit micStateChangedByConferenceOwner(json_obj);
    }
    else if(compare("monitorsInfoUpdated", name))
    {
        emit monitorsInfoUpdated(json_obj);
    }
    else if(compare("myEvent", name))
    {
        emit myEvent(json_obj);
    }
    else if(compare("mySlideShowStarted", name))
    {
        emit mySlideShowStarted(json_obj);
    }
    else if(compare("mySlideShowStopped", name))
    {
        emit mySlideShowStopped(json_obj);
    }
    else if(compare("mySlideShowTitleChanged", name))
    {
        emit mySlideShowTitleChanged(json_obj);
    }
    else if(compare("NDIDeviceCreated", name))
    {
        emit NDIDeviceCreated(json_obj);
    }
    else if(compare("NDIDeviceDeleted", name))
    {
        emit NDIDeviceDeleted(json_obj);
    }
    else if(compare("NDIStateChanged", name))
    {
        emit NDIStateChanged(json_obj);
    }
    else if(compare("newParticipantInConference", name))
    {
        emit newParticipantInConference(json_obj);
    }
    else if(compare("outgoingBitrateChanged", name))
    {
        emit outgoingBitrateChanged(json_obj);
    }
    else if(compare("outgoingRequestCameraControlAccepted", name))
    {
        emit outgoingRequestCameraControlAccepted(json_obj);
    }
    else if(compare("outgoingRequestCameraControlRejected", name))
    {
        emit outgoingRequestCameraControlRejected(json_obj);
    }
    else if(compare("outputSelfVideoRotateAngleChanged", name))
    {
        emit outputSelfVideoRotateAngleChanged(json_obj);
    }
    else if(compare("participantLeftConference", name))
    {
        emit participantLeftConference(json_obj);
    }
    else if(compare("peerAccepted", name))
    {
        emit peerAccepted(json_obj);
    }
    else if(compare("propertiesUpdated", name))
    {
        emit propertiesUpdated(json_obj);
    }
    else if(compare("ptzControlsChanged", name))
    {
        emit ptzControlsChanged(json_obj);
    }
    else if(compare("realtimeManagmentUrlAvailabilityChanged", name))
    {
        emit realtimeManagmentUrlAvailabilityChanged(json_obj);
    }
    else if(compare("receivedFileRequest", name))
    {
        emit receivedFileRequest(json_obj);
    }
    else if(compare("receiversInfoUpdated", name))
    {
        emit receiversInfoUpdated(json_obj);
    }
    else if(compare("recordRequest", name))
    {
        emit recordRequest(json_obj);
    }
    else if(compare("recordRequestReply", name))
    {
        emit recordRequestReply(json_obj);
    }
    else if(compare("rejectReceived", name))
    {
        emit rejectReceived(json_obj);
    }
    else if(compare("rejectSent", name))
    {
        emit rejectSent(json_obj);
    }
    else if(compare("remarkCountDown", name))
    {
        emit remarkCountDown(json_obj);
    }
    else if(compare("remotelyControlledCameraNotAvailableAnymore", name))
    {
        emit remotelyControlledCameraNotAvailableAnymore(json_obj);
    }
    else if(compare("requestCameraControlReceived", name))
    {
        emit requestCameraControlReceived(json_obj);
    }
    else if(compare("requestCameraControlSent", name))
    {
        emit requestCameraControlSent(json_obj);
    }
    else if(compare("requestInviteReceived", name))
    {
        emit requestInviteReceived(json_obj);
    }
    else if(compare("roleEventOccured", name))
    {
        emit roleEventOccured(json_obj);
    }
    else if(compare("serverConnected", name))
    {
        emit serverConnected(json_obj);
    }
    else if(compare("serverDisconnected", name))
    {
        emit serverDisconnected(json_obj);
    }
    else if(compare("settingsChanged", name))
    {
        emit settingsChanged(json_obj);
    }
    else if(compare("showCurrentUserWidget", name))
    {
        emit showCurrentUserWidget(json_obj);
    }
    else if(compare("showIncomingRequestWidget", name))
    {
        emit showIncomingRequestWidget(json_obj);
    }
    else if(compare("showInfoConnect", name))
    {
        emit showInfoConnect(json_obj);
    }
    else if(compare("showLogo", name))
    {
        emit showLogo(json_obj);
    }
    else if(compare("showTime", name))
    {
        emit showTime(json_obj);
    }
    else if(compare("showUpcomingMeetings", name))
    {
        emit showUpcomingMeetings(json_obj);
    }
    else if(compare("slideAdded", name))
    {
        emit slideAdded(json_obj);
    }
    else if(compare("slideCached", name))
    {
        emit slideCached(json_obj);
    }
    else if(compare("slideCachingStarted", name))
    {
        emit slideCachingStarted(json_obj);
    }
    else if(compare("slidePositionChanged", name))
    {
        emit slidePositionChanged(json_obj);
    }
    else if(compare("slideRemoved", name))
    {
        emit slideRemoved(json_obj);
    }
    else if(compare("slideShowAvailabilityChanged", name))
    {
        emit slideShowAvailabilityChanged(json_obj);
    }
    else if(compare("slideShowCleared", name))
    {
        emit slideShowCleared(json_obj);
    }
    else if(compare("slidesSorted", name))
    {
        emit slidesSorted(json_obj);
    }
    else if(compare("slideUploaded", name))
    {
        emit slideUploaded(json_obj);
    }
    else if(compare("stopCalling", name))
    {
        emit stopCalling(json_obj);
    }
    else if(compare("systemRatingUpdated", name))
    {
        emit systemRatingUpdated(json_obj);
    }
    else if(compare("tariffRestrictionsChanged", name))
    {
        emit tariffRestrictionsChanged(json_obj);
    }
    else if(compare("testAudioCapturerLevel", name))
    {
        emit testAudioCapturerLevel(json_obj);
    }
    else if(compare("testAudioCapturerStateChanged", name))
    {
        emit testAudioCapturerStateChanged(json_obj);
    }
    else if(compare("toneDial", name))
    {
        emit toneDial(json_obj);
    }
    else if(compare("updateAvatar", name))
    {
        emit updateAvatar(json_obj);
    }
    else if(compare("updateCameraInfo", name))
    {
        emit updateCameraInfo(json_obj);
    }
    else if(compare("updateFailed", name))
    {
        emit updateFailed(json_obj);
    }
    else if(compare("userRecordingMeStatusChanged", name))
    {
        emit userRecordingMeStatusChanged(json_obj);
    }
    else if(compare("usersAddedToGroups", name))
    {
        emit usersAddedToGroups(json_obj);
    }
    else if(compare("usersRemovedFromGroups", name))
    {
        emit usersRemovedFromGroups(json_obj);
    }
    else if(compare("usersStatusesChanged", name))
    {
        emit usersStatusesChanged(json_obj);
    }
    else if(compare("videoCapturerMute", name))
    {
        emit videoCapturerMute(json_obj);
    }
    else if(compare("videoMatrixChanged", name))
    {
        emit videoMatrixChanged(json_obj);
    }
    else if(compare("videoSlotMovedToMonitor", name))
    {
        emit videoSlotMovedToMonitor(json_obj);
    }
    else if(compare("videoSlotRemovedFromMonitor", name))
    {
        emit videoSlotRemovedFromMonitor(json_obj);
    }
    else if(compare("webManagerUrlChanged", name))
    {
        emit webManagerUrlChanged(json_obj);
    }
    else if(compare("windowStateChanged", name))
    {
        emit windowStateChanged(json_obj);
    }
}

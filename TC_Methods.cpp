#include "TC_Methods.h"
#include "TC_VideoSdkWrapper.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>


TC_Methods::TC_Methods(TC_VideoSdkWrapper* videoSdkWrapper, QObject* parent)
    : QObject(parent)
    , m_videoSdkWrapper(videoSdkWrapper)
{

}

TC_Methods::~TC_Methods()
{

}

QString TC_Methods::createJsonCommand(const QString& method, const QVariantMap& params)
{
    QJsonObject json = QJsonObject::fromVariantMap(params);
    json.insert("method", method);

    QJsonDocument doc(json);
    return QString(doc.toJson(QJsonDocument::Compact));
}

void TC_Methods::call(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("call", { {"peerId", peerId} }));
}

void TC_Methods::accept()
{
    m_videoSdkWrapper->send(createJsonCommand("accept"));
}

void TC_Methods::hangUp(bool forAll)
{
    m_videoSdkWrapper->send(createJsonCommand("hangUp", { {"forAll", forAll} }));
}

void TC_Methods::login(const QString& callId, const QString& password, bool encryptPassword)
{
    m_videoSdkWrapper->send(createJsonCommand("login", { {"login", callId}, {"password", password}, {"encryptPassword", encryptPassword} }));
}

void TC_Methods::logout()
{
    m_videoSdkWrapper->send(createJsonCommand("logout"));
}

void TC_Methods::connectToServer(const QString& server, int port)
{
    m_videoSdkWrapper->send(createJsonCommand("connectToServer", { {"server", server}, {"port", port} }));
}

void TC_Methods::sendCommand(const QString& peerId, const QString& command)
{
    m_videoSdkWrapper->send(createJsonCommand("sendCommand", { {"peerId", peerId}, {"command", command} }));
}

void TC_Methods::reject()
{
    m_videoSdkWrapper->send(createJsonCommand("reject"));
}

void TC_Methods::rejectPeer(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("rejectPeer", { {"peerId", peerId} }));
}

void TC_Methods::acceptPeer(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("acceptPeer", { {"peerId", peerId} }));
}

void TC_Methods::createConference(const QString& title
                                  , const QString& confType
                                  , bool autoAccept
                                  , bool useWaitingRoom
                                  , bool muteCamOnJoin
                                  , bool muteMicOnJoin
                                  , const QStringList& inviteList)
{
    QVariantMap params = {
        {"title", title},
        {"confType", confType},
        {"autoAccept", autoAccept},
        {"useWaitingRoom", useWaitingRoom},
        {"muteCamOnJoin", muteCamOnJoin},
        {"muteMicOnJoin", muteMicOnJoin}
    };
    if (!inviteList.isEmpty())
    {
        params.insert("inviteList", QJsonArray::fromStringList(inviteList));
    }
    m_videoSdkWrapper->send(createJsonCommand("createConference", params));
}

void TC_Methods::getHardware()
{
    m_videoSdkWrapper->send(createJsonCommand("getHardware"));
}

void TC_Methods::acceptInvitationToPodium()
{
    m_videoSdkWrapper->send(createJsonCommand("acceptInvitationToPodium"));
}

void TC_Methods::acceptRequestCameraControl(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("acceptRequestCameraControl", { {"callId", callId} }));
}

void TC_Methods::acceptRequestToPodium(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("acceptRequestToPodium", { {"peerId", peerId} }));
}

void TC_Methods::addSlide(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("addSlide", { {"fileId", fileId} }));
}

void TC_Methods::addToAbook(const QString& peerId, const QString& peerDn)
{
    m_videoSdkWrapper->send(createJsonCommand("addToAbook", { {"peerId", peerId}, {"peerDn", peerDn} }));
}

void TC_Methods::addToGroup(int groupId, const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("addToGroup", { {"groupId", groupId}, {"peerId", peerId} }));
}

void TC_Methods::allowRecord(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("allowRecord", { {"peerId", peerId} }));
}

void TC_Methods::block(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("block", { {"peerId", peerId} }));
}

void TC_Methods::changeCurrentMonitor(int monitorIndex)
{
    m_videoSdkWrapper->send(createJsonCommand("changeCurrentMonitor", { {"monitorIndex", monitorIndex} }));
}

void TC_Methods::changeVideoMatrixType(int matrixType)
{
    m_videoSdkWrapper->send(createJsonCommand("changeVideoMatrixType", { {"matrixType", matrixType} }));
}

void TC_Methods::changeWindowState(int windowState, bool stayOnTop)
{
    m_videoSdkWrapper->send(createJsonCommand("changeWindowState", { {"windowState", windowState}, {"stayOnTop", stayOnTop} }));
}

void TC_Methods::chatClear(const QString& id)
{
    m_videoSdkWrapper->send(createJsonCommand("chatClear", { {"id", id} }));
}

void TC_Methods::clearCallHistory()
{
    m_videoSdkWrapper->send(createJsonCommand("clearCallHistory"));
}

void TC_Methods::clearTokens()
{
    m_videoSdkWrapper->send(createJsonCommand("clearTokens"));
}

void TC_Methods::connectToService(const QString& domain)
{
    QVariantMap params;
    if (!domain.isEmpty())
    {
        params["domain"] = domain;
    }
    m_videoSdkWrapper->send(createJsonCommand("connectToService", params));
}

void TC_Methods::createGroup(const QString& name)
{
    m_videoSdkWrapper->send(createJsonCommand("createGroup", { {"name", name} }));
}

void TC_Methods::createNDIDevice(const QString& deviceId)
{
    m_videoSdkWrapper->send(createJsonCommand("createNDIDevice", { {"deviceId", deviceId} }));
}

void TC_Methods::deleteData(const QString& containerName)
{
    m_videoSdkWrapper->send(createJsonCommand("deleteData", { {"containerName", containerName} }));
}

void TC_Methods::deleteFileTransferFile(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("deleteFileTransferFile", { {"fileId", fileId} }));
}

void TC_Methods::deleteNDIDevice(const QString& deviceId)
{
    m_videoSdkWrapper->send(createJsonCommand("deleteNDIDevice", { {"deviceId", deviceId} }));
}

void TC_Methods::denyRecord(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("denyRecord", { {"peerId", peerId} }));
}

void TC_Methods::enableAudioReceiving(const QString& peerId, bool enable)
{
    m_videoSdkWrapper->send(createJsonCommand("enableAudioReceiving", { {"peerId", peerId}, {"enable", enable} }));
}

void TC_Methods::enableVideoReceiving(const QString& peerId, bool enable)
{
    m_videoSdkWrapper->send(createJsonCommand("enableVideoReceiving", { {"peerId", peerId}, {"enable", enable} }));
}

void TC_Methods::expandCallToMulti(const QString& title, const QStringList& inviteList)
{
    QVariantMap params = { {"title", title} };

    if (!inviteList.isEmpty())
    {
        QVariantList invites;
        for (const QString& invite : inviteList)
        {
            invites.append(invite);
        }
        params.insert("inviteList", invites);
    }

    m_videoSdkWrapper->send(createJsonCommand("expandCallToMulti", params));
}

void TC_Methods::fireMyEvent(const QString& data)
{
    m_videoSdkWrapper->send(createJsonCommand("fireMyEvent", { {"data", data} }));
}

void TC_Methods::getAbook()
{
    m_videoSdkWrapper->send(createJsonCommand("getAbook"));
}

void TC_Methods::getAllUserContainersNames()
{
    m_videoSdkWrapper->send(createJsonCommand("getAllUserContainersNames"));
}

void TC_Methods::getAppSndDev()
{
    m_videoSdkWrapper->send(createJsonCommand("getAppSndDev"));
}

void TC_Methods::getAppState()
{
    m_videoSdkWrapper->send(createJsonCommand("getAppState"));
}

void TC_Methods::activateLicense(const QString& key)
{
    m_videoSdkWrapper->send(createJsonCommand("activateLicense", { {"key", key} }));
}

void TC_Methods::auth(const QString& role, const QString& type, const QString& credentials)
{
    m_videoSdkWrapper->send(createJsonCommand("auth", { {"role", role}, {"type", type}, {"credentials", credentials} }));
}

void TC_Methods::getAudioDelayDetectorInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getAudioDelayDetectorInfo"));
}

void TC_Methods::getAudioMute()
{
    m_videoSdkWrapper->send(createJsonCommand("getAudioMute"));
}

void TC_Methods::getAudioReceivingLevel(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("getAudioReceivingLevel", { {"peerId", peerId} }));
}

void TC_Methods::getAuthInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getAuthInfo"));
}

void TC_Methods::getAvailableServersList()
{
    m_videoSdkWrapper->send(createJsonCommand("getAvailableServersList"));
}

void TC_Methods::getBackground()
{
    m_videoSdkWrapper->send(createJsonCommand("getBackground"));
}

void TC_Methods::getBanList()
{
    m_videoSdkWrapper->send(createJsonCommand("getBanList"));
}

void TC_Methods::getBroadcastPicture()
{
    m_videoSdkWrapper->send(createJsonCommand("getBroadcastPicture"));
}

void TC_Methods::getBroadcastSelfie()
{
    m_videoSdkWrapper->send(createJsonCommand("getBroadcastSelfie"));
}

void TC_Methods::getCallHistory(int count)
{
    m_videoSdkWrapper->send(createJsonCommand("getCallHistory", { {"count", count} }));
}

void TC_Methods::getChatLastMessages(const QString& id, int beginNumber, int count)
{
    m_videoSdkWrapper->send(createJsonCommand("getChatLastMessages", { {"id", id}, {"beginNumber", beginNumber}, {"count", count} }));
}

void TC_Methods::getConferenceParticipants()
{
    m_videoSdkWrapper->send(createJsonCommand("getConferenceParticipants"));
}

void TC_Methods::getConferences()
{
    m_videoSdkWrapper->send(createJsonCommand("getConferences"));
}

void TC_Methods::getConnected()
{
    m_videoSdkWrapper->send(createJsonCommand("getConnected"));
}

void TC_Methods::getContactDetails(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("getContactDetails", { {"peerId", peerId} }));
}

void TC_Methods::getCreatedNDIDevices()
{
    m_videoSdkWrapper->send(createJsonCommand("getCreatedNDIDevices"));
}

void TC_Methods::getCrop()
{
    m_videoSdkWrapper->send(createJsonCommand("getCrop"));
}

void TC_Methods::getCurrentUserProfileUrl()
{
    m_videoSdkWrapper->send(createJsonCommand("getCurrentUserProfileUrl"));
}

void TC_Methods::getDisplayNameById(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("getDisplayNameById", { {"peerId", peerId} }));
}

void TC_Methods::getFileList()
{
    m_videoSdkWrapper->send(createJsonCommand("getFileList"));
}

void TC_Methods::getFileTransferAvailability()
{
    m_videoSdkWrapper->send(createJsonCommand("getFileTransferAvailability"));
}

void TC_Methods::getGroups()
{
    m_videoSdkWrapper->send(createJsonCommand("getGroups"));
}

void TC_Methods::getHardwareKey()
{
    m_videoSdkWrapper->send(createJsonCommand("getHardwareKey"));
}

void TC_Methods::getHttpServerSettings()
{
    m_videoSdkWrapper->send(createJsonCommand("getHttpServerSettings"));
}

void TC_Methods::getHttpServerState()
{
    m_videoSdkWrapper->send(createJsonCommand("getHttpServerState"));
}

void TC_Methods::getIncomingCameraControlRequests()
{
    m_videoSdkWrapper->send(createJsonCommand("getIncomingCameraControlRequests"));
}

void TC_Methods::getInfoWidgetsState()
{
    m_videoSdkWrapper->send(createJsonCommand("getInfoWidgetsState"));
}

void TC_Methods::getLastCallsViewTime()
{
    m_videoSdkWrapper->send(createJsonCommand("getLastCallsViewTime"));
}

void TC_Methods::getLastSelectedConference()
{
    m_videoSdkWrapper->send(createJsonCommand("getLastSelectedConference"));
}

void TC_Methods::getLastUsedServersList(int count)
{
    m_videoSdkWrapper->send(createJsonCommand("getLastUsedServersList", { {"count", count} }));
}

void TC_Methods::getLicenseServerStatus()
{
    m_videoSdkWrapper->send(createJsonCommand("getLicenseServerStatus"));
}

void TC_Methods::getLicenseType()
{
    m_videoSdkWrapper->send(createJsonCommand("getLicenseType"));
}

void TC_Methods::getListOfChats()
{
    m_videoSdkWrapper->send(createJsonCommand("getListOfChats"));
}

void TC_Methods::getLogin()
{
    m_videoSdkWrapper->send(createJsonCommand("getLogin"));
}

void TC_Methods::getLogo()
{
    m_videoSdkWrapper->send(createJsonCommand("getLogo"));
}

void TC_Methods::getMaxConfTitleLength()
{
    m_videoSdkWrapper->send(createJsonCommand("getMaxConfTitleLength"));
}

void TC_Methods::getMicMute()
{
    m_videoSdkWrapper->send(createJsonCommand("getMicMute"));
}

void TC_Methods::getModes()
{
    m_videoSdkWrapper->send(createJsonCommand("getModes"));
}

void TC_Methods::getMonitorsInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getMonitorsInfo"));
}

void TC_Methods::getNDIState()
{
    m_videoSdkWrapper->send(createJsonCommand("getNDIState"));
}

void TC_Methods::getOutgoingBitrate()
{
    m_videoSdkWrapper->send(createJsonCommand("getOutgoingBitrate"));
}

void TC_Methods::getOutgoingCameraControlRequests()
{
    m_videoSdkWrapper->send(createJsonCommand("getOutgoingCameraControlRequests"));
}

void TC_Methods::getOutputSelfVideoRotateAngle()
{
    m_videoSdkWrapper->send(createJsonCommand("getOutputSelfVideoRotateAngle"));
}

void TC_Methods::getProperties()
{
    m_videoSdkWrapper->send(createJsonCommand("getProperties"));
}

void TC_Methods::getPtzControls()
{
    m_videoSdkWrapper->send(createJsonCommand("getPtzControls"));
}

void TC_Methods::getRemotelyControlledCameras()
{
    m_videoSdkWrapper->send(createJsonCommand("getRemotelyControlledCameras"));
}

void TC_Methods::getRenderInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getRenderInfo"));
}

void TC_Methods::getScheduler()
{
    m_videoSdkWrapper->send(createJsonCommand("getScheduler"));
}

void TC_Methods::getServerDomain()
{
    m_videoSdkWrapper->send(createJsonCommand("getServerDomain"));
}

void TC_Methods::getSettings()
{
    m_videoSdkWrapper->send(createJsonCommand("getSettings"));
}

void TC_Methods::getSlideShowCache()
{
    m_videoSdkWrapper->send(createJsonCommand("getSlideShowCache"));
}

void TC_Methods::getSlideShowInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getSlideShowInfo"));
}

void TC_Methods::getSystemInfo()
{
    m_videoSdkWrapper->send(createJsonCommand("getSystemInfo"));
}

void TC_Methods::getTariffRestrictions()
{
    m_videoSdkWrapper->send(createJsonCommand("getTariffRestrictions"));
}

void TC_Methods::getTokenForHttpServer()
{
    m_videoSdkWrapper->send(createJsonCommand("getTokenForHttpServer"));
}

void TC_Methods::getTrueConfRoomProKey()
{
    m_videoSdkWrapper->send(createJsonCommand("getTrueConfRoomProKey"));
}

void TC_Methods::getVideoMatrix()
{
    m_videoSdkWrapper->send(createJsonCommand("getVideoMatrix"));
}

void TC_Methods::getVideoMute()
{
    m_videoSdkWrapper->send(createJsonCommand("getVideoMute"));
}

void TC_Methods::getWebManagerUrl()
{
    m_videoSdkWrapper->send(createJsonCommand("getWebManagerUrl"));
}

void TC_Methods::gotoPodium()
{
    m_videoSdkWrapper->send(createJsonCommand("gotoPodium"));
}

void TC_Methods::hideVideoSlot(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("hideVideoSlot", { {"callId", callId} }));
}

void TC_Methods::inviteToConference(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("inviteToConference", { {"peerId", peerId} }));
}

void TC_Methods::inviteToPodium(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("inviteToPodium", { {"peerId", peerId} }));
}

void TC_Methods::kickFromPodium(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("kickFromPodium", { {"peerId", peerId} }));
}

void TC_Methods::kickPeer(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("kickPeer", { {"peerId", peerId} }));
}

void TC_Methods::leavePodium()
{
    m_videoSdkWrapper->send(createJsonCommand("leavePodium"));
}

void TC_Methods::loadData(const QString& containerName)
{
    m_videoSdkWrapper->send(createJsonCommand("loadData", { {"containerName", containerName} }));
}

void TC_Methods::moveVideoSlotToMonitor(const QString& callId, int monitorIndex)
{
    m_videoSdkWrapper->send(createJsonCommand("moveVideoSlotToMonitor", { {"callId", callId}, {"monitorIndex", monitorIndex} }));
}

void TC_Methods::productRegistrationOffline(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("productRegistrationOffline", { {"fileId", fileId} }));
}

void TC_Methods::ptzDown()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzDown"));
}

void TC_Methods::ptzLeft()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzLeft"));
}

void TC_Methods::ptzRight()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzRight"));
}

void TC_Methods::ptzStop()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzStop"));
}

void TC_Methods::ptzUp()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzUp"));
}

void TC_Methods::ptzZoomDec()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzZoomDec"));
}

void TC_Methods::ptzZoomInc()
{
    m_videoSdkWrapper->send(createJsonCommand("ptzZoomInc"));
}

void TC_Methods::rebootSystem()
{
    m_videoSdkWrapper->send(createJsonCommand("rebootSystem"));
}

void TC_Methods::rejectInvitationToPodium()
{
    m_videoSdkWrapper->send(createJsonCommand("rejectInvitationToPodium"));
}

void TC_Methods::rejectRequestCameraControl(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("rejectRequestCameraControl", { {"callId", callId} }));
}

void TC_Methods::rejectRequestToPodium(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("rejectRequestToPodium", { {"peerId", peerId} }));
}

void TC_Methods::remotelyControlledCameraPtzDown(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzDown", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::remotelyControlledCameraPtzLeft(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzLeft", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::remotelyControlledCameraPtzRight(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzRight", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::remotelyControlledCameraPtzUp(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzUp", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::remotelyControlledCameraPtzZoomDec(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzZoomDec", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::remotelyControlledCameraPtzZoomInc(const QString& cameraOwnerCallId)
{
    m_videoSdkWrapper->send(createJsonCommand("remotelyControlledCameraPtzZoomInc", { {"cameraOwnerCallId", cameraOwnerCallId} }));
}

void TC_Methods::removeAllSlides(bool removeFromServer)
{
    m_videoSdkWrapper->send(createJsonCommand("removeAllSlides", { {"removeFromServer", removeFromServer} }));
}

void TC_Methods::removeFromAbook(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("removeFromAbook", { {"peerId", peerId} }));
}

void TC_Methods::removeFromGroup(int groupId, const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("removeFromGroup", { {"groupId", groupId}, {"peerId", peerId} }));
}

void TC_Methods::removeFromServersList(const QString& serverName)
{
    m_videoSdkWrapper->send(createJsonCommand("removeFromServersList", { {"serverName", serverName} }));
}

void TC_Methods::removeGroup(int groupId)
{
    m_videoSdkWrapper->send(createJsonCommand("removeGroup", { {"groupId", groupId} }));
}

void TC_Methods::removeImageFromCachingQueue(int groupId)
{
    m_videoSdkWrapper->send(createJsonCommand("removeImageFromCachingQueue", { {"groupId", groupId} }));
}

void TC_Methods::removeSlide(int idx, bool removeFromServer)
{
    m_videoSdkWrapper->send(createJsonCommand("removeSlide", { {"idx", idx}, {"removeFromServer", removeFromServer} }));
}

void TC_Methods::removeVideoSlotFromMonitor(int monitorIndex)
{
    m_videoSdkWrapper->send(createJsonCommand("removeVideoSlotFromMonitor", { {"monitorIndex", monitorIndex} }));
}

void TC_Methods::renameGroup(int groupId, const QString& newName)
{
    m_videoSdkWrapper->send(createJsonCommand("renameGroup", { {"groupId", groupId}, {"newName", newName} }));
}

void TC_Methods::renameInAbook(const QString& peerId, const QString& peerDn)
{
    m_videoSdkWrapper->send(createJsonCommand("renameInAbook", { {"peerId", peerId}, {"peerDn", peerDn} }));
}

void TC_Methods::requestParticipantCameraControl(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("requestParticipantCameraControl", { {"callId", callId} }));
}

void TC_Methods::restoreWindow()
{
    m_videoSdkWrapper->send(createJsonCommand("restoreWindow"));
}

void TC_Methods::saveData(const QString& containerName, const QString& data, const QString& flags)
{
    m_videoSdkWrapper->send(createJsonCommand("saveData", { {"containerName", containerName}, {"data", data}, {"flags", flags} }));
}

void TC_Methods::sendFile(int fileId, const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("sendFile", { {"fileId", fileId}, {"peerId", peerId} }));
}

void TC_Methods::sendGroupMessage(const QString& message)
{
    m_videoSdkWrapper->send(createJsonCommand("sendGroupMessage", { {"message", message} }));
}

void TC_Methods::sendMessage(const QString& peerId, const QString& message)
{
    m_videoSdkWrapper->send(createJsonCommand("sendMessage", { {"peerId", peerId}, {"message", message} }));
}

void TC_Methods::setAppSndDev(const QString& name, const QString& description)
{
    m_videoSdkWrapper->send(createJsonCommand("setAppSndDev", { {"name", name}, {"description", description} }));
}

void TC_Methods::setAudioCapturer(const QString& name, const QString& description)
{
    m_videoSdkWrapper->send(createJsonCommand("setAudioCapturer", { {"name", name}, {"description", description} }));
}

void TC_Methods::setAudioMute(bool mute)
{
    m_videoSdkWrapper->send(createJsonCommand("setAudioMute", { {"mute", mute} }));
}

void TC_Methods::setAudioReceivingLevel(const QString& peerId, int level)
{
    m_videoSdkWrapper->send(createJsonCommand("setAudioReceivingLevel", { {"peerId", peerId}, {"level", level} }));
}

void TC_Methods::setAudioRenderer(const QString& name, const QString& description)
{
    m_videoSdkWrapper->send(createJsonCommand("setAudioRenderer", { {"name", name}, {"description", description} }));
}

void TC_Methods::setAuthParams(const QString& userType, const QString& authType, const QString& authValue)
{
    QVariantMap params{ {"userType", userType}, {"authType", authType} };
    if (authType == "password")
    {
        params.insert("password", authValue);
    }
    m_videoSdkWrapper->send(createJsonCommand("setAuthParams", params));
}

void TC_Methods::setBackground(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("setBackground", { {"fileId", fileId} }));
}

void TC_Methods::setBroadcastSelfie(bool enabled, int fps)
{
    m_videoSdkWrapper->send(createJsonCommand("setBroadcastSelfie", { {"enabled", enabled}, {"fps", fps} }));
}

void TC_Methods::setCrop(bool enable)
{
    m_videoSdkWrapper->send(createJsonCommand("setCrop", { {"enable", enable} }));
}

void TC_Methods::setDefaultBackground()
{
    m_videoSdkWrapper->send(createJsonCommand("setDefaultBackground"));
}

void TC_Methods::setDefaultLogo()
{
    m_videoSdkWrapper->send(createJsonCommand("setDefaultLogo"));
}

void TC_Methods::setHttpServerSettings(const QMap<QString, QVariant>& settings)
{
    QVariantMap settingsMap;
    for (auto it = settings.constBegin(); it != settings.constEnd(); ++it)
    {
        settingsMap.insert(it.key(), it.value());
    }

    QVariantMap params
    {
        {"settings", settingsMap}
    };

    m_videoSdkWrapper->send(createJsonCommand("setHttpServerSettings", params));
}

void TC_Methods::setLastCallsViewed()
{
    m_videoSdkWrapper->send(createJsonCommand("setLastCallsViewed"));
}

void TC_Methods::setLogo(int fileId, int mode)
{
    m_videoSdkWrapper->send(createJsonCommand("setLogo", { {"fileId", fileId}, {"mode", mode} }));
}

void TC_Methods::setMicMute(bool mute)
{
    m_videoSdkWrapper->send(createJsonCommand("setMicMute", { {"mute", mute} }));
}

void TC_Methods::setModeratorRole(const QString& peerId, bool moderator)
{
    m_videoSdkWrapper->send(createJsonCommand("setModeratorRole", { {"peerId", peerId}, {"moderator", moderator} }));
}

void TC_Methods::setModes(const QString& pin, const QString& mode)
{
    m_videoSdkWrapper->send(createJsonCommand("setModes", { {"pin", pin}, {"mode", mode} }));
}

void TC_Methods::setNDIState(bool enabled)
{
    m_videoSdkWrapper->send(createJsonCommand("setNDIState", { {"enabled", enabled} }));
}

void TC_Methods::setOutputSelfVideoRotateAngle(int rotateAngle)
{
    m_videoSdkWrapper->send(createJsonCommand("setOutputSelfVideoRotateAngle", { {"rotateAngle", rotateAngle} }));
}

void TC_Methods::setPanPos(int pos)
{
    m_videoSdkWrapper->send(createJsonCommand("setPanPos", { {"pos", pos} }));
}

void TC_Methods::setPtzDefaults()
{
    m_videoSdkWrapper->send(createJsonCommand("setPtzDefaults"));
}

void TC_Methods::setSettings(const QMap<QString, QVariant>& settings)
{
    QVariantMap settingsMap;
    for (auto it = settings.constBegin(); it != settings.constEnd(); ++it)
    {
        settingsMap.insert(it.key(), it.value());
    }

    QVariantMap params
    {
        {"settings", settingsMap}
    };

    m_videoSdkWrapper->send(createJsonCommand("setSettings", params));
}

void TC_Methods::setSlidePosition(int fromIdx, int toIdx)
{
    m_videoSdkWrapper->send(createJsonCommand("setSlidePosition", { {"fromIdx", fromIdx}, {"toIdx", toIdx} }));
}

void TC_Methods::setTiltPos(int pos)
{
    m_videoSdkWrapper->send(createJsonCommand("setTiltPos", { {"pos", pos} }));
}

void TC_Methods::setUsedApiVersion(const QString& version)
{
    m_videoSdkWrapper->send(createJsonCommand("setUsedApiVersion", { {"version", version} }));
}

void TC_Methods::setVideoCapturer(const QString& name, const QString& description)
{
    m_videoSdkWrapper->send(createJsonCommand("setVideoCapturer", { {"name", name}, {"description", description} }));
}

void TC_Methods::setVideoMute(bool mute)
{
    m_videoSdkWrapper->send(createJsonCommand("setVideoMute", { {"mute", mute} }));
}

void TC_Methods::setZoomPos(int pos)
{
    m_videoSdkWrapper->send(createJsonCommand("setZoomPos", { {"pos", pos} }));
}

void TC_Methods::showFirstSlide()
{
    m_videoSdkWrapper->send(createJsonCommand("showFirstSlide"));
}

void TC_Methods::showLastSlide()
{
    m_videoSdkWrapper->send(createJsonCommand("showLastSlide"));
}

void TC_Methods::showNextSlide()
{
    m_videoSdkWrapper->send(createJsonCommand("showNextSlide"));
}

void TC_Methods::showPrevSlide()
{
    m_videoSdkWrapper->send(createJsonCommand("showPrevSlide"));
}

void TC_Methods::showSlide(int idx)
{
    m_videoSdkWrapper->send(createJsonCommand("showSlide", { {"idx", idx} }));
}

void TC_Methods::showVideoSlot(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("showVideoSlot", { {"callId", callId} }));
}

void TC_Methods::shutdown(bool forAll)
{
    m_videoSdkWrapper->send(createJsonCommand("shutdown", { {"forAll", forAll} }));
}

void TC_Methods::shutdownSystem()
{
    m_videoSdkWrapper->send(createJsonCommand("shutdownSystem"));
}

void TC_Methods::sortSlides()
{
    m_videoSdkWrapper->send(createJsonCommand("sortSlides"));
}

void TC_Methods::startAudioDelayDetectorTest()
{
    m_videoSdkWrapper->send(createJsonCommand("startAudioDelayDetectorTest"));
}

void TC_Methods::startBroadcastPicture(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("startBroadcastPicture", { {"fileId", fileId} }));
}

void TC_Methods::startCapture(int captureId)
{
    m_videoSdkWrapper->send(createJsonCommand("startCapture", { {"captureId", captureId} }));
}

void TC_Methods::startHttpServer()
{
    m_videoSdkWrapper->send(createJsonCommand("startHttpServer"));
}

void TC_Methods::startRemark()
{
    m_videoSdkWrapper->send(createJsonCommand("startRemark"));
}

void TC_Methods::startSlideShow(const QString& title, int startingIdx)
{
    m_videoSdkWrapper->send(createJsonCommand("startSlideShow", { {"title", title}, {"startingIdx", startingIdx} }));
}

void TC_Methods::stopAudioDelayDetectorTest()
{
    m_videoSdkWrapper->send(createJsonCommand("stopAudioDelayDetectorTest"));
}

void TC_Methods::stopBroadcastPicture()
{
    m_videoSdkWrapper->send(createJsonCommand("stopBroadcastPicture"));
}

void TC_Methods::stopCachingAllImages()
{
    m_videoSdkWrapper->send(createJsonCommand("stopCachingAllImages"));
}

void TC_Methods::stopCapture()
{
    m_videoSdkWrapper->send(createJsonCommand("stopCapture"));
}

void TC_Methods::stopHttpServer()
{
    m_videoSdkWrapper->send(createJsonCommand("stopHttpServer"));
}

void TC_Methods::stopSlideShow()
{
    m_videoSdkWrapper->send(createJsonCommand("stopSlideShow"));
}

void TC_Methods::swapVideoSlots(const QString& callId1, const QString& callId2)
{
    m_videoSdkWrapper->send(createJsonCommand("swapVideoSlots", { {"callId1", callId1}, {"callId2", callId2} }));
}

void TC_Methods::switchVideoFlow(const QString& callId, bool mainCamera)
{
    m_videoSdkWrapper->send(createJsonCommand("switchVideoFlow", { {"callId", callId}, {"mainCamera", mainCamera} }));
}

void TC_Methods::testAudioCapturerStart()
{
    m_videoSdkWrapper->send(createJsonCommand("testAudioCapturerStart"));
}

void TC_Methods::testAudioCapturerStop()
{
    m_videoSdkWrapper->send(createJsonCommand("testAudioCapturerStop"));
}

void TC_Methods::testAudioRenderer()
{
    m_videoSdkWrapper->send(createJsonCommand("testAudioRenderer"));
}

void TC_Methods::toneDial(const QString& symbol, const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("toneDial", { {"symbol", symbol}, {"callId", callId} }));
}

void TC_Methods::turnRemoteCamera(const QString& peerId, bool on)
{
    m_videoSdkWrapper->send(createJsonCommand("turnRemoteCamera", { {"peerId", peerId}, {"on", on} }));
}

void TC_Methods::turnRemoteMic(const QString& peerId, bool on)
{
    m_videoSdkWrapper->send(createJsonCommand("turnRemoteMic", { {"peerId", peerId}, {"on", on} }));
}

void TC_Methods::turnRemoteSpeaker(const QString& peerId, bool on)
{
    m_videoSdkWrapper->send(createJsonCommand("turnRemoteSpeaker", { {"peerId", peerId}, {"on", on} }));
}

void TC_Methods::unblock(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("unblock", { {"peerId", peerId} }));
}

void TC_Methods::acceptIncomingFileRequest(const QString& fileRequestId)
{
    m_videoSdkWrapper->send(createJsonCommand("acceptIncomingFileRequest", { {"fileRequestId", fileRequestId} }));
}

void TC_Methods::addPresetFromCurrentVideoCapturer()
{
    m_videoSdkWrapper->send(createJsonCommand("addPresetFromCurrentVideoCapturer"));
}

void TC_Methods::applyVideoCapturerPreset(const QString& presetId)
{
    m_videoSdkWrapper->send(createJsonCommand("applyVideoCapturerPreset", { {"presetId", presetId} }));
}

void TC_Methods::changeConferenceMode(bool isSmartMeeting)
{
    m_videoSdkWrapper->send(createJsonCommand("changeConferenceMode", { {"isSmartMeeting", isSmartMeeting} }));
}

void TC_Methods::clearFileTransferHistory(bool deleteFilesFromDisk)
{
    m_videoSdkWrapper->send(createJsonCommand("clearFileTransferHistory", { {"deleteFilesFromDisk", deleteFilesFromDisk} }));
}

void TC_Methods::getAllVideoCapturerPresets()
{
    m_videoSdkWrapper->send(createJsonCommand("getAllVideoCapturerPresets"));
}

void TC_Methods::getBlur()
{
    m_videoSdkWrapper->send(createJsonCommand("getBlur"));
}

void TC_Methods::getComPort()
{
    m_videoSdkWrapper->send(createJsonCommand("getComPort"));
}

void TC_Methods::getFileRequestInfo(const QString& fileRequestId)
{
    m_videoSdkWrapper->send(createJsonCommand("getFileRequestInfo", { {"fileRequestId", fileRequestId} }));
}

void TC_Methods::getFileTransferHistory()
{
    m_videoSdkWrapper->send(createJsonCommand("getFileTransferHistory"));
}

void TC_Methods::getIncomingFilesRequests()
{
    m_videoSdkWrapper->send(createJsonCommand("getIncomingFilesRequests"));
}

void TC_Methods::getNoiseSuppression()
{
    m_videoSdkWrapper->send(createJsonCommand("getNoiseSuppression"));
}

void TC_Methods::getOutgoingFilesRequests()
{
    m_videoSdkWrapper->send(createJsonCommand("getOutgoingFilesRequests"));
}

void TC_Methods::getReplaceBackground()
{
    m_videoSdkWrapper->send(createJsonCommand("getReplaceBackground"));
}

void TC_Methods::getSleepMode()
{
    m_videoSdkWrapper->send(createJsonCommand("getSleepMode"));
}

void TC_Methods::openURLProtocol(const QString& url)
{
    m_videoSdkWrapper->send(createJsonCommand("openURLProtocol", { {"url", url} }));
}

void TC_Methods::pinUser(const QString& peerId, bool isPinNeeded)
{
    m_videoSdkWrapper->send(createJsonCommand("pinUser", { {"peerId", peerId}, {"isPinNeeded", isPinNeeded} }));
}

void TC_Methods::prepareCallIdForCall(const QString& callId)
{
    m_videoSdkWrapper->send(createJsonCommand("prepareCallIdForCall", { {"callId", callId} }));
}

void TC_Methods::rejectIncomingFileRequest(const QString& fileRequestId)
{
    m_videoSdkWrapper->send(createJsonCommand("rejectIncomingFileRequest", { {"fileRequestId", fileRequestId} }));
}

void TC_Methods::removeVideoCapturerPreset(const QString& presetId)
{
    m_videoSdkWrapper->send(createJsonCommand("removeVideoCapturerPreset", { {"presetId", presetId} }));
}

void TC_Methods::searchContact(const QString& searchingString, int searchingTimeoutMsec, int searchingMask)
{
    m_videoSdkWrapper->send(createJsonCommand("searchContact"
                                                  , { {"searchingString", searchingString}
                                                       , {"searchingTimeoutMsec", searchingTimeoutMsec}
                                                       , {"searchingMask", searchingMask} }));
}

void TC_Methods::searchContact2(const QString& searchingString)
{
    m_videoSdkWrapper->send(createJsonCommand("searchContact2", { {"searchingString", searchingString} }));
}

void TC_Methods::sendFileToConference(int fileId)
{
    m_videoSdkWrapper->send(createJsonCommand("sendFileToConference", { {"fileId", fileId} }));
}

void TC_Methods::sendStopContentSharing(const QString& peerId)
{
    m_videoSdkWrapper->send(createJsonCommand("sendStopContentSharing", { {"peerId", peerId} }));
}

void TC_Methods::setBlur(bool enabled)
{
    m_videoSdkWrapper->send(createJsonCommand("setBlur", { {"enabled", enabled} }));
}

void TC_Methods::setComPort(const QString& port)
{
    m_videoSdkWrapper->send(createJsonCommand("setComPort", { {"port", port} }));
}

void TC_Methods::setCurrentPtzPropertyInverted(const QString& property, bool inverted)
{
    m_videoSdkWrapper->send(createJsonCommand("setCurrentPtzPropertyInverted", { {"property", property}, {"on", inverted} }));
}

void TC_Methods::setDefaultContentSource(const QString& name)
{
    m_videoSdkWrapper->send(createJsonCommand("setDefaultContentSource", { {"name", name} }));
}

void TC_Methods::setExtStatus(int extStatus, const QString& additionalStatus)
{
    m_videoSdkWrapper->send(createJsonCommand("setExtStatus", { {"extStatus", extStatus}, {"additionalStatus", additionalStatus} }));
}

void TC_Methods::setNoiseSuppression(bool enabled)
{
    m_videoSdkWrapper->send(createJsonCommand("setNoiseSuppression", { {"enabled", enabled} }));
}

void TC_Methods::setParticipantPresenceInWaitingRoom(const QString& callId, bool inWaitingRoom)
{
    m_videoSdkWrapper->send(createJsonCommand("setParticipantPresenceInWaitingRoom", { {"callId", callId}, {"inWaitingRoom", inWaitingRoom} }));
}

void TC_Methods::setSleepMode(bool enabled)
{
    m_videoSdkWrapper->send(createJsonCommand("setSleepMode", { {"enabled", enabled} }));
}

void TC_Methods::updatePresetFromCurrentVideoCapturer(const QString& presetId)
{
    m_videoSdkWrapper->send(createJsonCommand("updatePresetFromCurrentVideoCapturer", { {"presetId", presetId} }));
}

void TC_Methods::eraseCustomScheduler()
{
    m_videoSdkWrapper->send(createJsonCommand("eraseCustomScheduler"));
}

void TC_Methods::setWaitingRoomState(bool isUsersMustBeInvited, bool enable)
{
    m_videoSdkWrapper->send(createJsonCommand("setWaitingRoomState", { {"isUsersMustBeInvited", isUsersMustBeInvited}, {"enable", enable} }));
}

void TC_Methods::setReplaceBackground(int fileId, bool enabled)
{
    m_videoSdkWrapper->send(createJsonCommand("setReplaceBackground", { {"fileId", fileId}, {"enabled", enabled} }));
}

void TC_Methods::addVideoCapturerPreset(const QVariantMap& params)
{
    // Example of filling params:
    //    QVariantMap params
    //    {
    //        {"videoCapturerName", "USB Video Device"},
    //        {"videoCapturerDescription", R"(\\?\usb#vid_046d&pid_0823&mi_02#6&1fd43445&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global)"},
    //        {"isMuted", false},
    //        {"comPort", ""},
    //        {"pan", QVariantMap{{"isPresent", false}}},
    //        {"tilt", QVariantMap{{"isPresent", true}, {"value", 666}}},
    //        {"zoom", QVariantMap{{"isPresent", true}, {"value", 666}}},
    //        {"preview", QVariantMap{{"isPresent", true}, {"value", "base64ImageSource"}}}
    //    };
    //
    // And the call is just addVideoCapturerPreset(params)

    m_videoSdkWrapper->send(createJsonCommand("addVideoCapturerPreset", params));
}

void TC_Methods::updateVideoCapturerPreset(const QVariantMap& params)
{
    // Example of filling params:
    //    QVariantMap params
    //    {
    //        {"videoCapturerName", "USB Video Device"},
    //        {"videoCapturerDescription", R"(\\?\usb#vid_046d&pid_0823&mi_02#6&1fd43445&0&0002#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global)"},
    //        {"isMuted", false},
    //        {"comPort", ""},
    //        {"pan", QVariantMap{{"isPresent", false}}},
    //        {"tilt", QVariantMap{{"isPresent", true}, {"value", 666}}},
    //        {"zoom", QVariantMap{{"isPresent", true}, {"value", 666}}},
    //        {"preview", QVariantMap{{"isPresent", true}, {"value", "base64ImageSource"}}}
    //    };
    //
    // And the call is just updateVideoCapturerPreset(params)

    m_videoSdkWrapper->send(createJsonCommand("updateVideoCapturerPreset", params));
}

void TC_Methods::setCustomScheduler(const QString& conferencesJsonStr)
{
    m_videoSdkWrapper->send(createJsonCommand("setCustomScheduler", { {"conferences", QJsonDocument::fromJson(conferencesJsonStr.toUtf8()).array()} }));
}

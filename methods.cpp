#include "methods.h"
#include "videosdk.h"

CMethods::CMethods(VideoSDK *sdk)
{
    m_sdk = sdk;
}

void CMethods::call(const QString &peerId)
{
    /* command = {"method": "call", "peerId": peerId} */
    QString command = "{\"method\": \"call\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::accept()
{
    QString command = "{\"method\": \"accept\"}";
    m_sdk->API_send(command);
}

void CMethods::hangUp(bool forAll)
{

    QString command = "{\"method\": \"hangUp\", \"forAll\": " + QString(forAll ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::login(const QString &callId, const QString &password)
{
    QString command = "{\"method\": \"login\", \"login\": \"" + callId +"\", \"password\": \""
                    + password +"\", \"encryptPassword\": true}";
    m_sdk->API_send(command);
}

void CMethods::logout()
{
    QString command = "{\"method\": \"logout\"}";
    m_sdk->API_send(command);
}

void CMethods::connectToServer(const QString &server, int port)
{
    QString command = "{\"method\": \"connectToServer\", \"server\": \"" + server +"\", \"port\": \"" + port +"\"}";
    m_sdk->API_send(command);
}

void CMethods::sendCommand(const QString &peerId, const QString &command)
{
    QString com = "{\"method\": \"sendCommand\", \"peerId\": \"" + peerId +"\", \"command\": \"" + command +"\"}";
    m_sdk->API_send(com);
}

void CMethods::showMainWindow(bool maximized, bool stayOnTop)
{
//state:
//   1 = minimized;
//   2 = full screen mode.
    int state = !maximized ? 1 : 2;
    QString command = "{\"method\": \"showMainWindow\", \"windowState\": " + QString::number(state)
                    + ", \"stayOnTop\": " + QString(stayOnTop ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::reject()
{
    QString command = "{\"method\": \"reject\"}";
    m_sdk->API_send(command);
}

void CMethods::rejectPeer(const QString &peerId)
{
    QString command = "{\"method\": \"rejectPeer\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::acceptPeer(const QString &peerId)
{
    QString command = "{\"method\": \"acceptPeer\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::createConference(const QString &title, const QString &confType, bool autoAccept, const QList<QString>& inviteList)
{
    QString command = "{\"method\": \"createConference\", \"title\": \"" + title
                    + "\", \"confType\": \"" + confType +"\", \"autoAccept\": " + QString(autoAccept ? "true" : "false") + "";

    if(!inviteList.isEmpty())
    {
        command += ", \"inviteList\": [";
        for(auto invite : inviteList)
        {
            command += "\"" + invite + "\"";
            if(invite != inviteList.back())
            {
                command += ", ";
            }
        }
        command += "]";
    }
    command += "}";

    m_sdk->API_send(command);
}

void CMethods::getHardware()
{
    QString command = "{\"method\": \"getHardware\"}";
    m_sdk->API_send(command);
}

void CMethods::acceptFile(int id)
{
    QString command = "{\"method\": \"acceptFile\", \"id\": " + QString::number(id) +"}";
    m_sdk->API_send(command);
}

void CMethods::acceptInvitationToPodium()
{
    QString command = "{\"method\": \"acceptInvitationToPodium\"}";
    m_sdk->API_send(command);
}

void CMethods::acceptRequestCameraControl(const QString &callId)
{
    QString command = "{\"method\": \"acceptRequestCameraControl\", \"callId\": \"" + callId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::acceptRequestToPodium(const QString &peerId)
{
    QString command = "{\"method\": \"acceptRequestToPodium\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::addSlide(int fileId)
{
    QString command = "{\"method\": \"addSlide\", \"fileId\": " + QString::number(fileId) +"}";
    m_sdk->API_send(command);
}

void CMethods::addToAbook(const QString &peerId, const QString &peerDn)
{
    QString command = "{\"method\": \"addToAbook\", \"peerId\": \"" + peerId +"\", \"peerDn\": \"" + peerDn +"\"}";
    m_sdk->API_send(command);
}

void CMethods::addToGroup(int groupId, const QString &peerId)
{
    QString command = "{\"method\": \"addToAbook\", \"groupId\": " + QString::number(groupId)
                    + ", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::allowRecord(const QString &peerId)
{
    QString command = "{\"method\": \"allowRecord\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::block(const QString &peerId)
{
    QString command = "{\"method\": \"block\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::changeCurrentMonitor(int monitorIndex)
{
    QString command = "{\"method\": \"changeCurrentMonitor\", \"monitorIndex\": " + QString::number(monitorIndex) +"}";
    m_sdk->API_send(command);
}

void CMethods::changeVideoMatrixType(int matrixType)
{
    QString command = "{\"method\": \"changeVideoMatrixType\", \"matrixType\": " + QString::number(matrixType) +"}";
    m_sdk->API_send(command);
}

void CMethods::changeWindowState(int windowState, bool stayOnTop)
{
    QString command = "{\"method\": \"changeWindowState\", \"windowState\": " + QString::number(windowState)
                    +", \"stayOnTop\": " + QString(stayOnTop ? "true" : "false") +"}";
    m_sdk->API_send(command);
}

void CMethods::chatClear(const QString &id)
{
    QString command = "{\"method\": \"chatClear\", \"id\": \"" + id +"\"}";
    m_sdk->API_send(command);
}

void CMethods::clearCallHistory()
{
    QString command = "{\"method\": \"clearCallHistory\"}";
    m_sdk->API_send(command);
}

void CMethods::clearFileTransfer()
{
    QString command = "{\"method\": \"clearFileTransfer\"}";
    m_sdk->API_send(command);
}

void CMethods::clearTokens()
{
    QString command = "{\"method\": \"clearTokens\"}";
    m_sdk->API_send(command);
}

void CMethods::connectToService()
{
    QString command = "{\"method\": \"connectToService\"}";
    m_sdk->API_send(command);
}

void CMethods::createGroup(const QString &name)
{
    QString command = "{\"method\": \"createGroup\", \"name\": \"" + name +"\"}";
    m_sdk->API_send(command);
}

void CMethods::createNDIDevice(const QString &deviceId)
{
    QString command = "{\"method\": \"createNDIDevice\", \"deviceId\": \"" + deviceId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::deleteData(const QString &containerName)
{
    QString command = "{\"method\": \"deleteData\", \"containerName\": \"" + containerName +"\"}";
    m_sdk->API_send(command);
}

void CMethods::deleteFileTransferFile(int fileId)
{
    QString command = "{\"method\": \"deleteFileTransferFile\", \"fileId\": " + QString::number(fileId) +"}";
    m_sdk->API_send(command);
}

void CMethods::deleteNDIDevice(const QString &deviceId)
{
    QString command = "{\"method\": \"deleteNDIDevice\", \"deviceId\": \"" + deviceId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::denyRecord(const QString &peerId)
{
    QString command = "{\"method\": \"denyRecord\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::enableAudioReceiving(const QString &peerId, bool enable)
{
    QString command = "{\"method\": \"enableAudioReceiving\", \"peerId\": \"" + peerId
                    +"\", \"enable\": " + QString(enable ? "true" : "false") +"}";
    m_sdk->API_send(command);
}

void CMethods::enableVideoReceiving(const QString &peerId, bool enable)
{
    QString command = "{\"method\": \"enableVideoReceiving\", \"peerId\": \"" + peerId
                    +"\", \"enable\": " + QString(enable ? "true" : "false") +"}";
    m_sdk->API_send(command);
}

void CMethods::expandCallToMulti(const QString& title, const QList<QString>& inviteList)
{
    QString command = "{\"method\": \"expandCallToMulti\", \"title\": \"" + title + "\"";

    if(!inviteList.isEmpty())
    {
        command += ", \"inviteList\": [";
        for(auto invite : inviteList)
        {
            command += "\"" + invite + "\"";
            if(invite != inviteList.back())
            {
                command += ", ";
            }
        }
        command += "]";
    }
    command += "}";

    m_sdk->API_send(command);
}

void CMethods::fireMyEvent(const QString &data)
{
    QString command = "{\"method\": \"fireMyEvent\", \"data\": \"" + data +"\"}";
    m_sdk->API_send(command);
}

void CMethods::getAbook()
{
    QString command = "{\"method\": \"getAbook\"}";
    m_sdk->API_send(command);
}

void CMethods::getAllUserContainersNames()
{
    QString command = "{\"method\": \"getAllUserContainersNames\"}";
    m_sdk->API_send(command);
}

void CMethods::getAppSndDev()
{
    QString command = "{\"method\": \"getAppSndDev\"}";
    m_sdk->API_send(command);
}

void CMethods::getAppState()
{
    QString command = "{\"method\": \"getAppState\"}";
    m_sdk->API_send(command);
}

void CMethods::activateLicense(const QString &key)
{
    QString command = "{\"method\": \"activateLicense\", \"key\": \"" + key +"\"}";
    m_sdk->API_send(command);
}

void CMethods::auth(const QString &role, const QString &type, const QString &credentials)
{
    QString command = "{\"method\": \"auth\"";
    if(!type.isEmpty())
    {
        command += ", \"type\": \"" + type + "\"";
    }
    if(!credentials.isEmpty())
    {
        command += ", \"credentials\": \"" + credentials + "\"";
    }
    command += ", \"role\": \"" + role + "\"}";
    m_sdk->API_send(command);
}

void CMethods::getAudioDelayDetectorInfo()
{
    QString command = "{\"method\": \"getAudioDelayDetectorInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getAudioMute()
{
    QString command = "{\"method\": \"getAudioMute\"}";
    m_sdk->API_send(command);
}

void CMethods::getAudioReceivingLevel(const QString &peerId)
{
    QString command = "{\"method\": \"getAudioReceivingLevel\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

void CMethods::getAuthInfo()
{
    QString command = "{\"method\": \"getAuthInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getAvailableServersList()
{
    QString command = "{\"method\": \"getAvailableServersList\"}";
    m_sdk->API_send(command);
}

void CMethods::getBackground()
{
    QString command = "{\"method\": \"getBackground\"}";
    m_sdk->API_send(command);
}

void CMethods::getBanList()
{
    QString command = "{\"method\": \"getBanList\"}";
    m_sdk->API_send(command);
}

void CMethods::getBroadcastPicture()
{
    QString command = "{\"method\": \"getBroadcastPicture\"}";
    m_sdk->API_send(command);
}

void CMethods::getBroadcastSelfie()
{
    QString command = "{\"method\": \"getBroadcastSelfie\"}";
    m_sdk->API_send(command);
}

void CMethods::getCallHistory(int count)
{
    QString command = "{\"method\": \"getCallHistory\", \"count\": " + QString::number(count) + "}";
    m_sdk->API_send(command);
}

void CMethods::getChatLastMessages(const QString &id, int beginNumber, int count)
{
    QString command = "{\"method\": \"getChatLastMessages\", \"id\": \"" + id + "\", \"beginNumber\": " + QString::number(beginNumber)
                    + ", \"count\": " + QString::number(count) + "}";
    m_sdk->API_send(command);
}

void CMethods::getConferenceParticipants()
{
    QString command = "{\"method\": \"getConferenceParticipants\"}";
    m_sdk->API_send(command);
}

void CMethods::getConferences()
{
    QString command = "{\"method\": \"getConferences\"}";
    m_sdk->API_send(command);
}

void CMethods::getConnected()
{
    QString command = "{\"method\": \"getConnected\"}";
    m_sdk->API_send(command);
}

void CMethods::getContactDetails(const QString& peerId)
{
    QString command = "{\"method\": \"getContactDetails\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::getCreatedNDIDevices()
{
    QString command = "{\"method\": \"getCreatedNDIDevices\"}";
    m_sdk->API_send(command);
}

void CMethods::getCrop()
{
    QString command = "{\"method\": \"getCrop\"}";
    m_sdk->API_send(command);
}

void CMethods::getCurrentUserProfileUrl()
{
    QString command = "{\"method\": \"getCurrentUserProfileUrl\"}";
    m_sdk->API_send(command);
}

void CMethods::getDisplayNameById(const QString& peerId)
{
    QString command = "{\"method\": \"getDisplayNameById\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::getFileInfo(int id)
{
    QString command = "{\"method\": \"getFileInfo\", \"id\": " + QString::number(id) + "}";
    m_sdk->API_send(command);
}

void CMethods::getFileList()
{
    QString command = "{\"method\": \"getFileList\"}";
    m_sdk->API_send(command);
}

void CMethods::getFileRequests()
{
    QString command = "{\"method\": \"getFileRequests\"}";
    m_sdk->API_send(command);
}

void CMethods::getFileTransferAvailability()
{
    QString command = "{\"method\": \"getFileTransferAvailability\"}";
    m_sdk->API_send(command);
}

void CMethods::getFileTransferInfo()
{
    QString command = "{\"method\": \"getFileTransferInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getFileUploads()
{
    QString command = "{\"method\": \"getFileUploads\"}";
    m_sdk->API_send(command);
}

void CMethods::getGroups()
{
    QString command = "{\"method\": \"getGroups\"}";
    m_sdk->API_send(command);
}

void CMethods::getHardwareKey()
{
    QString command = "{\"method\": \"getHardwareKey\"}";
    m_sdk->API_send(command);
}

void CMethods::getHttpServerSettings()
{
    QString command = "{\"method\": \"getHttpServerSettings\"}";
    m_sdk->API_send(command);
}

void CMethods::getHttpServerState()
{
    QString command = "{\"method\": \"getHttpServerState\"}";
    m_sdk->API_send(command);
}

void CMethods::getIncomingCameraControlRequests()
{
    QString command = "{\"method\": \"getIncomingCameraControlRequests\"}";
    m_sdk->API_send(command);
}

void CMethods::getInfoWidgetsState()
{
    QString command = "{\"method\": \"getInfoWidgetsState\"}";
    m_sdk->API_send(command);
}

void CMethods::getLastCallsViewTime()
{
    QString command = "{\"method\": \"getLastCallsViewTime\"}";
    m_sdk->API_send(command);
}

void CMethods::getLastSelectedConference()
{
    QString command = "{\"method\": \"getLastSelectedConference\"}";
    m_sdk->API_send(command);
}

void CMethods::getLastUsedServersList(int count)
{
    QString command = "{\"method\": \"getLastUsedServersList\", \"count\": " + QString::number(count) + "}";
    m_sdk->API_send(command);
}

void CMethods::getLicenseServerStatus()
{
    QString command = "{\"method\": \"getLicenseServerStatus\"}";
    m_sdk->API_send(command);
}

void CMethods::getLicenseType()
{
    QString command = "{\"method\": \"getLicenseType\"}";
    m_sdk->API_send(command);
}

void CMethods::getListOfChats()
{
    QString command = "{\"method\": \"getListOfChats\"}";
    m_sdk->API_send(command);
}

void CMethods::getLogin()
{
    QString command = "{\"method\": \"getLogin\"}";
    m_sdk->API_send(command);
}

void CMethods::getLogo()
{
    QString command = "{\"method\": \"getLogo\"}";
    m_sdk->API_send(command);
}

void CMethods::getMaxConfTitleLength()
{
    QString command = "{\"method\": \"getMaxConfTitleLength\"}";
    m_sdk->API_send(command);
}

void CMethods::getMicMute()
{
    QString command = "{\"method\": \"getMicMute\"}";
    m_sdk->API_send(command);
}

void CMethods::getModes()
{
    QString command = "{\"method\": \"getModes\"}";
    m_sdk->API_send(command);
}

void CMethods::getMonitorsInfo()
{
    QString command = "{\"method\": \"getMonitorsInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getNDIState()
{
    QString command = "{\"method\": \"getNDIState\"}";
    m_sdk->API_send(command);
}

void CMethods::getOutgoingBitrate()
{
    QString command = "{\"method\": \"getOutgoingBitrate\"}";
    m_sdk->API_send(command);
}

void CMethods::getOutgoingCameraControlRequests()
{
    QString command = "{\"method\": \"getOutgoingCameraControlRequests\"}";
    m_sdk->API_send(command);
}

void CMethods::getOutputSelfVideoRotateAngle()
{
    QString command = "{\"method\": \"getOutputSelfVideoRotateAngle\"}";
    m_sdk->API_send(command);
}

void CMethods::getProperties()
{
    QString command = "{\"method\": \"getProperties\"}";
    m_sdk->API_send(command);
}

void CMethods::getPtzControls()
{
    QString command = "{\"method\": \"getPtzControls\"}";
    m_sdk->API_send(command);
}

void CMethods::getRemotelyControlledCameras()
{
    QString command = "{\"method\": \"getRemotelyControlledCameras\"}";
    m_sdk->API_send(command);
}

void CMethods::getRenderInfo()
{
    QString command = "{\"method\": \"getRenderInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getScheduler()
{
    QString command = "{\"method\": \"getScheduler\"}";
    m_sdk->API_send(command);
}

void CMethods::getServerDomain()
{
    QString command = "{\"method\": \"getServerDomain\"}";
    m_sdk->API_send(command);
}

void CMethods::getSettings()
{
    QString command = "{\"method\": \"getSettings\"}";
    m_sdk->API_send(command);
}

void CMethods::getSlideShowCache()
{
    QString command = "{\"method\": \"getSlideShowCache\"}";
    m_sdk->API_send(command);
}

void CMethods::getSlideShowInfo()
{
    QString command = "{\"method\": \"getSlideShowInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getSystemInfo()
{
    QString command = "{\"method\": \"getSystemInfo\"}";
    m_sdk->API_send(command);
}

void CMethods::getTariffRestrictions()
{
    QString command = "{\"method\": \"getTariffRestrictions\"}";
    m_sdk->API_send(command);
}

void CMethods::getTokenForHttpServer()
{
    QString command = "{\"method\": \"getTokenForHttpServer\"}";
    m_sdk->API_send(command);
}

void CMethods::getTrueConfRoomProKey()
{
    QString command = "{\"method\": \"getTrueConfRoomProKey\"}";
    m_sdk->API_send(command);
}

void CMethods::getVideoMatrix()
{
    QString command = "{\"method\": \"getVideoMatrix\"}";
    m_sdk->API_send(command);
}

void CMethods::getVideoMute()
{
    QString command = "{\"method\": \"getVideoMute\"}";
    m_sdk->API_send(command);
}

void CMethods::getWebManagerUrl()
{
    QString command = "{\"method\": \"getWebManagerUrl\"}";
    m_sdk->API_send(command);
}

void CMethods::gotoPodium()
{
    QString command = "{\"method\": \"gotoPodium\"}";
    m_sdk->API_send(command);
}

void CMethods::hideVideoSlot(const QString &callId)
{
    QString command = "{\"method\": \"hideVideoSlot\", \"callId\": \"" + callId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::inviteToConference(const QString& peerId)
{
    QString command = "{\"method\": \"inviteToConference\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::inviteToPodium(const QString &peerId)
{
    QString command = "{\"method\": \"inviteToPodium\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::kickFromPodium(const QString &peerId)
{
    QString command = "{\"method\": \"kickFromPodium\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::kickPeer(const QString &peerId)
{
    QString command = "{\"method\": \"kickPeer\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::leavePodium()
{
    QString command = "{\"method\": \"leavePodium\"}";
    m_sdk->API_send(command);
}

void CMethods::loadData(const QString &containerName)
{
    QString command = "{\"method\": \"loadData\", \"containerName\": \"" + containerName + "\"}";
    m_sdk->API_send(command);
}

void CMethods::moveVideoSlotToMonitor(const QString &callId, int monitorIndex)
{
    QString command = "{\"method\": \"moveVideoSlotToMonitor\", \"callId\": \"" + callId + "\", \"monitorIndex\": "
                    + QString::number(monitorIndex) + "}";
    m_sdk->API_send(command);
}

void CMethods::productRegistrationOffline(int fileId)
{
    QString command = "{\"method\": \"productRegistrationOffline\", \"fileId\": " + QString::number(fileId) + "}";
    m_sdk->API_send(command);
}

void CMethods::ptzDown()
{
    QString command = "{\"method\": \"ptzDown\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzLeft()
{
    QString command = "{\"method\": \"ptzLeft\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzRight()
{
    QString command = "{\"method\": \"ptzRight\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzStop()
{
    QString command = "{\"method\": \"ptzStop\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzUp()
{
    QString command = "{\"method\": \"ptzUp\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzZoomDec()
{
    QString command = "{\"method\": \"ptzZoomDec\"}";
    m_sdk->API_send(command);
}

void CMethods::ptzZoomInc()
{
    QString command = "{\"method\": \"ptzZoomInc\"}";
    m_sdk->API_send(command);
}

void CMethods::rebootSystem()
{
    QString command = "{\"method\": \"rebootSystem\"}";
    m_sdk->API_send(command);
}

void CMethods::rejectFile(int id)
{
    QString command = "{\"method\": \"rejectFile\", \"id\": " + QString::number(id) + "}";
    m_sdk->API_send(command);
}

void CMethods::rejectInvitationToPodium()
{
    QString command = "{\"method\": \"rejectInvitationToPodium\"}";
    m_sdk->API_send(command);
}

void CMethods::rejectRequestCameraControl(const QString &callId)
{
    QString command = "{\"method\": \"rejectRequestCameraControl\", \"callId\": \"" + callId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::rejectRequestToPodium(const QString &peerId)
{
    QString command = "{\"method\": \"rejectRequestToPodium\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzDown(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzDown\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzLeft(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzLeft\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzRight(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzRight\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzUp(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzUp\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzZoomDec(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzZoomDec\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::remotelyControlledCameraPtzZoomInc(const QString &cameraOwnerCallId)
{
    QString command = "{\"method\": \"remotelyControlledCameraPtzZoomInc\", \"cameraOwnerCallId\": \"" + cameraOwnerCallId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::removeAllSlides(bool removeFromServer)
{
    QString command = "{\"method\": \"removeAllSlides\", \"removeFromServer\": " + QString(removeFromServer ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::removeFromAbook(const QString &peerId)
{
    QString command = "{\"method\": \"removeFromAbook\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::removeFromGroup(int groupId, const QString& peerId)
{
    QString command = "{\"method\": \"removeFromGroup\", \"groupId\": " + QString::number(groupId)
                    + ", \"peerId\", \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::removeFromServersList(const QString &serverName)
{
    QString command = "{\"method\": \"removeFromServersList\", \"serverName\": \"" + serverName + "\"}";
    m_sdk->API_send(command);
}

void CMethods::removeGroup(int groupId)
{
    QString command = "{\"method\": \"removeGroup\", \"groupId\": " + QString::number(groupId) + "}";
    m_sdk->API_send(command);
}

void CMethods::removeImageFromCachingQueue(int groupId)
{
    QString command = "{\"method\": \"removeImageFromCachingQueue\", \"groupId\": " + QString::number(groupId) + "}";
    m_sdk->API_send(command);
}

void CMethods::removeSlide(int idx, bool removeFromServer)
{
    QString command = "{\"method\": \"removeSlide\", \"idx\": " + QString::number(idx) + ", \"removeFromServer\": "
                    + QString(removeFromServer ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::removeVideoSlotFromMonitor(int monitorIndex)
{
    QString command = "{\"method\": \"removeVideoSlotFromMonitor\", \"monitorIndex\": " + QString::number(monitorIndex) + "}";
    m_sdk->API_send(command);
}

void CMethods::renameGroup(int groupId, const QString &newName)
{
    QString command = "{\"method\": \"renameGroup\", \"groupId\": " + QString::number(groupId) + ", \"newName\": \"" +  newName + "\"}";
    m_sdk->API_send(command);
}

void CMethods::renameInAbook(const QString &peerId, const QString &peerDn)
{
    QString command = "{\"method\": \"renameInAbook\", \"peerId\": \"" + peerId + "\", \"peerDn\": \"" +  peerDn + "\"}";
    m_sdk->API_send(command);
}

void CMethods::requestParticipantCameraControl(const QString &callId)
{
    QString command = "{\"method\": \"requestParticipantCameraControl\", \"callId\": \"" + callId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::restoreWindow()
{
    QString command = "{\"method\": \"restoreWindow\"}";
    m_sdk->API_send(command);
}

void CMethods::saveData(const QString &containerName, const QString &data, const QString &flags)
{
    QString command = "{\"method\": \"saveData\", \"containerName\": \"" + containerName
                    + "\", \"data\": \"" + data + "\", \"flags\": \"" + flags + "\"}";
    m_sdk->API_send(command);
}

void CMethods::sendConferenceFile(int fileId)
{
    QString command = "{\"method\": \"sendConferenceFile\", \"fileId\": " + QString::number(fileId) + "}";
    m_sdk->API_send(command);
}

void CMethods::sendFile(int fileId, const QString &peerId)
{
    QString command = "{\"method\": \"sendFile\", \"fileId\": " + QString::number(fileId)
                    + ", \"peerId\", \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::sendGroupMessage(const QString &message)
{
    QString command = "{\"method\": \"sendGroupMessage\", \"message\": \"" + message + "\"}";
    m_sdk->API_send(command);
}

void CMethods::sendMessage(const QString &peerId, const QString &message)
{
    QString command = "{\"method\": sendMessage\", \"peerId\": \"" + peerId + "\", \"message\": \"" +  message + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setAppSndDev(const QString &name, const QString &description)
{
    QString command = "{\"method\": setAppSndDev\", \"name\": \"" + name + "\", \"description\": \"" +  description + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setAudioCapturer(const QString &name, const QString &description)
{
    QString command = "{\"method\": setAudioCapturer\", \"name\": \"" + name + "\", \"description\": \"" +  description + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setAudioMute(bool mute)
{
    QString command = "{\"method\": \"setAudioMute\", \"mute\": " + QString(mute ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::setAudioReceivingLevel(const QString &peerId, int level)
{
    QString command = "{\"method\": \"setAudioReceivingLevel\", \"peerId\": \"" + peerId + "\", \"level\": " +  QString::number(level) + "}";
    m_sdk->API_send(command);
}

void CMethods::setAudioRenderer(const QString &name, const QString &description)
{
    QString command = "{\"method\": \"setAudioRenderer\", \"name\": \"" + name + "\", \"description\": \"" +  description + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setAuthParams(const QString &userType, const QString &authType, const QString &authValue)
{
    QString command = "{\"method\": \"setAuthParams\", \"userType\": \"" + userType + "\", \"authType\": \"" + authType + "\"";
    if(authType == "password")
    {
        command += ", \"password\": \"" + authValue + "\"";
    }
    if(authType == "pin")
    {
        command += ", \"newPin\": \"" + authValue + "\"";
    }
    command += "}";
    m_sdk->API_send(command);
}

void CMethods::setBackground(int fileId)
{
    QString command = "{\"method\": \"setBackground\", \"fileId\": " + QString::number(fileId) + "}";
    m_sdk->API_send(command);
}

void CMethods::setBroadcastSelfie(bool enabled, int fps)
{
    QString command = "{\"method\": \"setBroadcastSelfie\", \"enabled\": " + QString(enabled ? "true" : "false")
                    + ", \"fps\": " + QString::number(fps) + "}";
    m_sdk->API_send(command);
}

void CMethods::setCrop(bool enable)
{
    QString command = "{\"method\": \"setCrop\", \"enable\": " + QString(enable ? "true" : "false") + "}";
}

void CMethods::setDefaultBackground()
{
    QString command = "{\"method\": \"setDefaultBackground\"}";
    m_sdk->API_send(command);
}

void CMethods::setDefaultLogo()
{
    QString command = "{\"method\": \"setDefaultLogo\"}";
    m_sdk->API_send(command);
}

void CMethods::setHttpServerSettings(const QMap<QString, int> &settings)
{
    QString command = "{\"method\": \"setHttpServerSettings\"";

    command += ", settings: {";

    if(!settings.isEmpty())
    {
        for(auto key : settings.keys())
        {
            if(key != settings.keys().front())
            {
                command += ", ";
            }
            command += "\"" + key + "\": " + QString::number(settings.value(key));
        }
    }
    command += "}}";;

    m_sdk->API_send(command);
}

void CMethods::setLastCallsViewed()
{
    QString command = "{\"method\": \"setLastCallsViewed\"}";
    m_sdk->API_send(command);
}

void CMethods::setLogo(int fileId, int mode)
{
    QString command = "{\"method\": \"setLogo\", \"fileId\": " + QString::number(fileId) + ", \"mode\": "
                    + QString::number(mode) + "}";
    m_sdk->API_send(command);
}

void CMethods::setMicMute(bool mute)
{
    QString command = "{\"method\": \"setMicMute\", \"mute\": " + QString(mute ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::setModeratorRole(const QString &peerId, bool moderator)
{
    QString command = "{\"method\": \"setModeratorRole\", \"peerId\": \"" + peerId + "\", \"moderator\": " + QString(moderator ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::setModes(const QString &pin, const QString &mode)
{
    QString command = "{\"method\": \"setModes\", \"pin\": \"" + pin + "\", \"mode\": \"" + mode + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setNDIState(bool enabled)
{
    QString command = "{\"method\": \"setNDIState\", \"enabled\": " + QString(enabled ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::setOutputSelfVideoRotateAngle(int rotateAngle)
{
    QString command = "{\"method\": \"setOutputSelfVideoRotateAngle\", \"rotateAngle\": " + QString::number(rotateAngle) + "}";
    m_sdk->API_send(command);
}

void CMethods::setPanPos(int pos)
{
    QString command = "{\"method\": \"setPanPos\", \"pos\": " + QString::number(pos) + "}";
    m_sdk->API_send(command);
}

void CMethods::setPtzDefaults()
{
    QString command = "{\"method\": \"setPtzDefaults\"}";
    m_sdk->API_send(command);
}

void CMethods::setSettings(const QString &settings)
{
    QString command = "{\"method\": \"setSettings\", \"settings\": {" + settings + "}}";
    m_sdk->API_send(command);
}

void CMethods::setSlidePosition(int fromIdx, int toIdx)
{
    QString command = "{\"method\": \"setSlidePosition\", \"fromIdx\": " + QString::number(fromIdx) + ", \"toIdx\": "
                    + QString::number(toIdx) + "}";
    m_sdk->API_send(command);
}

void CMethods::setTiltPos(int pos)
{
    QString command = "{\"method\": \"setTiltPos\", \"pos\": " + QString::number(pos) + "}";
    m_sdk->API_send(command);
}

void CMethods::setUsedApiVersion(const QString &version)
{
    QString command = "{\"method\": \"setUsedApiVersion\", \"version\": \"" + version + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setVideoCapturer(const QString &name, const QString &description)
{
    QString command = "{\"method\": \"setVideoCapturer\", \"name\": \"" + name + "\", \"description\": \""
            + description + "\"}";
    m_sdk->API_send(command);
}

void CMethods::setVideoMute(bool mute)
{
    QString command = "{\"method\": \"setVideoMute\", \"mute\": " + QString(mute ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::setZoomPos(int pos)
{
    QString command = "{\"method\": \"setZoomPos\", \"pos\": " + QString::number(pos) + "}";
    m_sdk->API_send(command);
}

void CMethods::showFirstSlide()
{
    QString command = "{\"method\": \"showFirstSlide\"}";
    m_sdk->API_send(command);
}

void CMethods::showLastSlide()
{
    QString command = "{\"method\": \"showLastSlide\"}";
    m_sdk->API_send(command);
}

void CMethods::showNextSlide()
{
    QString command = "{\"method\": \"showNextSlide\"}";
    m_sdk->API_send(command);
}

void CMethods::showPrevSlide()
{
    QString command = "{\"method\": \"showPrevSlide\"}";
    m_sdk->API_send(command);
}

void CMethods::showSlide(int idx)
{
    QString command = "{\"method\": \"showSlide\", \"idx\": " + QString::number(idx) + "}";
    m_sdk->API_send(command);
}

void CMethods::showVideoSlot(const QString &callId)
{
    QString command = "{\"method\": \"showVideoSlot\", \"callId\": \"" + callId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::shutdown(bool forAll)
{
    QString command = "{\"method\": \"shutdown\", \"forAll\": " + QString(forAll ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::shutdownSystem()
{
    QString command = "{\"method\": \"shutdownSystem\"}";
    m_sdk->API_send(command);
}

void CMethods::sortSlides()
{
    QString command = "{\"method\": \"sortSlides\"}";
    m_sdk->API_send(command);
}

void CMethods::startAudioDelayDetectorTest()
{
    QString command = "{\"method\": \"startAudioDelayDetectorTest\"}";
    m_sdk->API_send(command);
}

void CMethods::startBroadcastPicture(int fileId)
{
    QString command = "{\"method\": \"startBroadcastPicture\", \"fileId\": " + QString::number(fileId) + "}";
    m_sdk->API_send(command);
}

void CMethods::startCapture(int captureId)
{
    QString command = "{\"method\": \"startCapture\", \"captureId\": " + QString::number(captureId) + "}";
    m_sdk->API_send(command);
}

void CMethods::startHttpServer()
{
    QString command = "{\"method\": \"startHttpServer\"}";
    m_sdk->API_send(command);
}

void CMethods::startRemark()
{
    QString command = "{\"method\": \"startRemark\"}";
    m_sdk->API_send(command);
}

void CMethods::startSlideShow(const QString &title, int startingIdx)
{
    QString command = "{\"method\": \"startSlideShow\", \"title\": \"" + title + "\", \"startingIdx\": " + QString::number(startingIdx) + "}";
    m_sdk->API_send(command);
}

void CMethods::stopAudioDelayDetectorTest()
{
    QString command = "{\"method\": \"stopAudioDelayDetectorTest\"}";
    m_sdk->API_send(command);
}

void CMethods::stopBroadcastPicture()
{
    QString command = "{\"method\": \"stopBroadcastPicture\"}";
    m_sdk->API_send(command);
}

void CMethods::stopCachingAllImages()
{
    QString command = "{\"method\": \"stopCachingAllImages\"}";
    m_sdk->API_send(command);
}

void CMethods::stopCapture()
{
    QString command = "{\"method\": \"stopCapture\"}";
    m_sdk->API_send(command);
}

void CMethods::stopHttpServer()
{
    QString command = "{\"method\": \"stopHttpServer\"}";
    m_sdk->API_send(command);
}

void CMethods::stopSlideShow()
{
    QString command = "{\"method\": \"stopSlideShow\"}";
    m_sdk->API_send(command);
}

void CMethods::swapVideoSlots(const QString &callId1, const QString &callId2)
{
    QString command = "{\"method\": \"swapVideoSlots\", \"callId1\": \"" + callId1 + "\", \"callId2\": \"" + callId2 + "\"}";
    m_sdk->API_send(command);
}

void CMethods::switchVideoFlow(const QString &callId, bool mainCamera)
{
    QString command = "{\"method\": \"switchVideoFlow\", \"callId\": \"" + callId + "\", \"mainCamera\": " + QString(mainCamera ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::testAudioCapturerStart()
{
    QString command = "{\"method\": \"testAudioCapturerStart\"}";
    m_sdk->API_send(command);
}

void CMethods::testAudioCapturerStop()
{
    QString command = "{\"method\": \"testAudioCapturerStop\"}";
    m_sdk->API_send(command);
}

void CMethods::testAudioRenderer()
{
    QString command = "{\"method\": \"testAudioRenderer\"}";
    m_sdk->API_send(command);
}

void CMethods::toneDial(const QString &symbol, const QString &callId)
{
    QString command = "{\"method\": \"toneDial\", \"symbol\": \"" + symbol + "\", \"callId\": \"" + callId + "\"}";
    m_sdk->API_send(command);
}

void CMethods::turnRemoteCamera(const QString &peerId, bool on)
{
    QString command = "{\"method\": \"turnRemoteCamera\", \"peerId\": \"" + peerId + "\", \"on\": " + QString(on ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::turnRemoteMic(const QString &peerId, bool on)
{
    QString command = "{\"method\": \"turnRemoteMic\", \"peerId\": \"" + peerId + "\", \"on\": " + QString(on ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::turnRemoteSpeaker(const QString &peerId, bool on)
{
    QString command = "{\"method\": \"turnRemoteSpeaker\", \"peerId\": \"" + peerId + "\", \"on\": " + QString(on ? "true" : "false") + "}";
    m_sdk->API_send(command);
}

void CMethods::unblock(const QString &peerId)
{
    QString command = "{\"method\": \"unblock\", \"peerId\": \"" + peerId + "\"}";
    m_sdk->API_send(command);
}

























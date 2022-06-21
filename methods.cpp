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








































#include "methods.h"
#include "videosdk.h"

CMethods::CMethods(VideoSDK *sdk)
{
    m_sdk = sdk;
}

/*!
* Make p2p call
*
* @param[in] peerId A unique user ID (TrueConfID)
*/
void CMethods::call(const QString &peerId)
{
    /* command = {"method": "call", "peerId": peerId} */
    QString command = "{\"method\": \"call\", \"peerId\": \"" + peerId +"\"}";
    m_sdk->API_send(command);
}

#include "events.h"
#include "videosdk.h"
#include <qdebug.h>

CEvents::CEvents(VideoSDK *sdk)
{
    m_sdk = sdk;
    QObject::connect(m_sdk, SIGNAL(socketReceived(QString)), this, SLOT(socketReceived(QString)));
}

void CEvents::socketReceived(QString data)
{
    qDebug() << "CEvents::socketReceived:" << endl << data << endl;
}

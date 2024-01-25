#include "TC_Events.h"
#include "TC_VideoSdkWrapper.h"


TC_Events::TC_Events(TC_VideoSdkWrapper* videoSdkWrapper, QObject* parent)
    : QObject(parent)
{
    connect(videoSdkWrapper, &TC_VideoSdkWrapper::notificationReceived, this, &TC_Events::socketReceivedEvent);
}

TC_Events::~TC_Events()
{

}

void TC_Events::socketReceivedEvent(const QString& eventName, const QJsonObject& eventJsonObj)
{
    if (QMetaObject::invokeMethod(this, eventName.toUtf8().constData(), Q_ARG(const QJsonObject&, eventJsonObj)))
    {
        return;
    }

    Q_EMIT unsupportedEvent(eventName, eventJsonObj);
}

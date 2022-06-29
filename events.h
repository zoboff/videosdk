#ifndef CEVENTS_H
#define CEVENTS_H

#include <QObject>

class VideoSDK;

class CEvents: public QObject
{
    Q_OBJECT
public:
    explicit CEvents(VideoSDK *sdk);

private:
    VideoSDK *m_sdk;

private slots:
    void socketReceived(QString data);

signals:
     void NDIDeviceCreated(const QString &responce);
};

#endif // CEVENTS_H

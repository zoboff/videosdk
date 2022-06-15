#ifndef METHODS_H
#define METHODS_H

#include <QObject>

class VideoSDK;

class CMethods {

public:
    CMethods(VideoSDK *sdk);

private:
    VideoSDK *m_sdk;

/* All Video SDK API methods */
public:
    /*
    Make p2p call

            Parameters
            ----------
            peerId : str
                A unique user ID (TrueConfID)
    */
    void call(const QString &peerId);
};


#endif // METHODS_H

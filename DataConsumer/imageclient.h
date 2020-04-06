#ifndef IMAGECLIENT_H
#define IMAGECLIENT_H

#include <QObject>
//#include <QImage>
#include <QTimer>

#include "rep_ImageProvider_replica.h"

class ImageClient : public QObject
{
    Q_OBJECT

    QSharedPointer<ImageProviderReplica> _replicaPtr;
    QTimer _tm, _requestor;
    int _receivedRate;

private slots:
    void tick();
    void sendGrabRequest();

public:
    void Start(int _requestIntervalMs);
    void Stop();
    void SetRequestsPeriod(int _requestIntervalMs);

    ImageClient();
    ImageClient(QSharedPointer<ImageProviderReplica> ptr);
    ~ImageClient();

signals:
    void newImageAvailable(QImage img);
    void receivedRateUpdate(int _receivedRate);

public slots:
    void onFrameChanged(QImage imgData);
};

#endif // IMAGECLIENT_H

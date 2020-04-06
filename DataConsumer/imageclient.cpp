#include "imageclient.h"

ImageClient::ImageClient()
{
    _receivedRate = 0;
    _tm.setInterval(1000);
}

ImageClient::ImageClient(QSharedPointer<ImageProviderReplica> ptr) : _replicaPtr(ptr)
{
    connect(_replicaPtr.data(), SIGNAL(frameChanged(QImage)), this, SLOT(onFrameChanged(QImage)));
    _receivedRate = 0;
    _tm.setInterval(1000);
}

ImageClient::~ImageClient()
{

}

void ImageClient::onFrameChanged(QImage imgData)
{
    _receivedRate++;
    //qInfo() << '.';//"received image " << QString("%1x%2").arg(imgData.width()).arg(imgData.height());
    emit(newImageAvailable(imgData));
}

void ImageClient::Start(int _requestIntervalMs)
{
    connect(&_tm, SIGNAL(timeout()), this, SLOT(tick()));
    _tm.start();

    connect(&_requestor, SIGNAL(timeout()), this, SLOT(sendGrabRequest()));
    if(_requestIntervalMs)
        _requestor.start(_requestIntervalMs);
    else
        _requestor.start(17);
}

void ImageClient::Stop()
{
    _requestor.stop();
    _tm.stop();
}

void ImageClient::SetRequestsPeriod(int _requestIntervalMs)
{
    _requestor.stop();
    _requestor.start(_requestIntervalMs);
}

void ImageClient::tick()
{
    //qInfo() << "FPS = " << _receivedRate << endl;
    emit(receivedRateUpdate(_receivedRate));
    _receivedRate= 0;
}

void ImageClient::sendGrabRequest()
{
    //qInfo() << "sending req" << endl;
    _replicaPtr->TakeSnapshot();
}

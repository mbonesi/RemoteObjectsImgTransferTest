#ifndef FRAMEGRABBER_H
#define FRAMEGRABBER_H

#include <QObject>
#include <QImage>
#include <QTimer>

#include "rep_ImageProvider_source.h"

class FrameGrabber : public ImageProviderSimpleSource
{    
    Q_OBJECT

    std::atomic<int> _requestsPerSec;

    QTimer _tm;
    QImage _image;

private slots:
    void tick();

public:
    FrameGrabber();
    void TakeSnapshot();

};

#endif // FRAMEGRABBER_H

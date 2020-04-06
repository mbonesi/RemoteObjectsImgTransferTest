#include "framegrabber.h"
#include <QPainter>

void FrameGrabber::tick()
{
    //qInfo() << "Reqs/sec = " << _requestsPerSec;
    _requestsPerSec = 0;
}

FrameGrabber::FrameGrabber() : _requestsPerSec(0)
{
    bool bLoadOK= false;
    bLoadOK = _image.load("/home/mbonesi/TEMP/IMAGETRANSFERTEST/DataSource/image.png");
    _tm.setInterval(1000L);
    connect(&_tm, SIGNAL(timeout()), this, SLOT(tick()));
    _tm.start();
}

void FrameGrabber::TakeSnapshot()
{
    int x = qrand() % 2048;
    int y = qrand() % 128;
    QImage outgoing(_image);
    QPainter qPainter(&outgoing);
    qPainter.setBrush(Qt::blue);
    qPainter.setPen(Qt::blue);
    qPainter.drawRect(x,y,48,48);
    qPainter.end();
    setFrame(outgoing);
    _requestsPerSec++;
}

#include <QCoreApplication>

#include "framegrabber.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //QRemoteObjectHost sourceNode(QUrl(QStringLiteral("local:switch")));
    QRemoteObjectHost sourceNode(QUrl(QStringLiteral("tcp://127.0.0.1:2001")));

    FrameGrabber softFG;
    sourceNode.enableRemoting(&softFG);

    qInfo() << "Serving remote FrameGrab requests";

    return a.exec();
}


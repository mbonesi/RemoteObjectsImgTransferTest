#include "mainwindow.h"

#include <QApplication>
#include "../DataConsumer/imageclient.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QRemoteObjectNode replicaNode; // create remote object node
    //replicaNode.connectToNode(QUrl(QStringLiteral("local:switch"))); // connect with remote host node
    replicaNode.connectToNode(QUrl(QStringLiteral("tcp://127.0.0.1:2001")));

    QSharedPointer<ImageProviderReplica> ptr;
    ptr.reset(replicaNode.acquire<ImageProviderReplica>()); // acquire replica of source from host node

    MainWindow w(ptr);
    w.show();
    return a.exec();
}

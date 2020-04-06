#include <QCoreApplication>

#include "imageclient.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QRemoteObjectNode replicaNode; // create remote object node
    replicaNode.connectToNode(QUrl(QStringLiteral("local:switch"))); // connect with remote host node

    QSharedPointer<ImageProviderReplica> ptr;
    ptr.reset(replicaNode.acquire<ImageProviderReplica>()); // acquire replica of source from host node

    ImageClient cli(ptr);
    cli.Start(40);

    return a.exec();
}

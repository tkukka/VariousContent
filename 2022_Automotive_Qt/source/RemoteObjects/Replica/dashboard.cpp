#include "dashboard.h"

Dashboard::Dashboard(QObject *parent)
    : QObject{parent},
      m_text{"Dashboard/Replica"}
{

    qDebug() << "[replica] Creating replica node...";
    m_node.reset(new QRemoteObjectNode(this));
    qDebug() << "[replica] Connecting to remote node...";
    bool connected = m_node->connectToNode(QUrl(QStringLiteral("local:car")));

    if(!connected) {
        qWarning() << "[replica] not connected to a remote node!";
    }

    qDebug() << "[replica] Acquring remote object (locally)...";
    m_carReplica.reset(m_node->acquire<CarReplica>());

    if (!m_carReplica) {
        qWarning() << "[replica] Couldn't acquire replica object!";
    }


    connect(m_carReplica.get(), &CarReplica::massChanged, this, &Dashboard::printMass);
    connect(this, &Dashboard::testExecuted, m_carReplica.get(), &CarReplica::powerUp);
    //TODO handle QRemoteObjectReplica:: stateChanged
}

void Dashboard::test()
{
    qDebug() << "[replica] Testing property: mass";
    qDebug() << "[replica] current mass:" << m_carReplica->mass();
    emit testExecuted(m_text);
}

void Dashboard::printMass()
{
    qDebug() << "[replica] source signalled: Mass changed. Current mass:" << m_carReplica->mass();
}

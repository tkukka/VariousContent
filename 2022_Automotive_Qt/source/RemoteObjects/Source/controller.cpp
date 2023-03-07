#include "controller.h"

Controller::Controller(QObject *parent)
    : QObject{parent}, m_mass{2000}
{
    qDebug() << "[source] Creating source object...";
    m_car.reset(new Car(this));
    m_car->setMass(m_mass);
    qDebug() << "[source] Creating source node...";
    m_node.reset(new QRemoteObjectHost(QUrl(QStringLiteral("local:car")), this));
    qDebug() << "[source] Enabling remote access...";
    m_node->enableRemoting(m_car.get());
}

void Controller::start()
{
    qDebug() << "[Controller/Source] " << Q_FUNC_INFO;
    m_car->powerUp("Controller/Source");
}

int Controller::mass() const
{
    qDebug() << "[Controller/Source] read mass:" << m_mass;
    return m_mass;
}

void Controller::setMass(int newMass)
{
    if (m_mass == newMass)
        return;

    qDebug() << "[Controller/Source] setting mass:" << newMass;
    m_mass = newMass;
    m_car->setMass(m_mass);
    emit massChanged();
}

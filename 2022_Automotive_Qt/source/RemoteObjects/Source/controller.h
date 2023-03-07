#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QQmlEngine>
#include "car.h"

class Controller : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON
    Q_PROPERTY(int mass READ mass WRITE setMass NOTIFY massChanged FINAL)
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller() = default;

    Q_INVOKABLE void start();

    int mass() const;
    void setMass(int newMass);

signals:

    void massChanged();

private:
    QScopedPointer<Car> m_car;
    QScopedPointer<QRemoteObjectHost> m_node;
    int m_mass;
};

#endif // CONTROLLER_H

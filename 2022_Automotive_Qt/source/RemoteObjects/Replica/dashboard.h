#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QQmlEngine>
#include <QScopedPointer>

#include "rep_car_replica.h"

class Dashboard : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit Dashboard(QObject *parent = nullptr);

    Q_INVOKABLE void test();

public slots:
    void printMass();

signals:
    void testExecuted(QString m_message);
private:
    QString m_text;
    QScopedPointer<QRemoteObjectNode> m_node;
    QScopedPointer<CarReplica> m_carReplica;
};

#endif // DASHBOARD_H

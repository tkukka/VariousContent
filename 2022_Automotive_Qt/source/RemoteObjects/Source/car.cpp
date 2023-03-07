#include "car.h"

Car::Car(QObject *parent) : CarSimpleSource{parent}
{

}


void Car::powerUp(QString from)
{
    qDebug() << "[source/Car] Car powered up by:" << from << "Mass:" << mass();
}

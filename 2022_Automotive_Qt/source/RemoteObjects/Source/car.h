#ifndef CAR_H
#define CAR_H

#include "rep_car_source.h"

class Car : public CarSimpleSource
{
    Q_OBJECT
public:
    explicit Car(QObject *parent = nullptr);
    virtual ~Car() override = default;

public slots:
    virtual void powerUp(QString from) override;
};

#endif // CAR_H

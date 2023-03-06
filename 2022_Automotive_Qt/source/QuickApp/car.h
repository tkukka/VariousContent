#ifndef CAR_H
#define CAR_H

#include <QQmlEngine>

class Car : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(int maxPower READ maxPower WRITE setMaxPower NOTIFY maxPowerChanged FINAL REQUIRED)
    Q_PROPERTY(double power READ power WRITE setPower NOTIFY powerChanged FINAL)
    Q_PROPERTY(double charge READ charge WRITE setCharge NOTIFY chargeChanged FINAL)
    Q_PROPERTY(double maxCharge READ maxCharge WRITE setMaxCharge NOTIFY maxChargeChanged FINAL REQUIRED)
    Q_PROPERTY(int maxSpeed READ maxSpeed WRITE setMaxSpeed NOTIFY maxSpeedChanged FINAL)
    Q_PROPERTY(double speed READ speed WRITE setSpeed NOTIFY speedChanged FINAL)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged FINAL)
    Q_PROPERTY(int mass READ mass WRITE setMass NOTIFY massChanged FINAL REQUIRED)
    Q_PROPERTY(bool powered READ powered WRITE setPowered NOTIFY poweredChanged FINAL)
    Q_PROPERTY(bool parked READ parked WRITE setParked NOTIFY parkedChanged FINAL)

public:
    explicit Car(QObject *parent = nullptr);
    virtual ~Car();

    int maxPower() const;
    void setMaxPower(int newMaxPower);

    double power() const;
    void setPower(double newPower);

    double maxCharge() const;
    void setMaxCharge(double newMaxCharge);

    double charge() const;
    void setCharge(double newCharge);

    int maxSpeed() const;
    void setMaxSpeed(int newMaxSpeed);

    double speed() const;
    void setSpeed(double newSpeed);

    double distance() const;
    void setDistance(double newDistance);

    int mass() const;
    void setMass(int newMass);

    bool powered() const;
    void setPowered(bool newPowered);

    void updateSpeed();
    static double drag(double speed);

    void updateDistance();
    void updateCharge();

    bool parked() const;
    void setParked(bool newParked);

    void saveSettings() const;
    void loadSettings();

signals:
    void maxPowerChanged();
    void powerChanged(double newPower);
    void maxChargeChanged();
    void chargeChanged(double newCharge);
    void depleted();
    void maxSpeedChanged();
    void speedChanged(double newSpeed);
    void distanceChanged(double newCharge);
    void massChanged(int newMass);
    void poweredChanged(bool newPowered);
    void parkedChanged();

protected:
    virtual void timerEvent(QTimerEvent *event) override;

private:
    int m_maxPower;         // [kW]
    double m_power;         // [kW]
    double m_maxCharge;     // [kWh]
    double m_charge;        // [kWh]
    int m_maxSpeed;         // [km/h]
    double m_speed;         // [km/h]
    double m_distance;      // [m]
    int m_mass;             // [kg]
    bool m_powered;         // engine status
    double m_deltaTime;
    int m_timer;
    bool m_parked;          // parking brake status
};

#endif // CAR_H

#include <QCoreApplication>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include "car.h"

constexpr double DragCoeff = 1.6;
constexpr double StaticFriction = 1000;     // [N]
constexpr double MaxForce = 5000;           // [N]
constexpr double Tolerance = 0.2;
constexpr double DeltaTime = 0.2;           // time slice [s]

constexpr const char* JSON_DISTANCE = "distance";
constexpr const char* JSON_MAX_CHARGE = "maxCharge";
constexpr const char* JSON_CHARGE = "charge";

Car::Car(QObject *parent):
    QObject{parent},
    m_power{0},
    m_charge{0},
    m_speed{0},
    m_distance{0},
    m_mass{2000},
    m_deltaTime{DeltaTime},
    m_powered{false},
    m_parked{false}
{
    loadSettings();
    m_timer = startTimer(DeltaTime * 1000);
}

Car::~Car()
{
    killTimer(m_timer);
    saveSettings();
}

int Car::maxPower() const
{
    return m_maxPower;
}

void Car::setMaxPower(int newMaxPower)
{
    if (m_maxPower == newMaxPower)
        return;
    m_maxPower = newMaxPower;
    emit maxPowerChanged();
}

double Car::power() const
{
    return m_power;
}

void Car::setPower(double newPower)
{
    newPower = qBound(0.0, newPower, static_cast<double>(m_maxPower));

    if (qFuzzyCompare(m_power, newPower))
        return;
    m_power = newPower;
    emit powerChanged(m_power);
}

double Car::maxCharge() const
{
    return m_maxCharge;
}

void Car::setMaxCharge(double newMaxCharge)
{
    if (qFuzzyCompare(m_maxCharge, newMaxCharge))
        return;
    m_maxCharge = newMaxCharge;
    emit maxChargeChanged();
}

double Car::charge() const
{
    return m_charge;
}

void Car::setCharge(double newCharge)
{
    if (newCharge > m_maxCharge) {
        newCharge = m_maxCharge;
    }

    if (qFuzzyCompare(m_charge, newCharge))
        return;

    if (newCharge <= 0) {
        newCharge = 0;
        emit depleted();
    }

    m_charge = newCharge;
    emit chargeChanged(m_charge);
}

int Car::maxSpeed() const
{
    return m_maxSpeed;
}

void Car::setMaxSpeed(int newMaxSpeed)
{
    if (m_maxSpeed == newMaxSpeed)
        return;
    m_maxSpeed = newMaxSpeed;
    emit maxSpeedChanged();
}

double Car::speed() const
{
    return m_speed;
}

void Car::setSpeed(double newSpeed)
{
    if (qFuzzyCompare(m_speed, newSpeed))
        return;
    m_speed = newSpeed;
    emit speedChanged(m_speed);
}

double Car::distance() const
{
    return m_distance;
}

void Car::setDistance(double newDistance)
{
    if (newDistance < 0) {
        return;
    }

    if (qFuzzyCompare(m_distance, newDistance))
        return;

    m_distance = newDistance;
    emit distanceChanged(m_distance);
}

int Car::mass() const
{
    return m_mass;
}

void Car::setMass(int newMass)
{
    if (m_mass == newMass)
        return;
    m_mass = newMass;
    emit massChanged(m_mass);
}

bool Car::powered() const
{
    return m_powered;
}

void Car::setPowered(bool newPowered)
{
    if (m_powered == newPowered)
        return;
    m_powered = newPowered;
    emit poweredChanged(m_powered);
}

void Car::updateSpeed()
{
    double oldSpeed = m_speed / 3.6;        // 3.6: [km/h] => [m/s]
    double forwardForce = 0;
    if (m_powered && m_charge > 0) {
        // make up a force pulling car forward
        forwardForce = m_power / m_maxPower * MaxForce;
    }
    double friction =  StaticFriction + drag(oldSpeed);
    if (m_parked) {
        friction += MaxForce;
    }
    double netForce = forwardForce - friction;   // resultant force
    double acceleration = netForce / m_mass;     // F =  m · a => a = F/m

    if (qAbs(acceleration) <= Tolerance ){  // stabilize quicker to equilibrium
        acceleration = 0;
    }

    double newSpeed =  3.6 * (oldSpeed + acceleration * m_deltaTime);  // 3.6: [m/s] => [km/h]

    if (newSpeed <= 0) { // Stop the movement when the speed is exhausted
        newSpeed = 0;
    }

    setSpeed(newSpeed);
    //qDebug() << "netForce:" << netForce << "acc:" << acceleration << "oldSpeed:" << oldSpeed*3.6 << "newSpeed:" << newSpeed;
}

// air resistance ~ velocity squared
double Car::drag(double speed)
{
    return DragCoeff * speed * speed;
}

void Car::updateDistance()
{

    double increment = m_deltaTime * m_speed / 3.6;     // travelled distance s = V · t [m]
    setDistance(m_distance + increment);
}

void Car::updateCharge()
{
    if (m_powered) {
        double oldCharge = 3600 * m_charge;             // [kWh] => [kW · s]
        double discharge = m_deltaTime * m_power;       // energy consumed E = P · t  [kW · s]
        setCharge((oldCharge - discharge) / 3600);
    }
}

void Car::timerEvent(QTimerEvent *event)
{
    updateSpeed();
    updateDistance();
    updateCharge();
}

bool Car::parked() const
{
    return m_parked;
}

void Car::setParked(bool newParked)
{
    if (m_parked == newParked)
        return;
    m_parked = newParked;
    emit parkedChanged();
}

void Car::saveSettings() const
{
    QString fileName = QCoreApplication::applicationName() + ".ini";
    QFile settingsFile(fileName);

    if (!settingsFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open access settings file" << fileName;
        return;
    }

    qDebug() << "Writing settings to" << fileName;

    QJsonObject object;
    object[JSON_DISTANCE] = qRound(m_distance);
    object[JSON_MAX_CHARGE] = m_maxCharge;
    object[JSON_CHARGE] = m_charge;

    settingsFile.write( QJsonDocument(object).toJson() );
    settingsFile.flush();
    settingsFile.close();
}

void Car::loadSettings()
{
    QString fileName = QCoreApplication::applicationName() + ".ini";
    QFile settingsFile(fileName);

    if (settingsFile.exists()) {
        if(!settingsFile.open(QIODevice::ReadOnly)) {
            qWarning() << "Couldn't open settings file" << fileName;
            return;
        }

        qDebug() << "Reading settings from" << fileName;

        const QByteArray data = settingsFile.readAll();
        settingsFile.close();

        QJsonParseError jsonError;
        const QJsonDocument jsonDoc = QJsonDocument::fromJson(data, &jsonError);

        if(jsonError.error != QJsonParseError::NoError) {
            qWarning() << "Couldn't parse settings file" << fileName;
            return;
        }

        if(!jsonDoc.isObject()) {
            qWarning() << fileName << "didn't contain a proper JSON object";
            return;
        }

        const QJsonObject &object = jsonDoc.object();

        if (object.contains(JSON_DISTANCE) && object[JSON_DISTANCE].isDouble()) {
                setDistance( object[JSON_DISTANCE].toDouble() );
                qDebug() << "Set distance:" << m_distance;
            }
        else {
             qWarning() << "Couldn't find JSON:" << JSON_DISTANCE;
        }

        if (object.contains(JSON_MAX_CHARGE) && object[JSON_MAX_CHARGE].isDouble()) {
                setMaxCharge( object[JSON_MAX_CHARGE].toDouble() );
                qDebug() << "Set max charge:" << m_maxCharge;
            }
        else {
             qWarning() << "Couldn't find JSON:" << JSON_MAX_CHARGE;
        }

        if (object.contains(JSON_CHARGE) && object[JSON_CHARGE].isDouble()) {
                setCharge( object[JSON_CHARGE].toDouble() );
                qDebug() << "Set charge:" << m_charge;
            }
        else {
             qWarning() << "Couldn't find JSON:" << JSON_CHARGE;
        }
    } // if settings file exists

}

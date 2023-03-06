#include <QPainter>
#include <QPen>
#include <QFontMetrics>
#include "odometer.h"
//TODO: optimoi UIn päivitystä vielä harvemmaksi?? lisää int-muuttuja, jonka
// muuttuminen emittoi näkymän päivityksen
OdoMeter::OdoMeter(QQuickItem *parent) : QQuickPaintedItem{parent},
    m_foregroundColor{Qt::GlobalColor::black},
    m_backgroundColor{Qt::GlobalColor::white},
    m_distance{0},
    m_visualDigits{7}

{
    const QFontMetrics fm(m_font);
    m_digitWidth = fm.horizontalAdvance("8");
    connect(this, &OdoMeter::distanceChanged, this, &OdoMeter::onDistanceChanged);
}

void OdoMeter::paint(QPainter *painter)
{
    painter->setFont(m_font);
    painter->setPen(QPen(m_foregroundColor));
    const auto rect = boundingRect();
    painter->fillRect(rect, Qt::GlobalColor::cyan);
    painter->fillRect(rect.adjusted(0, 0, -m_digitWidth, 0), m_backgroundColor);
    painter->drawText(rect, Qt::AlignVCenter, toString());
}

const QColor &OdoMeter::foregroundColor() const
{
    return m_foregroundColor;
}

void OdoMeter::setForegroundColor(const QColor &newForegroundColor)
{
    if (m_foregroundColor == newForegroundColor)
        return;
    m_foregroundColor = newForegroundColor;
    emit foregroundColorChanged();
}

const QColor &OdoMeter::backgroundColor() const
{
    return m_backgroundColor;
}

void OdoMeter::setBackgroundColor(const QColor &newBackgroundColor)
{
    if (m_backgroundColor == newBackgroundColor)
        return;
    m_backgroundColor = newBackgroundColor;
    emit backgroundColorChanged();
}

const QFont &OdoMeter::font() const
{
    return m_font;
}

void OdoMeter::setFont(const QFont &newFont)
{
    if (m_font == newFont)
        return;
    m_font = newFont;
    emit fontChanged();
    //qDebug() << "Font set to" << m_font;
    const QFontMetrics fm(m_font);
    m_digitWidth = fm.horizontalAdvance("8");
}

double OdoMeter::distance() const
{
    return m_distance;
}

void OdoMeter::setDistance(double newDistance)
{
    if (qFuzzyCompare(m_distance, newDistance))
        return;
    m_distance = newDistance;
    emit distanceChanged();
}

void OdoMeter::onDistanceChanged()
{
    const auto rect = boundingRect();
    update(rect.toRect());
}

void OdoMeter::add(double increment)
{
    setDistance(m_distance + increment);
}

void OdoMeter::reset()
{
    setDistance(0);
}

int OdoMeter::visualDigits() const
{
    return m_visualDigits;
}

void OdoMeter::setVisualDigits(int newVisualDigits)
{
    if (m_visualDigits == newVisualDigits)
        return;
    m_visualDigits = newVisualDigits;
    emit visualDigitsChanged();
}

QString OdoMeter::toString() const
{
    int value_in_100m = qRound(m_distance / 100);
    return QString("%1").arg(value_in_100m, m_visualDigits, 10, QLatin1Char('0'));
    //auto s = QString("%1").arg(value_in_100m, m_visualDigits, 10, QLatin1Char('0'));
    //qDebug() << s;
    //return s;
}


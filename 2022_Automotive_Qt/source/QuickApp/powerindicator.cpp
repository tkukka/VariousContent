#include <QPainter>
#include <QPen>
#include <QColor>
#include <QFont>
#include "powerindicator.h"


constexpr int StartAngle = -135 *16;
constexpr int MaxAngleSpan = -270 *16;
constexpr int ArcPenWidth = 10;
constexpr const char *FontName = "Segoa";
constexpr int FontSize = 22;
constexpr int TextMargin = 15;


namespace {
// choose color according to power level [0...1]
Qt::GlobalColor pickColor(double level);
}

PowerIndicator::PowerIndicator(QQuickItem *parent) :
    QQuickPaintedItem{parent},
    m_value{0},
    m_maxValue{1}

{
    connect(this, &PowerIndicator::valueChanged, this, &PowerIndicator::onValueChanged);
    connect(this, &QQuickItem::enabledChanged, this, &PowerIndicator::onEnableChanged);
}

void PowerIndicator::paint(QPainter *painter)
{
    double powerRatio = m_value / m_maxValue;
    const QPen textPen(pickColor(powerRatio));
    const auto rect = boundingRect();   // bounding rectangle of the widget

    // prepare for the arc
    int spanAngle = qRound( MaxAngleSpan * powerRatio);
    const auto arcRect = rect.adjusted(ArcPenWidth, ArcPenWidth, -ArcPenWidth, -ArcPenWidth); // fit inside the bounding rectangle
    QPen arcPen(textPen);
    arcPen.setWidth(ArcPenWidth);
    painter->setPen(arcPen);
    painter->drawArc(arcRect, StartAngle, spanAngle);

    // prepare for the text
    const QFont font(FontName, FontSize);
    painter->setFont(font);
    painter->setPen(textPen);
    const QString powerText(QString("%1 kW").arg(m_value, 0, 'f', 0));
    painter->drawText(rect.adjusted(-TextMargin, 0, -TextMargin, 0), Qt::AlignVCenter|Qt::AlignRight, powerText);
}

double PowerIndicator::value() const
{
    return m_value;
}

void PowerIndicator::setValue(double newValue)
{
    if (qFuzzyCompare(m_value, newValue))
        return;
    m_value = newValue;
    emit valueChanged();
}

double PowerIndicator::maxValue() const
{
    return m_maxValue;
}

void PowerIndicator::setMaxValue(double newMaxValue)
{

    if (qFuzzyCompare(m_maxValue, newMaxValue))
        return;
    m_maxValue = newMaxValue;
    emit maxValueChanged();
}

void PowerIndicator::onValueChanged()
{
    if (isEnabled()) {
        const auto rect = boundingRect();
        update(rect.toRect());
    }
}

void PowerIndicator::onEnableChanged()
{
    if (isEnabled()) {
        const auto rect = boundingRect();
        update(rect.toRect());
    }
}

namespace {

Qt::GlobalColor pickColor(double level)
{
    if (level >= 0 && level < 0.25) {
        return Qt::GlobalColor::white;
    }
    else if (level >= 0.25 && level < 0.6) {
         return Qt::GlobalColor::green;
    }
    else if (level >= 0.6 && level < 0.8) {
         return Qt::GlobalColor::magenta;
    }
    else if (level >= 0.8 && level <= 1.01) {
         return Qt::GlobalColor::red;
    }

    return Qt::GlobalColor::gray;
}

} // namespace

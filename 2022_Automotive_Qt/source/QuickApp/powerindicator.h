#ifndef POWERINDICATOR_H
#define POWERINDICATOR_H

#include <QQmlEngine>
#include <QQuickPaintedItem>

class PowerIndicator : public QQuickPaintedItem
{
    Q_OBJECT
    QML_ELEMENT
    Q_PROPERTY(double value READ value WRITE setValue NOTIFY valueChanged FINAL)
    Q_PROPERTY(double maxValue READ maxValue WRITE setMaxValue NOTIFY maxValueChanged FINAL)

public:
    explicit PowerIndicator(QQuickItem *parent = nullptr);
    virtual void paint(QPainter *painter) override;

    double value() const;
    void setValue(double newValue);
    double maxValue() const;
    void setMaxValue(double newMaxValue);

signals:
    void valueChanged();
    void maxValueChanged();
    void textChanged();

public slots:
    void onValueChanged();
    void onEnableChanged();

private:
    double m_value;
    double m_maxValue;
};

#endif // POWERINDICATOR_H

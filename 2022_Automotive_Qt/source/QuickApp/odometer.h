#ifndef ODOMETER_H
#define ODOMETER_H

#include <QQmlEngine>
#include <QQuickPaintedItem>
#include <QColor>
#include <QFont>

class OdoMeter : public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QColor foregroundColor READ foregroundColor WRITE setForegroundColor NOTIFY foregroundColorChanged FINAL)
    Q_PROPERTY(QColor backgroundColor READ backgroundColor WRITE setBackgroundColor NOTIFY backgroundColorChanged FINAL)
    Q_PROPERTY(QFont font READ font WRITE setFont NOTIFY fontChanged FINAL)
    Q_PROPERTY(double distance READ distance WRITE setDistance NOTIFY distanceChanged FINAL)
    Q_PROPERTY(int visualDigits READ visualDigits WRITE setVisualDigits NOTIFY visualDigitsChanged FINAL)
    QML_ELEMENT

public:
    explicit OdoMeter(QQuickItem *parent = nullptr);

    virtual void paint(QPainter *painter) override;

    const QColor &foregroundColor() const;
    void setForegroundColor(const QColor &newForegroundColor);

    const QColor &backgroundColor() const;
    void setBackgroundColor(const QColor &newBackgroundColor);

    const QFont &font() const;
    void setFont(const QFont &newFont);

    double distance() const;
    void setDistance(double newDistance);
    Q_INVOKABLE void add(double increment);
    Q_INVOKABLE void reset();

    int visualDigits() const;
    void setVisualDigits(int newVisualDigits);

    QString toString() const;   // round to 100 m precision and convert to string

public slots:
    void onDistanceChanged();

signals:
    void foregroundColorChanged();
    void backgroundColorChanged();
    void fontChanged();
    void distanceChanged();
    void visualDigitsChanged();

private:
    QColor m_foregroundColor;
    QColor m_backgroundColor;
    QFont m_font;        // use application default font
    double m_distance;   // [m]
    int m_visualDigits;  // how many digits displayed
    int m_digitWidth;    // pixel width of a digit
};

#endif // ODOMETER_H

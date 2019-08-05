#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QObject>
#include <QColor>
#include <QPainter>
#include <QGraphicsItem>
#include <QStyleOptionGraphicsItem>



const static float LightSize = 25;
const static float WidgetDimension = 25;
const static float LightScale = 0.6;

class LightWidget :public QObject,/*public QGraphicsLayoutItem,*/ public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
//    Q_INTERFACES(QGraphicsLayoutItem)
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    LightWidget(const QColor &color,QGraphicsItem *parent = nullptr);
    // Virtual Function Area (Must be implemented)
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
//    void setGeometry(const QRectF &rect);
//    QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
    // End Virtual Function Area
    QColor getColor() const;
    bool isOn() const;
    void setOn(bool on);
    void setColor(const QColor &color);
    void TurnOnInteraction();
    void TurnOffInteraction();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;

public slots:
    void turnOff();
    void turnOn();
private:
    QColor m_color;
    bool m_on;
    bool m_IsClickable;

};

#endif // LIGHTWIDGET_H

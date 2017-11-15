#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "lightwidget.h"
#include "lightwidgetleft.h"
#include "commonenum.h"
#include <QtCore>
#include <QtWidgets>

class TrafficLight : public QGraphicsItem
{
public:
    //@Override
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //Override
    TrafficLight(region re,QGraphicsItem *parent = 0);
    TrafficLight(QGraphicsItem *parent = 0);
    region getRegion();
    bool checkDir(Direction dir);
    void setManualControl();
    void setUpFacilities();
    LightWidget *getMainGreen() const;
    LightWidget *getMainRed() const;
    LightWidget *getMainYellow() const;
    LightWidget *getLeftGreen() const;
//protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QList<LightWidget *> *getLight() const;

    void setRegion(const region &region);

private:
    LightWidget *m_main_light_green;
    LightWidget *m_main_light_red;
    LightWidget *m_main_light_yellow;
    LightWidget *m_left_light;
    QList<LightWidget *> *m_light;
    region m_region;
};

#endif // TRAFFICLIGHT_H

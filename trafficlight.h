#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "lightwidget.h"
#include "lightwidgetleft.h"
#include "commonenum.h"
#include <QtCore>
#include <QtWidgets>

class TrafficLight : public QGraphicsItemGroup
{
public:
    //@Override
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //Override
    TrafficLight(region re,QGraphicsItemGroup *parent = 0);
    region getRegion();
    bool checkDir(Direction dir);
    LightWidget *getMainGreen() const;
    LightWidget *getMainRed() const;
    LightWidget *getMainYellow() const;
    LightWidgetLeft *getLeftGreen() const;
private:
    LightWidget *m_main_light_green;
    LightWidget *m_main_light_red;
    LightWidget *m_main_light_yellow;
    LightWidgetLeft *m_left_light;
    region m_region;
};

#endif // TRAFFICLIGHT_H

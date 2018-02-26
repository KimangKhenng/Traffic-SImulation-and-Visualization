#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "lightwidget.h"
#include "lightwidgetleft.h"
#include "commonenum.h"
#include <QtCore>
#include <QtWidgets>

class TrafficLight :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
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
    void setDuration(const int &left,const int &yellow,const int &green);
    void setInitialState(const STATE_MACHINE& state);
    void startTrafficLight();
    void stopTrafficLight();
    LightWidget *getMainGreen() const;
    LightWidget *getMainRed() const;
    LightWidget *getMainYellow() const;
    LightWidget *getLeftGreen() const;
//protected:
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void hoverEnterEvent(QGraphicsSceneHoverEvent *event) Q_DECL_OVERRIDE;
    QList<LightWidget *> *getLight() const;

    void setRegion(const region &region);

    TRAFFICMODE getMode() const;
    void setMode(const TRAFFICMODE &mode);

private:
    QState *makeState(LightWidget *light, int duration,QState *parent = 0);
    int m_red_duration;
    int m_left_duration;
    int m_main_green_duration;
    int m_yellow_duration;
    LightWidget *m_main_light_green;
    LightWidget *m_main_light_red;
    LightWidget *m_main_light_yellow;
    LightWidget *m_left_light;
    QList<LightWidget *> *m_light;
    region m_region;
    TRAFFICMODE m_mode;
    QState *m_MainGreen_Going_Left;
    QState *m_Left_Going_Yellow;
    QState *m_Yellow_Going_Red;
    QState *m_Red_Going_Yellow;
    QState *m_Yellow_Going_Green;
    QStateMachine *m_state_machine;
};

#endif // TRAFFICLIGHT_H

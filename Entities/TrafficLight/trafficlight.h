#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QState>
#include <QStateMachine>
#include <QFinalState>
#include "lightwidget.h"
#include "lightwidgetleft.h"
#include "commonenum.h"


class TrafficLight :public QObject, public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    //Override
    TrafficLight(region re,QGraphicsItem *parent = nullptr);
    TrafficLight(QGraphicsItem *parent = nullptr);
    ~TrafficLight() override;
    //@Override
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;

    region getRegion();
    bool checkDir(Direction dir);
    void setManualControl();
    void setUpFacilities();
    void setDuration(const int &left,const int &yellow,const int &green,const int &red);
    void setInitialState(const STATE_MACHINE& state);
    void startTrafficLight();
    void stopTrafficLight();
    LightWidget *getMainGreen() const;
    LightWidget *getMainRed() const;
    LightWidget *getMainYellow() const;
    LightWidget *getLeftGreen() const;
    QList<LightWidget *> *getLight() const;

    void setRegion(const region &region);

    TRAFFICMODE getMode() const;
    void setMode(const TRAFFICMODE &mode);
    void turnOffInteraction();
    void turnOnInteraction();
protected:
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
private:
    QState *makeState(LightWidget *light, int duration,QState *parent = nullptr);
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

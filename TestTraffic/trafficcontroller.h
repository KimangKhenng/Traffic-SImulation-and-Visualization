#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "trafficlight.h"
#include "lightwidget.h"
#include <QtCore>
#include <QtWidgets>
class TrafficController
{
public:
    TrafficController(QList<TrafficLight *> *light);
    void setLight(QList<TrafficLight *> *light);
    void turnTrafficOn();
    void turnTrafficOff();
private:
    QState *makeState(LightWidget *light, int duration);
    QStateMachine *m_state;
    QList<TrafficLight *> *m_traffic_light;
    QList<QState *> *m_state_list;
};

#endif // TRAFFICCONTROLLER_H

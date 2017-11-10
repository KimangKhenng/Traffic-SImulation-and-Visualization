#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "trafficlight.h"
#include "lightwidget.h"
#include "trafficdetector.h"
#include <QtCore>
#include <QtWidgets>
class TrafficController : public QGraphicsItemGroup
{
public:
    TrafficController(QGraphicsItemGroup *parent = 0);
    TrafficLight *getTrafficLight(region r);
    void turnTrafficOn();
    void turnTrafficOff();
    QList<TrafficDetector *> *getDetector() const;
    void setDetector(QList<TrafficDetector *> *detector);
    QList<TrafficLight *> *getTraffic_light() const;
    void setTraffic_light(QList<TrafficLight *> *traffic_light);

private:
    QState *makeState(LightWidget *light, int duration);
    QState *first_phase();
    QState *second_phase();
    QState *third_phase();
    QState *fourth_phase();
    QStateMachine *m_state;
    QList<TrafficLight *> *m_traffic_light;
    QList<QState *> *m_state_list;
    QList<TrafficDetector *> *m_detector;
};

#endif // TRAFFICCONTROLLER_H

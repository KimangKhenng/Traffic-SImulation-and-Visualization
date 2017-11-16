#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "trafficlight.h"
#include "lightwidget.h"
#include "trafficdetector.h"
#include "commonenum.h"
#include <QtCore>
#include <QtWidgets>
class TrafficController : public QGraphicsItemGroup
{
public:
    TrafficController(QGraphicsItemGroup *parent = 0);
    TrafficLight *getTrafficLight(region r);
    void turnTrafficOn();
    void turnTrafficOff();
    void turnOffDetector();
    void turnOnDetector();
    QList<TrafficDetector *> *getDetector() const;
    QList<TrafficDetector *> *getDetectorByRegion(region x) const;
    void setDetector(QList<TrafficDetector *> *detector);
    QList<TrafficLight *> *getTraffic_light() const;
    void setTraffic_light(QList<TrafficLight *> *traffic_light);
    QList<QElapsedTimer *> *getTimer();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
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

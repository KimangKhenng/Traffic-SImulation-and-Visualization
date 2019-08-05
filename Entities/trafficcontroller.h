#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "TrafficLight/trafficlight.h"
#include "TrafficLight/lightwidget.h"
#include "trafficdetector.h"
#include "commonenum.h"


class TrafficController : public QGraphicsItemGroup
{
public:
    TrafficController(QGraphicsItemGroup *parent = nullptr);
    TrafficLight* getTrafficLight(region r);
    //void turnTrafficOn();
    //void turnTrafficOff();
    void turnOffDetector();
    void turnOnDetector();
    void showDetector();
    void hideDetector();
    void startTrafficLightAll();
    void stopTrafficLightAll();
    void manualControl();
    void setLightDuration(const int& green,const int& left, const int& yellow,const int& red);
    QList<TrafficDetector *> getDetector();
    QList<TrafficDetector *> getDetectorByRegion(region x) const;

    QList<TrafficLight *> getTraffic_light();

    QList<QElapsedTimer *> *getTimer();
    void updateDetectors();
    void turnOffLightInteraction();
    void turnOnLightInteraction();

private:
    //QStateMachine *m_state;
    QList<TrafficLight *> m_traffic_light;
    QList<QState *> *m_state_list;
    QList<TrafficDetector *> m_detector;
};

#endif // TRAFFICCONTROLLER_H

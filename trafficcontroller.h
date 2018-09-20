#ifndef TRAFFICCONTROLLER_H
#define TRAFFICCONTROLLER_H

#include "trafficlight.h"
#include "lightwidget.h"
#include "trafficdetector.h"
#include "commonenum.h"

class TrafficController : public QGraphicsItemGroup
{
public:
    TrafficController(QGraphicsItemGroup *parent = nullptr);
    TrafficLight *getTrafficLight(region r);
    //void turnTrafficOn();
    //void turnTrafficOff();
    void turnOffDetector();
    void turnOnDetector();
    void startTrafficLightAll();
    void stopTrafficLightAll();
    void manualControl();
    void setLightDuration(const int& green,const int& left, const int& yellow);
    QList<TrafficDetector *> *getDetector() const;
    QList<TrafficDetector *> *getDetectorByRegion(region x) const;
    void setDetector(QList<TrafficDetector *> *detector);
    QList<TrafficLight *> *getTraffic_light() const;
    void setTraffic_light(QList<TrafficLight *> *traffic_light);
    QList<QElapsedTimer *> *getTimer();
protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) Q_DECL_OVERRIDE;
private:
    //QStateMachine *m_state;
    QList<TrafficLight *> *m_traffic_light;
    QList<QState *> *m_state_list;
    QList<TrafficDetector *> *m_detector;
};

#endif // TRAFFICCONTROLLER_H

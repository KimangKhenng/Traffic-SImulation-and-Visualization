#ifndef SIMULATIONSCENE_H
#define SIMULATIONSCENE_H
#include <QtCore>
#include <QtWidgets>
#include "commonenum.h"
#include "vehicle.h"
#include "trafficdetector.h"
class SimulationScene: public QGraphicsScene
{

public:
    SimulationScene();
    int getNumber(const region &x) const;
    QList<Vehicle *> getVehicle() const;
    QList<TrafficLight *> getTrafficLight(const region &r) const;
    QList<TrafficDetector *> getDetector() const;
    void trunOffAllCar();
    void setGoThrought(bool x);
//protected:
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // SIMULATIONSCENE_H

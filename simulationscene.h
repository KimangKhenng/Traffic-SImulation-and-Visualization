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
    int getNumber(region x);
    QList<Vehicle *> getVehicle();
    QList<TrafficDetector *> getDetector();
//protected:
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // SIMULATIONSCENE_H

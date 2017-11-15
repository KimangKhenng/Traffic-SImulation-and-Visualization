#ifndef SIMULATIONSCENE_H
#define SIMULATIONSCENE_H
#include <QtCore>
#include <QtWidgets>
#include "commonenum.h"
#include "vehicle.h"
class SimulationScene: public QGraphicsScene
{

public:
    SimulationScene();
    int getNumber(region x);
//protected:
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // SIMULATIONSCENE_H

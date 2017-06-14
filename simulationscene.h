#ifndef SIMULATIONSCENE_H
#define SIMULATIONSCENE_H
#include <QtCore>
#include <QtWidgets>

class SimulationScene: public QGraphicsScene
{

public:
    SimulationScene();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
};

#endif // SIMULATIONSCENE_H

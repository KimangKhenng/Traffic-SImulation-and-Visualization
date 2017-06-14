#include "simulationscene.h"

SimulationScene::SimulationScene()
{
setItemIndexMethod(QGraphicsScene::NoIndex);
}

void SimulationScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<event->scenePos();
    qDebug()<<sceneRect();
}

#include "simulationscene.h"

SimulationScene::SimulationScene()
{
setItemIndexMethod(QGraphicsScene::NoIndex);
setBackgroundBrush (Qt::Dense7Pattern);
}

void SimulationScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<event->scenePos();
    //qDebug()<<sceneRect();
}

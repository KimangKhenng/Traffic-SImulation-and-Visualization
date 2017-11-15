#include "simulationscene.h"

SimulationScene::SimulationScene()
{
    /////////////////
    ///
    /// Set Index Method of How QGraphicsScene
    /// Should manage item
    /// NoIndex is good for dynamic scene
    setItemIndexMethod(QGraphicsScene::NoIndex);
    /////////////////
    ///
    /// Set background brush for scene
    setBackgroundBrush (Qt::Dense5Pattern);
}

int SimulationScene::getNumber(region x)
{
    int size = 0;
    QList<QGraphicsItem *> v = this->items();
    QList<Vehicle *> p;
    for(int i = 0 ; i < v.size() ; ++i){
        if(dynamic_cast<Vehicle *>(v.at(i))){
            p.append(dynamic_cast<Vehicle *>(v.at(i)));
        }
    }
    for(int i = 0 ; i < p.size() ; ++i){
        if(p.at(i)->getRegion() == x){
            size++;
        }
    }
    return size;
}

//void SimulationScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
//{
//    QGraphicsScene::mousePressEvent(mouseEvent);
//    qDebug()<<"Hi";
//}

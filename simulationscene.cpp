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
    setBackgroundBrush (Qt::white);
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

QList<Vehicle *> SimulationScene::getVehicle()
{
    QList<QGraphicsItem *> v = this->items();
    QList<Vehicle *> p;
    for(int i = 0 ; i < v.size() ; ++i){
        if(dynamic_cast<Vehicle *>(v.at(i))){
            p.append(dynamic_cast<Vehicle *>(v.at(i)));
        }
    }
    return p;
}

QList<TrafficDetector *> SimulationScene::getDetector()
{
    QList<QGraphicsItem *> v = this->items();
    QList<TrafficDetector *> d;
    for(int i = 0 ; i < v.size() ; ++i){
        if(dynamic_cast<TrafficDetector *>(v.at(i))){
            d.append(dynamic_cast<TrafficDetector *>(v.at(i)));
        }
    }
    return d;
}

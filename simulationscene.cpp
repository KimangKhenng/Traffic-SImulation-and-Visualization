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
    setBackgroundBrush (Qt::gray);
}

int SimulationScene::getNumber(const region &x) const
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

QList<Vehicle *> SimulationScene::getVehicle() const
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

QList<TrafficDetector *> SimulationScene::getDetector() const
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

QList<TrafficLight *> SimulationScene::getTrafficLight(const region &r) const
{
    QList<TrafficLight *> light_list;
    for(int i = 0 ; i < this->items().length() ; ++i){
        if(dynamic_cast<TrafficLight *>(this->items().at(i))){
            if(dynamic_cast<TrafficLight *>(this->items().at(i))->getRegion() == r){
                light_list.append(dynamic_cast<TrafficLight *>(this->items().at(i)));
            }
        }
    }
    return light_list;
}

void SimulationScene::trunOffAllCar()
{
    for(int i = 0 ; i < this->getVehicle().size() ; ++i){
        this->getVehicle().at(i)->setActionOff();
    }
}

void SimulationScene::setGoThrought(bool x)
{
    if(x){
        for(int i = 0 ; i < getVehicle().size() ; ++i){
            getVehicle().at(i)->setMode(VEHICLEMETHOD::GO_THROUGH);
        }
    }else{
        for(int i = 0 ; i < getVehicle().size() ; ++i){
            getVehicle().at(i)->setMode(VEHICLEMETHOD::SIGHTSEEING);
        }
    }
}

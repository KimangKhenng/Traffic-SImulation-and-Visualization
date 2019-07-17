#include "simulationscene.h"

SimulationScene::SimulationScene(QGraphicsScene *parent):QGraphicsScene (parent)
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
    m_Controller = new TrafficController;
    this->addItem(m_Controller);

}

uint SimulationScene::getNumber(const region &x) const
{
    uint size = 0;
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
    return m_Vehicles;
}

QList<Vehicle *> SimulationScene::getVehicle(const region &r) const
{
    QList<Vehicle* > ve;
    for(size_t i = 0 ; i < m_Vehicles.size() ; ++i ){
        if(m_Vehicles.at(i)->getRegion() == r){
            ve.append(m_Vehicles.at(i));
        }
    }
    return ve;
}

QList<TrafficDetector *> SimulationScene::getDetector() const
{
    return m_Controller->getDetector();
}

void SimulationScene::addVehicle(Vehicle *vehicle)
{
    m_Vehicles.append(vehicle);
    this->addItem(vehicle);
}


void SimulationScene::removeVehicle(Vehicle *ve)
{
    m_Vehicles.removeOne(ve);
    this->removeItem(ve);
    delete ve;
}

TrafficLight * SimulationScene::getTrafficLight(const region &r) const
{
    return m_Controller->getTrafficLight(r);
}

QList<TrafficLight *> SimulationScene::getTrafficLight() const
{
    return m_Controller->getTraffic_light();
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

void SimulationScene::resetScene()
{
    for(int i = 0 ; i < this->getVehicle().size() ; i++){
       this->removeItem(this->getVehicle().at(i));
       //delete this->getVehicle().at(i);
    }
    for(int i = 0 ; i < this->getTrafficLight().size() ; i++){
        this->removeItem(this->getTrafficLight().at(i));
    }
}

void SimulationScene::showTrafficLight()
{
    for(size_t i = 0 ; i < m_Controller->getTraffic_light().size() ; ++i){
        m_Controller->getTraffic_light().at(i)->setMode(TRAFFICMODE::HAS_SIGNAL);
        this->addItem(m_Controller->getTraffic_light().at(i));
    }
}

void SimulationScene::HideTrafficLight()
{
    for(int i = 0 ; i < m_Controller->getTraffic_light().size() ; ++i){
        m_Controller->getTraffic_light().at(i)->setMode(TRAFFICMODE::NO_SIGNAL);
        this->removeItem(m_Controller->getTraffic_light().at(i));
    }
}

TrafficController *SimulationScene::getController() const
{
    return m_Controller;
}

#include "simulationscene.h"

SimulationScene::SimulationScene(QGraphicsScene *parent):QGraphicsScene (parent)
{
    //Add Road and Background to scene
    //QGraphicsPixmapItem *m_picture = new QGraphicsPixmapItem(QPixmap(":/image/Image/road-image.png")/*.scaled (600,600)*/);
    QGraphicsSvgItem *m_terrain = new QGraphicsSvgItem(":/image/Image/terrain.svg");
    m_terrain->setFlag(QGraphicsItem::ItemIsMovable,false);
    m_terrain->setFlag(QGraphicsItem::ItemIsSelectable,false);
    m_path = new QGraphicsSvgItem(":/image/Image/road-path.svg");
    m_path->setFlag(QGraphicsItem::ItemIsMovable,false);
    m_path->setFlag(QGraphicsItem::ItemIsSelectable,false);
    //m_terrain->moveBy (-60,0);
    //m_picture->moveBy(30,0);
    m_path->moveBy (15,-15);
    m_path->setScale (0.7);
    m_path->setZValue (-1);
    m_path->setOpacity(0);
    //m_picture->setZValue (-2);
    m_terrain->setZValue (-3);
    m_terrain->moveBy(-70,5);
    this->addItem (m_terrain);
    this->addItem (m_path);

    setItemIndexMethod(QGraphicsScene::NoIndex);

    setBackgroundBrush (Qt::white);
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


void SimulationScene::setGoThrough(bool x)
{
    if(x){
        for(int i = 0 ; i < m_Vehicles.size() ; ++i){
            m_Vehicles.at(i)->setMode(VEHICLEMETHOD::GO_THROUGH);
        }
    }else{
        for(int i = 0 ; i < getVehicle().size() ; ++i){
            m_Vehicles.at(i)->setMode(VEHICLEMETHOD::SIGHTSEEING);
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
    for(int i = 0 ; i < m_Controller->getTraffic_light().size() ; ++i){
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

void SimulationScene::showIntersectionPath(const bool &show)
{
    if(show){
        m_path->setOpacity(100);
    }else{
        m_path->setOpacity(0);
    }
}

void SimulationScene::showDetectors()
{
    m_Controller->showDetector();
}

void SimulationScene::hideDetectors()
{
    m_Controller->hideDetector();
}

void SimulationScene::turnOffDetectors()
{
    m_Controller->turnOffDetector();
}

void SimulationScene::turnOnDetectors()
{
    m_Controller->turnOnDetector();
}

void SimulationScene::showVehiclesVision()
{
    for(int i = 0 ; i < m_Vehicles.size() ; ++i){
        m_Vehicles.at(i)->turnOnSightSeeing();
    }
}

void SimulationScene::hideVehiclesVision()
{
    for(int i = 0 ; i < m_Vehicles.size() ; ++i){
        m_Vehicles.at(i)->turnOffSightSeeing();
    }
}

TrafficController *SimulationScene::getController() const
{
    return m_Controller;
}

void SimulationScene::updateScene(const VEHICLEMETHOD &seeing)
{
#if PARALLEL_OMP

    omp_set_num_threads(4);
    #pragma omp parallel private(m_Vehicles)
    {

        for(auto i = m_Vehicles.begin() ; i != m_Vehicles.end() ; ++i){
            #pragma omp single nowait
            {
                (*i)->update(seeing);

            }
        }
    }
    #pragma omp parallel for
    for(size_t i = 0 ; i < m_Vehicles.size() ; ++i ){
        if(m_Vehicles.at(i)->isDeletable()){
            removeVehicle(m_Vehicles.at(i));
        }
    }
#elif PARALLEL_CONCURRENT
    for(int i = 0; i < m_Vehicles.size() ; ++i){

        QFuture<void> f = QtConcurrent::run(m_Vehicles.at(i),&Vehicle::update,seeing);

    }
#else
    advance();
    for(size_t i = 0 ; i < m_Vehicles.size() ; ++i ){
        if(m_Vehicles.at(i)->isDeletable()){
            removeVehicle(m_Vehicles.at(i));
        }
    }
#endif
}

void SimulationScene::turnOffInteraction()
{
    for(int i = 0 ; i < m_Vehicles.size() ; ++i){
        m_Vehicles.at(i)->turnOffInteraction();
    }
    m_Controller->turnOffLightInteraction();


}

void SimulationScene::turnOnInteraction()
{
    for(int i = 0 ; i < m_Vehicles.size() ; ++i){
        m_Vehicles.at(i)->turnOnInteraction();
    }
    m_Controller->turnOnLightInteraction();
}

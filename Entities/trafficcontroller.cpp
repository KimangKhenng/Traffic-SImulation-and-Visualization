#include "trafficcontroller.h"

TrafficController::TrafficController(QGraphicsItemGroup *parent):QGraphicsItemGroup(parent)
{
    //m_state = new QStateMachine();
    // ArrageDetector
    setAcceptHoverEvents(true);
    for(int i = 0 ; i < 12 ; ++i){
        m_detector.append(new TrafficDetector(LENGTH));
    }
    QPointF p1(364,380);
    QPointF p2(364-15,380);
    QPointF p3(364-30,380);
    // Detector 12,11,10
    QGraphicsItemGroup *group1 = new QGraphicsItemGroup();
    for(int i = 0 ; i < 3 ; ++i){
        group1->addToGroup(m_detector.at(i));
    }
    this->addToGroup(group1);
    m_detector.at(0)->setPos(p1);
    m_detector.at(1)->setPos(p2);
    m_detector.at(2)->setPos(p3);
    // Detector 9,8,7
    QGraphicsItemGroup *group2 = new QGraphicsItemGroup();
    for(int i = 3 ; i < 6 ; ++i){
        group2->addToGroup(m_detector.at(i));
    }
    this->addToGroup(group2);
    m_detector.at(3)->setPos(p1);
    m_detector.at(4)->setPos(p2);
    m_detector.at(5)->setPos(p3);
    group2->setRotation(90);
    group2->moveBy(628,-30);
    // Detector 6,5,4
    QGraphicsItemGroup *group3 = new QGraphicsItemGroup();
    for(int i = 6 ; i < 9 ; ++i){
        group3->addToGroup(m_detector.at(i));
    }
    this->addToGroup(group3);
    m_detector.at(6)->setPos(p1);
    m_detector.at(7)->setPos(p2);
    m_detector.at(8)->setPos(p3);
    group3->setRotation(90);
    group3->moveBy(870,-75.5);
    // Detector 3,2,1
    QGraphicsItemGroup *group4 = new QGraphicsItemGroup();
    for(int i = 9 ; i < 12 ; ++i){
        group4->addToGroup(m_detector.at(i));
    }
    this->addToGroup(group4);
    m_detector.at(9)->setPos(p1);
    m_detector.at(10)->setPos(p2);
    m_detector.at(11)->setPos(p3);
    group4->moveBy(-49,-243);
    //Create Traffic Light

    for(int i = 0 ; i < 4 ; ++i){
        m_traffic_light.append(new TrafficLight());
        m_traffic_light.at(i)->setUpFacilities();
    }
    //Arrange Traffic Light
    //TrafficLight 1
    m_traffic_light.at(0)->setPos(400,380);
    m_traffic_light.at(0)->setRegion(region::REGION_S_N);
    //m_traffic_light->at(0)->setInitialState(STATE_MACHINE::Green_Going_Left);
    //TrafficLight 2
    m_traffic_light.at(1)->setRotation(90);
    m_traffic_light.at(1)->setPos(260,380);
    m_traffic_light.at(1)->setRegion(region::REGION_W_E);
    //m_traffic_light->at(1)->setInitialState(STATE_MACHINE::Red_Going_Yellow);
    //TrafficLight 3
    m_traffic_light.at(2)->setPos(250,240);
    m_traffic_light.at(2)->setRotation(180);
    m_traffic_light.at(2)->setRegion(region::REGION_N_S);
    //m_traffic_light->at(2)->setInitialState(STATE_MACHINE::Green_Going_Left);
//    m_traffic_light->at(2)->setTransform(QTransform::fromScale(1, -1));
    //TrafficLight 4
    m_traffic_light.at(3)->setPos(410,230);
    m_traffic_light.at(3)->setRotation(270);
    m_traffic_light.at(3)->setRegion(region::REGION_E_W);
    //m_traffic_light->at(3)->setInitialState(STATE_MACHINE::Red_Going_Yellow);
    //m_traffic_light->at(3)->setTransform(QTransform::fromScale(-1, 1));
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        for(int j = 0 ; j < m_traffic_light.at(i)->getLight()->size() ; j++){
            m_traffic_light.at(i)->getLight()->at(j)->setScale(0.8);
        }
    }
    for(size_t i = 0 ; i < getDetector().size() ; ++i){
        getDetector().at(i)->setOpacity(0);
    }
}
TrafficLight *TrafficController::getTrafficLight(region r)
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        if(m_traffic_light.at(i)->getRegion() == r){
            return m_traffic_light.at(i);
        }
    }
    return nullptr;
}

//void TrafficController::turnTrafficOn()
//{
//    if(!m_state){
//        return;
//    }
//    m_state->start();
//}

//void TrafficController::turnTrafficOff()
//{
//    if(!m_state){
//        return;
//    }
//    m_state->stop();
//}

void TrafficController::turnOffDetector()
{
    for(int i = 0 ; i < m_detector.size() ; ++i){
        m_detector.at(i)->turnOff();
    }
}

void TrafficController::turnOnDetector()
{
    for(int i = 0 ; i < m_detector.size() ; ++i){
        m_detector.at(i)->turnOn();
    }
}

void TrafficController::showDetector()
{
    for(int i = 0 ; i < m_detector.size() ; ++i){
        m_detector.at(i)->turnOnDisplay();
    }
}

void TrafficController::hideDetector()
{
    for(int i = 0 ; i < m_detector.size() ; ++i){
        m_detector.at(i)->turnOffDisplay();
    }
}

void TrafficController::startTrafficLightAll()
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->startTrafficLight();
        m_traffic_light.at(i)->setMode(TRAFFICMODE::HAS_SIGNAL);
    }
}

void TrafficController::stopTrafficLightAll()
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->stopTrafficLight();
        m_traffic_light.at(i)->setMode(TRAFFICMODE::NO_SIGNAL);
    }
}

void TrafficController::manualControl()
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->stopTrafficLight();
        m_traffic_light.at(i)->setMode(TRAFFICMODE::HAS_SIGNAL);
    }
}

void TrafficController::setLightDuration(const int &green, const int &left, const int &yellow, const int &red)
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->setDuration(left,yellow,green,red);
    }
    m_traffic_light.at(0)->setInitialState(STATE_MACHINE::Green_Going_Left);
    m_traffic_light.at(1)->setInitialState(STATE_MACHINE::Red_Going_Yellow);
    m_traffic_light.at(2)->setInitialState(STATE_MACHINE::Green_Going_Left);
    m_traffic_light.at(3)->setInitialState(STATE_MACHINE::Red_Going_Yellow);
}

QList<TrafficLight *> TrafficController::getTraffic_light()
{
    return m_traffic_light;
}



QList<QElapsedTimer *> *TrafficController::getTimer()
{
    QList<QElapsedTimer *> *time = new QList<QElapsedTimer *>();
    for(int i = 0 ; i < m_detector.size() ; i++){
        time->append(m_detector.at(i)->getTimer());
    }
    return time;
}

void TrafficController::updateDetectors()
{
    for(int i = 0 ; i < m_detector.size() ; ++i){
        m_detector.at(i)->forward();
    }
}

void TrafficController::turnOffLightInteraction()
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->turnOffInteraction();
    }
}

void TrafficController::turnOnLightInteraction()
{
    for(int i = 0 ; i < m_traffic_light.size() ; ++i){
        m_traffic_light.at(i)->turnOnInteraction();
    }
}


QList<TrafficDetector *> TrafficController::getDetector()
{
    return m_detector;
}

QList<TrafficDetector *> TrafficController::getDetectorByRegion(region x) const
{
    QList<TrafficDetector *> d;
    switch (x) {
        case region::REGION_S_N :
            for(int i = 0 ; i < 3 ; ++i){
                d.append(m_detector.at(i));
            }
            return d;
        case region::REGION_W_E :
            for(int i = 3 ; i < 6 ; ++i){
                d.append(m_detector.at(i));
            }
            return d;
        case region::REGION_N_S :
            for(int i = 6 ; i < 9 ; ++i){
                d.append(m_detector.at(i));
            }
            return d;
        case region::REGION_E_W :
            for(int i = 9 ; i < 12 ; ++i){
                d.append(m_detector.at(i));
            }
            return d;
    }
    return d;
}

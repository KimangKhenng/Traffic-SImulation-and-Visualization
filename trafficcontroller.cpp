#include "trafficcontroller.h"

TrafficController::TrafficController(QGraphicsItemGroup *parent):QGraphicsItemGroup(parent)
{
    m_state = new QStateMachine();
    m_traffic_light = new QList<TrafficLight *>();
    for(int i = 0 ; i < 4 ; ++i){
        m_traffic_light->append(new TrafficLight(static_cast<region>(i)));
    }
    //Arrange Traffic Light
    //TrafficLight 1
    m_traffic_light->at(0)->setPos(400,380);
    this->addToGroup(m_traffic_light->at(0));
    //TrafficLight 2
    m_traffic_light->at(1)->setRotation(90);
    m_traffic_light->at(1)->setPos(260,380);
    this->addToGroup(m_traffic_light->at(1));
    //TrafficLight 3
    m_traffic_light->at(2)->setPos(160,220);
    this->addToGroup(m_traffic_light->at(2));
    //TrafficLight 4
    m_traffic_light->at(3)->setRotation(90);
    m_traffic_light->at(3)->setPos(420,140);
    this->addToGroup(m_traffic_light->at(3));
    // ArrageDetector
    m_detector = new QList<TrafficDetector *>();
    for(int i = 0 ; i < 12 ; ++i){
        m_detector->append(new TrafficDetector(LENGTH));
    }
    QPointF p1(364,365);
    QPointF p2(364-15,365);
    QPointF p3(364-30,365);
    // Detector 12,11,10
    QGraphicsItemGroup *group1 = new QGraphicsItemGroup();
    for(int i = 0 ; i < 3 ; ++i){
        group1->addToGroup(m_detector->at(i));
    }
    this->addToGroup(group1);
    m_detector->at(0)->setPos(p1);
    m_detector->at(1)->setPos(p2);
    m_detector->at(2)->setPos(p3);
    // Detector 9,8,7
    QGraphicsItemGroup *group2 = new QGraphicsItemGroup();
    for(int i = 3 ; i < 6 ; ++i){
        group2->addToGroup(m_detector->at(i));
    }
    this->addToGroup(group2);
    m_detector->at(3)->setPos(p1);
    m_detector->at(4)->setPos(p2);
    m_detector->at(5)->setPos(p3);
    group2->setRotation(90);
    group2->moveBy(629,-30);
    // Detector 6,5,4
    QGraphicsItemGroup *group3 = new QGraphicsItemGroup();
    for(int i = 6 ; i < 9 ; ++i){
        group3->addToGroup(m_detector->at(i));
    }
    this->addToGroup(group3);
    m_detector->at(6)->setPos(p1);
    m_detector->at(7)->setPos(p2);
    m_detector->at(8)->setPos(p3);
    group3->setRotation(90);
    group3->moveBy(840,-80);
    // Detector 3,2,1
    QGraphicsItemGroup *group4 = new QGraphicsItemGroup();
    for(int i = 9 ; i < 12 ; ++i){
        group4->addToGroup(m_detector->at(i));
    }
    this->addToGroup(group4);
    m_detector->at(9)->setPos(p1);
    m_detector->at(10)->setPos(p2);
    m_detector->at(11)->setPos(p3);
    group4->moveBy(-49,-213);




}
TrafficLight *TrafficController::getTrafficLight(region r)
{
    for(int i = 0 ; i < m_traffic_light->size() ; ++i){
        if(m_traffic_light->at(i)->getRegion() == r){
            return m_traffic_light->at(i);
        }
    }
    return nullptr;
}

void TrafficController::turnTrafficOn()
{
    if(!m_state){
        return;
    }
    m_state->start();
}

void TrafficController::turnTrafficOff()
{
    if(!m_state){
        return;
    }
    m_state->stop();
}

QState *TrafficController::makeState(LightWidget *light, int duration)
{
    QState *lightState = new QState();
    QTimer *timer = new QTimer(lightState);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState *timing = new QState(lightState);
    QObject::connect(timing,SIGNAL(entered()),light,SLOT(turnOn()));
    QObject::connect(timing,SIGNAL(entered()),timer,SLOT(start()));
    QObject::connect(timing,SIGNAL(exit()),light,SLOT(turnOff()));
    QFinalState *done = new QFinalState(lightState);
    timing->addTransition(timer,SIGNAL(timeout()),done);
    lightState->setInitialState(timing);
    return lightState;
}

QList<TrafficLight *> *TrafficController::getTraffic_light() const
{
    return m_traffic_light;
}

void TrafficController::setTraffic_light(QList<TrafficLight *> *traffic_light)
{
    m_traffic_light = traffic_light;
}

QList<TrafficDetector *> *TrafficController::getDetector() const
{
    return m_detector;
}

void TrafficController::setDetector(QList<TrafficDetector *> *detector)
{
    m_detector = detector;
}

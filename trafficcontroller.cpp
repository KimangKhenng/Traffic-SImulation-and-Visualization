#include "trafficcontroller.h"

TrafficController::TrafficController(QGraphicsItemGroup *parent):QGraphicsItemGroup(parent)
{
    m_state = new QStateMachine();
    // ArrageDetector
    m_detector = new QList<TrafficDetector *>();
    for(int i = 0 ; i < 12 ; ++i){
        m_detector->append(new TrafficDetector(LENGTH));
    }
    QPointF p1(364,380);
    QPointF p2(364-15,380);
    QPointF p3(364-30,380);
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
    group2->moveBy(628,-30);
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
    group3->moveBy(870,-80);
    // Detector 3,2,1
    QGraphicsItemGroup *group4 = new QGraphicsItemGroup();
    for(int i = 9 ; i < 12 ; ++i){
        group4->addToGroup(m_detector->at(i));
    }
    this->addToGroup(group4);
    m_detector->at(9)->setPos(p1);
    m_detector->at(10)->setPos(p2);
    m_detector->at(11)->setPos(p3);
    group4->moveBy(-49,-243);
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

void TrafficController::turnOffDetector()
{
    for(int i = 0 ; i < m_detector->size() ; ++i){
        m_detector->at(i)->setOpacity(0.0);
    }
}

void TrafficController::turnOnDetector()
{
    for(int i = 0 ; i < m_detector->size() ; ++i){
        m_detector->at(i)->setOpacity(1.0);
    }
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

QState *TrafficController::first_phase()
{
    return nullptr;
}

QState *TrafficController::second_phase()
{
    return nullptr;
}

QState *TrafficController::third_phase()
{
    return nullptr;
}

QState *TrafficController::fourth_phase()
{
    return nullptr;
}

QList<TrafficLight *> *TrafficController::getTraffic_light() const
{
    return m_traffic_light;
}

void TrafficController::setTraffic_light(QList<TrafficLight *> *traffic_light)
{
    m_traffic_light = traffic_light;
}

QList<QElapsedTimer *> *TrafficController::getTimer()
{
    QList<QElapsedTimer *> *time = new QList<QElapsedTimer *>();
    for(int i = 0 ; i < m_detector->size() ; i++){
        time->append(m_detector->at(i)->getTimer());
    }
    return time;
}

void TrafficController::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //qDebug()<<"Hello";
    QGraphicsItem::mousePressEvent(event);
}

QList<TrafficDetector *> *TrafficController::getDetector() const
{
    return m_detector;
}

QList<TrafficDetector *> *TrafficController::getDetectorByRegion(region x) const
{
    QList<TrafficDetector *> *d = new QList<TrafficDetector *>();
    switch (x) {
        case region::REGION_S_N :
            for(int i = 0 ; i < 3 ; ++i){
                d->append(m_detector->at(i));
            }
            return d;
        case region::REGION_W_E :
            for(int i = 3 ; i < 6 ; ++i){
                d->append(m_detector->at(i));
            }
            return d;
        case region::REGION_N_S :
            for(int i = 6 ; i < 9 ; ++i){
                d->append(m_detector->at(i));
            }
            return d;
        case region::REGION_E_W :
            for(int i = 9 ; i < 12 ; ++i){
                d->append(m_detector->at(i));
            }
            return d;
    }
    return nullptr;
}

void TrafficController::setDetector(QList<TrafficDetector *> *detector)
{
    m_detector = detector;
}

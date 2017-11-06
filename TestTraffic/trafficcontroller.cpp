#include "trafficcontroller.h"

TrafficController::TrafficController(QList<TrafficLight *> *light):m_traffic_light(light)
{
    m_state = new QStateMachine();
}


void TrafficController::setLight(QList<TrafficLight *> *light)
{
    m_traffic_light = light;
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

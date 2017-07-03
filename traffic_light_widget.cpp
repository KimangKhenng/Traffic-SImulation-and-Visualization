#include "traffic_light_widget.h"
#include <QtWidgets>
#include "mainwindow.h"
Traffic_Light_widget::Traffic_Light_widget(QWidget *parent):QWidget(parent)
{
    this->setGeometry (0,0,35,80);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    m_traffic_light = new TrafficLight();
    vbox->addWidget(m_traffic_light);
    vbox->setMargin(0);

}
void Traffic_Light_widget::set_duration(int red, int yello, int green)
{
    m_red_duration = red;
    m_yellow_duration = yello;
    m_green_duration = green;
}

void Traffic_Light_widget::set_up()
{
    m_machine = new QStateMachine(this);
    QState *redGoingYellow = make_light_state(m_traffic_light->redLight(), m_red_duration);
    redGoingYellow->setObjectName("redGoingYellow");
    QState *yellowGoingGreen = make_light_state(m_traffic_light->yellowLight(), m_yellow_duration);
    yellowGoingGreen->setObjectName("yellowGoingGreen");
    redGoingYellow->addTransition(redGoingYellow, SIGNAL(finished()), yellowGoingGreen);
    QState *greenGoingYellow = make_light_state(m_traffic_light->greenLight(), m_green_duration);
    greenGoingYellow->setObjectName("greenGoingYellow");
    yellowGoingGreen->addTransition(yellowGoingGreen, SIGNAL(finished()), greenGoingYellow);
    QState *yellowGoingRed = make_light_state(m_traffic_light->yellowLight(), m_yellow_duration);
    yellowGoingRed->setObjectName("yellowGoingRed");
    greenGoingYellow->addTransition(greenGoingYellow, SIGNAL(finished()), yellowGoingRed);
    yellowGoingRed->addTransition(yellowGoingRed, SIGNAL(finished()), redGoingYellow);
    m_machine->addState(redGoingYellow);
    m_machine->addState(yellowGoingGreen);
    m_machine->addState(greenGoingYellow);
    m_machine->addState(yellowGoingRed);
    m_machine->setInitialState(redGoingYellow);
}

void Traffic_Light_widget::start()
{
    m_machine->start();
}

QState *Traffic_Light_widget::make_light_state(LightWidget *light, int duration, QState *parent)
{
    QState *lightState = new QState(parent);
    QTimer *timer = new QTimer(lightState);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState *timing = new QState(lightState);
    QObject::connect(timing, SIGNAL(entered()), light, SLOT(turnOn()));
    QObject::connect(timing, SIGNAL(entered()), timer, SLOT(start()));
    QObject::connect(timing, SIGNAL(exited()), light, SLOT(turnOff()));
    QFinalState *done = new QFinalState(lightState);
    timing->addTransition(timer, SIGNAL(timeout()), done);
    lightState->setInitialState(timing);
    return lightState;
}

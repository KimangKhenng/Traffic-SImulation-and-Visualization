#include "traffic_light_widget.h"
#include <QtWidgets>
#include "mainwindow.h"
Traffic_Light_widget::Traffic_Light_widget(QWidget *parent):QWidget(parent),m_is_check(false)
{
    this->setGeometry (0,0,35,80);
    QVBoxLayout *vbox = new QVBoxLayout(this);
    m_traffic_light = new TrafficLight();
    m_machine = new QStateMachine(this);
    initiate_instance ();
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
    m_redGoingYellow = make_light_state(m_traffic_light->redLight(), m_red_duration);
    m_redGoingYellow->setObjectName("redGoingYellow");
    m_yellowGoingGreen = make_light_state(m_traffic_light->yellowLight(), m_yellow_duration);
    m_yellowGoingGreen->setObjectName("yellowGoingGreen");
    m_redGoingYellow->addTransition(m_redGoingYellow, SIGNAL(finished()), m_yellowGoingGreen);
    m_greenGoingYellow = make_light_state(m_traffic_light->greenLight(), m_green_duration);
    m_greenGoingYellow->setObjectName("greenGoingYellow");
    m_yellowGoingGreen->addTransition(m_yellowGoingGreen, SIGNAL(finished()), m_greenGoingYellow);
    m_yellowGoingRed = make_light_state(m_traffic_light->yellowLight(), m_yellow_duration);
    m_yellowGoingRed->setObjectName("yellowGoingRed");
    m_greenGoingYellow->addTransition(m_greenGoingYellow, SIGNAL(finished()), m_yellowGoingRed);
    m_yellowGoingRed->addTransition(m_yellowGoingRed, SIGNAL(finished()), m_redGoingYellow);

}

void Traffic_Light_widget::start()
{
    m_machine->start();
}

void Traffic_Light_widget::stop()
{
    m_machine->stop ();
//    delete m_redGoingYellow;
//    delete m_yellowGoingGreen;
//    delete m_greenGoingYellow;
//    delete m_yellowGoingRed;

}

void Traffic_Light_widget::initiate_instance()
{
    m_redGoingYellow = new QState();
    m_yellowGoingGreen = new QState();
    m_greenGoingYellow = new QState();
    m_yellowGoingRed = new QState();
}

QState *Traffic_Light_widget::get_current_state()
{
    if(m_machine->configuration ().contains (m_redGoingYellow)){
        return m_redGoingYellow;
    }
    if(m_machine->configuration ().contains (m_greenGoingYellow)){
        return m_greenGoingYellow;
    }
    if(m_machine->configuration ().contains (m_yellowGoingGreen)){
        return m_yellowGoingGreen;
    }
    if(m_machine->configuration ().contains (m_yellowGoingRed)){
        return m_yellowGoingRed;
    }
    return nullptr;
}

QState *Traffic_Light_widget::get_red()
{
    return m_redGoingYellow;
}

QState *Traffic_Light_widget::get_green()
{
    return m_greenGoingYellow;
}

QState *Traffic_Light_widget::get_red_yellow()
{
    return m_yellowGoingRed;
}

QState *Traffic_Light_widget::get_green_yellow()
{
    return m_yellowGoingGreen;
}

bool Traffic_Light_widget::is_running()
{
    return m_machine->isRunning ();
}

void Traffic_Light_widget::mousePressEvent(QMouseEvent *event)
{
    //Make other false
    Q_UNUSED(event);
    m_is_check = true;
    make_other_widget_state_false ();
    if(m_is_check){
        set_opacity (0.5);
    }
}

void Traffic_Light_widget::set_opacity(float num)
{
    setWindowOpacity (num);
}

void Traffic_Light_widget::get_other_widget(QList<Traffic_Light_widget *> *m_traffic)
{
    m_traffic_list = m_traffic;
}

void Traffic_Light_widget::make_other_widget_state_false()
{
    for(int i = 0 ; i<m_traffic_list->size ();i++){
        if(m_traffic_list->at (i) != this){
            m_traffic_list->at (i)->make_state_check (false);
            m_traffic_list->at (i)->set_opacity (1);
        }
    }
}

bool Traffic_Light_widget::get_check_state()
{
    return m_is_check;
}

void Traffic_Light_widget::set_initial_state_nornal()
{
    m_machine->addState(m_redGoingYellow);
    m_machine->addState(m_yellowGoingGreen);
    m_machine->addState(m_greenGoingYellow);
    m_machine->addState(m_yellowGoingRed);
    m_machine->setInitialState(m_redGoingYellow);
}

void Traffic_Light_widget::make_state_check(bool value)
{
    m_is_check = value;
}

void Traffic_Light_widget::set_initial_state(bool red,bool green)
{
    m_machine->addState(m_redGoingYellow);
    m_machine->addState(m_yellowGoingGreen);
    m_machine->addState(m_greenGoingYellow);
    m_machine->addState(m_yellowGoingRed);
    if(red){
        m_machine->setInitialState(m_redGoingYellow);
    }
    if(green){
        m_machine->setInitialState (m_greenGoingYellow);
    }
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

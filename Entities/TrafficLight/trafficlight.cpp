#include "trafficlight.h"

QRectF TrafficLight::boundingRect() const
{
    return QRectF(0,0,WidgetDimension*4,WidgetDimension);
}

void TrafficLight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(QColor("#2c3e50")));
    painter->drawRoundedRect(boundingRect(),8,8);
    //setAcceptHoverEvents(true);
    //painter->drawRect(this->boundingRect());
}

TrafficLight::TrafficLight(region re, QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,m_region(re)
{
}

TrafficLight::TrafficLight(QGraphicsItem *parent)
    :QGraphicsItem (parent)
    ,m_red_duration(0)
    ,m_left_duration(0)
    ,m_main_green_duration(0)
    ,m_yellow_duration(0)
    ,m_mode(TRAFFICMODE::NO_SIGNAL)
    ,m_state_machine(new QStateMachine(this))
{

}

TrafficLight::~TrafficLight()
{

}

region TrafficLight::getRegion()
{
    return m_region;
}

bool TrafficLight::checkDir(Direction dir)
{
    switch (dir) {
    case Direction::LEFT_TURNING :
        //qDebug()<<"Hello";
        return getLeftGreen()->isOn();
    case Direction::RIGHT_TURNING :
        return getMainGreen()->isOn();
//        return true;
    case Direction::THROUGH :
        return getMainGreen()->isOn();
    }
    return false;
}

void TrafficLight::setManualControl()
{
    for(int i = 0 ; i < m_light->size() ; ++i){
        if(i != 3){
            m_light->at(i)->turnOff();
        }else{
            m_light->at(i)->turnOn();
        }
    }
}

void TrafficLight::setUpFacilities()
{
    // Setup light and attach color
    m_left_light = new LightWidgetLeft(QColor("#2ecc71"),this);
    //this->addToGroup(m_left_light);
    m_main_light_green = new LightWidget(QColor("#2ecc71"),this);
    //this->addToGroup(m_main_light_green);
    m_main_light_green->moveBy(LightSize,0);
    m_main_light_yellow = new LightWidget(QColor("#f1c40f"),this);
    //this->addToGroup(m_main_light_yellow);
    m_main_light_yellow->moveBy(LightSize*2,0);
    m_main_light_red = new LightWidget(QColor("#e74c3c"),this);
    //this->addToGroup(m_main_light_red);
    m_main_light_red->moveBy(LightSize*3,0);
    m_light = new QList<LightWidget *>();
    m_light->append(m_left_light);
    m_light->append(m_main_light_green);
    m_light->append(m_main_light_yellow);
    m_light->append(m_main_light_red);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void TrafficLight::setDuration(const int &left, const int &yellow, const int &green, const int &red)
{
    m_red_duration = red;
    m_left_duration = left;
    m_yellow_duration = yellow;
    m_main_green_duration = green;
    // setup state to light
    // Create main green going to left light state
    m_MainGreen_Going_Left = makeState(m_main_light_green,m_main_green_duration);
    m_MainGreen_Going_Left->setObjectName("Main Green Going Left");
    // Create main left going to green light state
    m_Left_Going_Yellow = makeState(m_left_light,m_left_duration);
    m_Left_Going_Yellow->setObjectName("Left Going Yellow");
    // Create yellow green going to red light state
    m_Yellow_Going_Red = makeState(m_main_light_yellow,m_yellow_duration);
    m_Yellow_Going_Red->setObjectName("Yellow Going Red");
    // Create red green going to yellow light state
    m_Red_Going_Yellow = makeState(m_main_light_red,m_red_duration);
    m_Red_Going_Yellow->setObjectName("Red Going Yellow");
    // Create yellow going to green light state
    m_Yellow_Going_Green = makeState(m_main_light_yellow,m_yellow_duration);
    m_Yellow_Going_Green->setObjectName("Yellow Going Green");

    // Connect these two state : m_MainGreen_Going_Left -> m_Left_Going_Yellow
    m_MainGreen_Going_Left->addTransition(m_MainGreen_Going_Left,SIGNAL(finished()),m_Left_Going_Yellow);
    // Connect these two state : m_Yellow_Going_Left -> m_Left_Going_Red
    m_Left_Going_Yellow->addTransition(m_Left_Going_Yellow,SIGNAL(finished()),m_Yellow_Going_Red);
    // Connect these two state : m_Yellow_Going_Red -> m_Red_Going_Yellow
    m_Yellow_Going_Red->addTransition(m_Yellow_Going_Red,SIGNAL(finished()),m_Red_Going_Yellow);
    // Connect these two state : m_Red_Going_Yellow -> m_Yellow_Going_Green
    m_Red_Going_Yellow->addTransition(m_Red_Going_Yellow,SIGNAL(finished()),m_Yellow_Going_Green);
    // Connect these two state : m_MainGreen_Going_Left -> m_MainGreen_Going_Left
    m_Yellow_Going_Green->addTransition(m_Yellow_Going_Green,SIGNAL(finished()),m_MainGreen_Going_Left);
    // Create state machine
    m_state_machine->addState(m_MainGreen_Going_Left);
    m_state_machine->addState(m_Left_Going_Yellow);
    m_state_machine->addState(m_Yellow_Going_Red);
    m_state_machine->addState(m_Red_Going_Yellow);
    m_state_machine->addState(m_Yellow_Going_Green);

}

void TrafficLight::setInitialState(const STATE_MACHINE &state)
{
    switch (state) {
    case STATE_MACHINE::Green_Going_Left:
        m_state_machine->setInitialState(m_MainGreen_Going_Left);
        break;
    case STATE_MACHINE::Left_Going_Yellow:
        m_state_machine->setInitialState(m_Left_Going_Yellow);
        break;
    case STATE_MACHINE::Yellow_Going_Red:
        m_state_machine->setInitialState(m_Yellow_Going_Red);
        break;
    case STATE_MACHINE::Red_Going_Yellow:
        m_state_machine->setInitialState(m_Red_Going_Yellow);
        break;
    case STATE_MACHINE::Yellow_Going_Green:
        m_state_machine->setInitialState(m_Yellow_Going_Green);
        break;
    }
}

void TrafficLight::startTrafficLight()
{
    if(!m_state_machine){
        //qDebug()<<"Case 1";
        return;
    }else if(m_state_machine->isRunning()){
        //qDebug()<<"Case 2";
        return;
    }else{
        //qDebug()<<"Case 3";
        m_state_machine->start();
    }
}

void TrafficLight::stopTrafficLight()
{
    if(!m_state_machine){
        //qDebug()<<"Case 1";
        return;
    }else if(!m_state_machine->isRunning()){
        //qDebug()<<"Case 2";
        return;
    }else{
        qDebug()<<"Case 3";
        m_state_machine->stop();
    }
}

LightWidget *TrafficLight::getMainGreen() const
{
    return m_main_light_green;
}

LightWidget *TrafficLight::getMainRed() const
{
    return m_main_light_red;
}

LightWidget *TrafficLight::getMainYellow() const
{
    return m_main_light_yellow;
}

LightWidget *TrafficLight::getLeftGreen() const
{
    return m_left_light;
}

void TrafficLight::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::SizeAllCursor);
}

void TrafficLight::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void TrafficLight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::SizeAllCursor);
}

QList<LightWidget *> *TrafficLight::getLight() const
{
    return m_light;
}

void TrafficLight::setRegion(const region &region)
{
    m_region = region;
}

TRAFFICMODE TrafficLight::getMode() const
{
    return m_mode;
}

void TrafficLight::setMode(const TRAFFICMODE &mode)
{
    m_mode = mode;
}

void TrafficLight::turnOffInteraction()
{
    setAcceptHoverEvents(false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
    for(int i = 0 ; i < m_light->size() ; ++i){
        m_light->at(i)->TurnOffInteraction();
    }

}

void TrafficLight::turnOnInteraction()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    for(int i = 0 ; i < m_light->size() ; ++i){
        m_light->at(i)->TurnOnInteraction();
    }
}

QState *TrafficLight::makeState(LightWidget *light, int duration, QState *parent)
{
    QState *lightState = new QState(parent);
    QTimer *timer = new QTimer(lightState);
    timer->setInterval(duration);
    timer->setSingleShot(true);
    QState *timing = new QState(lightState);
    QObject::connect(timing,SIGNAL(entered()),light,SLOT(turnOn()));
    QObject::connect(timing,SIGNAL(entered()),timer,SLOT(start()));
    QObject::connect(timing,SIGNAL(exited()),light,SLOT(turnOff()));
    QFinalState *done = new QFinalState(lightState);
    timing->addTransition(timer,SIGNAL(timeout()),done);
    lightState->setInitialState(timing);
    return lightState;
}

//void TrafficLight::mousePressEvent(QGraphicsSceneMouseEvent *event)
//{
//    qDebug()<<getRegion();
//    qDebug()<<"Position "<<this->mapToScene(event->pos());

//}

//void TrafficLight::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    setCursor(QCursor(Qt::PointingHandCursor));
//}

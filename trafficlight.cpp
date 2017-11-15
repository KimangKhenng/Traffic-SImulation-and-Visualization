#include "trafficlight.h"

QRectF TrafficLight::boundingRect() const
{
    return QRectF(0,0,SIZE*4,SIZE);
}

void TrafficLight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(QBrush(QColor("#2c3e50")));
    painter->drawRect(this->boundingRect());
}

TrafficLight::TrafficLight(region re, QGraphicsItem *parent):QGraphicsItem(parent),m_region(re)
{

}

TrafficLight::TrafficLight(QGraphicsItem *parent):QGraphicsItem (parent)
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
    m_left_light = new LightWidgetLeft(QColor("#2ecc71"),this);
    //this->addToGroup(m_left_light);
    m_main_light_green = new LightWidget(QColor("#2ecc71"),this);
    //this->addToGroup(m_main_light_green);
    m_main_light_green->moveBy(SIZE,0);
    m_main_light_yellow = new LightWidget(QColor("#f1c40f"),this);
    //this->addToGroup(m_main_light_yellow);
    m_main_light_yellow->moveBy(SIZE*2,0);
    m_main_light_red = new LightWidget(QColor("#e74c3c"),this);
    //this->addToGroup(m_main_light_red);
    m_main_light_red->moveBy(SIZE*3,0);
    m_light = new QList<LightWidget *>();
    m_light->append(m_left_light);
    m_light->append(m_main_light_green);
    m_light->append(m_main_light_yellow);
    m_light->append(m_main_light_red);
    setFlag(QGraphicsItem::ItemIsMovable);
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

QList<LightWidget *> *TrafficLight::getLight() const
{
    return m_light;
}

void TrafficLight::setRegion(const region &region)
{
    m_region = region;
}

void TrafficLight::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<getRegion();
    qDebug()<<"Position "<<this->mapToScene(event->pos());

}

//void TrafficLight::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
//{
//    setCursor(QCursor(Qt::PointingHandCursor));
//}

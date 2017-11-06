#include "trafficlight.h"

QRectF TrafficLight::boundingRect() const
{
    return QRectF(0,0,SIZE*4,SIZE);
}

void TrafficLight::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setRenderHint(QPainter::Antialiasing);
    painter->setBrush(Qt::black);
    painter->drawRect(this->boundingRect());
}

TrafficLight::TrafficLight(region re, QGraphicsItemGroup *parent):QGraphicsItemGroup(parent),m_region(re)
{
    m_left_light = new LightWidgetLeft(Qt::green);
    this->addToGroup(m_left_light);
    m_main_light_green = new LightWidget(Qt::green);
    this->addToGroup(m_main_light_green);
    m_main_light_green->moveBy(SIZE,0);
    m_main_light_yellow = new LightWidget(Qt::yellow);
    this->addToGroup(m_main_light_yellow);
    m_main_light_yellow->moveBy(SIZE*2,0);
    m_main_light_red = new LightWidget(Qt::red);
    this->addToGroup(m_main_light_red);
    m_main_light_red->moveBy(SIZE*3,0);
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

LightWidgetLeft *TrafficLight::getLeftGreen() const
{
    return m_left_light;
}

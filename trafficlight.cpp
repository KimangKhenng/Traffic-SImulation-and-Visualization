#include "trafficlight.h"

TrafficLight::TrafficLight(QWidget *parent):QWidget(parent)
{
    QVBoxLayout *vbox = new QVBoxLayout(this);
    m_red = new LightWidget(Qt::red);
    vbox->addWidget(m_red);
    m_yellow = new LightWidget(Qt::yellow);
    vbox->addWidget(m_yellow);
    m_green = new LightWidget(Qt::green);
    vbox->addWidget(m_green);
    QPalette pal = palette();
    pal.setColor(QPalette::Background, Qt::black);
    setPalette(pal);
    setAutoFillBackground(true);
}

LightWidget *TrafficLight::redLight() const
{
    return m_red;
}

LightWidget *TrafficLight::yellowLight() const
{
    return m_yellow;
}

LightWidget *TrafficLight::greenLight() const
{
    return m_green;
}

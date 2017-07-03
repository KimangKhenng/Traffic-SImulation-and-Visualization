#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <QtWidgets>
#include "lightwidget.h"
class TrafficLight : public QWidget
{
public:
    TrafficLight(QWidget *parent = 0);
    LightWidget *redLight() const;
    LightWidget *yellowLight() const;
    LightWidget *greenLight() const;
private:
    LightWidget *m_red;
    LightWidget *m_yellow;
    LightWidget *m_green;
};

#endif // TRAFFICLIGHT_H

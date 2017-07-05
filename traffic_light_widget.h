#ifndef TRAFFIC_LIGHT_WIDGET_H
#define TRAFFIC_LIGHT_WIDGET_H

#include <QtWidgets>
#include "trafficlight.h"
class Traffic_Light_widget :public QWidget
{
public:
    Traffic_Light_widget(QWidget *parent=0);
    void set_duration(int red,int yello,int green);
    void set_up();
    void start();
    void stop();
    void initiate_instance();
    QState *get_current_state();
    bool is_running();
    virtual void mousePressEvent (QMouseEvent *event);
private:
    QState *make_light_state(LightWidget *light, int duration, QState *parent = 0);
    int m_red_duration;
    int m_yellow_duration;
    int m_green_duration;
    QState *m_redGoingYellow;
    QState *m_yellowGoingGreen;
    QState *m_greenGoingYellow;
    QState *m_yellowGoingRed;
    QStateMachine *m_machine;
    TrafficLight *m_traffic_light;
};

#endif // TRAFFIC_LIGHT_WIDGET_H

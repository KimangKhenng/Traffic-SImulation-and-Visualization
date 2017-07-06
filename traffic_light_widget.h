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
    QState *get_red();
    QState *get_green();
    QState *get_red_yellow();
    QState *get_green_yellow();
    bool is_running();
    virtual void mousePressEvent (QMouseEvent *event);
    void set_opacity(float num);
    void get_other_widget(QList<Traffic_Light_widget *> *m_traffic);
    void make_other_widget_state_false();
    bool get_check_state();
    void set_initial_state_nornal ();
    void make_state_check(bool value);
    void set_initial_state(bool red, bool green);
private:
    QState *make_light_state(LightWidget *light, int duration, QState *parent = 0);
    int m_red_duration;
    int m_yellow_duration;
    int m_green_duration;
    bool m_is_check;
    QState *m_redGoingYellow;
    QState *m_yellowGoingGreen;
    QState *m_greenGoingYellow;
    QState *m_yellowGoingRed;
    QStateMachine *m_machine;
    TrafficLight *m_traffic_light;
    QList<Traffic_Light_widget *> *m_traffic_list;
};

#endif // TRAFFIC_LIGHT_WIDGET_H

#ifndef TRAFFICSIGNALCONTROL_H
#define TRAFFICSIGNALCONTROL_H

#include "traffic_light_widget.h"

class TrafficSignalControl
{
public:
    TrafficSignalControl(Traffic_Light_widget *t1,Traffic_Light_widget *t2,Traffic_Light_widget *t3,Traffic_Light_widget *t4);

private:
    Traffic_Light_widget *m_light_1;
    Traffic_Light_widget *m_light_2;
    Traffic_Light_widget *m_light_3;
    Traffic_Light_widget *m_light_4;
};

#endif // TRAFFICSIGNALCONTROL_H

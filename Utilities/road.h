#ifndef ROAD_H
#define ROAD_H

#include <QPainterPath>
#include <QTransform>
#include "Entities/TrafficLight/trafficlight.h"
#include "commonenum.h"
class road
{
public:
    ///////////////////
    /// \brief getLeft
    /// \param approach = region for vehicle to appear
    /// \return Path for vehicle
    /// function to return path for vehicle
    static QPainterPath getLeft(const region& approach);
    static QPainterPath getThrough(const region& approach,const int& lane);
    static QPainterPath getRight(const region& approach);
private:
    static QPainterPath get_1_1();
    static QPainterPath get_1_2();
    static QPainterPath get_1_3();
    static QPainterPath get_1_4();
    static QPainterPath get_1_5();
    static QPainterPath get_2_1();
    static QPainterPath get_2_2();
    static QPainterPath get_2_3();
    static QPainterPath get_2_4();
    static QPainterPath get_2_5();
    static QPainterPath get_3_1();
    static QPainterPath get_3_2();
    static QPainterPath get_3_3();
    static QPainterPath get_3_4();
    static QPainterPath get_3_5();
    static QPainterPath get_4_1();
    static QPainterPath get_4_2();
    static QPainterPath get_4_3();
    static QPainterPath get_4_4();
    static QPainterPath get_4_5();
    static QPainterPath draw_1_1();
    static QPainterPath draw_1_2();
    static QPainterPath draw_1_3();
    static QPainterPath draw_1_4();
    static QPainterPath draw_1_5();
    static QPainterPath draw_2_1();
    static QPainterPath draw_2_2();
    static QPainterPath draw_2_3();
    static QPainterPath draw_2_4();
    static QPainterPath draw_2_5();
    static QPainterPath draw_3_1();
    static QPainterPath draw_3_2();
    static QPainterPath draw_3_3();
    static QPainterPath draw_3_4();
    static QPainterPath draw_3_5();
    static QPainterPath draw_4_1();
    static QPainterPath draw_4_2();
    static QPainterPath draw_4_3();
    static QPainterPath draw_4_4();
    static QPainterPath draw_4_5();
};

#endif // ROAD_H

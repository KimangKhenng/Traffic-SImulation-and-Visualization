#ifndef ROAD_H
#define ROAD_H

#include <QtCore>
#include <QtWidgets>
class road
{
public:
    road();
    QPainterPath get_1_1();
    QPainterPath get_1_2();
    QPainterPath get_1_3();
    QPainterPath get_1_4();
    QPainterPath get_1_5();
    QPainterPath get_2_1();
    QPainterPath get_2_2();
    QPainterPath get_2_3();
    QPainterPath get_2_4();
    QPainterPath get_2_5();
    QPainterPath get_3_1();
    QPainterPath get_3_2();
    QPainterPath get_3_3();
    QPainterPath get_3_4();
    QPainterPath get_3_5();
    QPainterPath get_4_1();
    QPainterPath get_4_2();
    QPainterPath get_4_3();
    QPainterPath get_4_4();
    QPainterPath get_4_5();
    QList<QPainterPath> get_all_path();
private:
    QPainterPath draw_1_1();
    QPainterPath draw_1_2();
    QPainterPath draw_1_3();
    QPainterPath draw_1_4();
    QPainterPath draw_1_5();
    QPainterPath draw_2_1();
    QPainterPath draw_2_2();
    QPainterPath draw_2_3();
    QPainterPath draw_2_4();
    QPainterPath draw_2_5();
    QPainterPath draw_3_1();
    QPainterPath draw_3_2();
    QPainterPath draw_3_3();
    QPainterPath draw_3_4();
    QPainterPath draw_3_5();
    QPainterPath draw_4_1();
    QPainterPath draw_4_2();
    QPainterPath draw_4_3();
    QPainterPath draw_4_4();
    QPainterPath draw_4_5();
    QList<QPainterPath> m_path_list;
};

#endif // ROAD_H

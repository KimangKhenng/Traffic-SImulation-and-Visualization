#ifndef ROAD_H
#define ROAD_H

#include <QtCore>
#include <QtWidgets>
class road : public QGraphicsPathItem
{
public:
    road(QGraphicsScene *scene);
    QPainterPath m_path_1;
    QPainterPath m_path_2;
    QPainterPath m_path_3;
    QPainterPath m_path_4;
    QPainterPath m_path_5;

};

#endif // ROAD_H

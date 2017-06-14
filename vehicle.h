#ifndef VEHICLE_H
#define VEHICLE_H
#include <QGraphicsItem>
#include <QObject>
#include "road.h"
class Vehicle: public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    Vehicle();
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    QPainterPath shape() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    void rotate_to_point(QPointF point);
    void extract_coordinate(road *path);
    void initialize();
    QPointF current_index();
    QPointF initial_path();
public slots:
    void advance();
private:
    qreal m_angle;
    qreal m_speed;
    QColor m_color;
    QList<QPointF> m_path_to_follow;
    QPointF m_destination;
    int m_point_index;

};

#endif // VEHICLE_H

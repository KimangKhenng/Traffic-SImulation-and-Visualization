#include "vehicle.h"
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QtWidgets>
#include "road.h"

//Declear static Macro variable
static const double Pi = 3.14159265358979323846264338327950288419717;
static double TwoPi = 2.0*Pi;

Vehicle::Vehicle():m_angle(0),m_speed(0),m_color(qrand()%256,qrand()%256,qrand()%256),m_point_index(0)
{
    setTransformOriginPoint(10,5);
    setFlag(QGraphicsItem::ItemIsMovable);
}

QRectF Vehicle::boundingRect() const
{
    return QRectF(10,5,20,10);
}

QPainterPath Vehicle::shape() const
{
    QPainterPath path;
    path.addRect(boundingRect());
    return path;
}

void Vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(m_color);
    painter->drawRect(boundingRect());
    Q_UNUSED(option);
    Q_UNUSED(widget);
}

void Vehicle::rotate_to_point(QPointF point)
{
    QLineF line(pos(),point);
    setRotation(-1*line.angle());
}

void Vehicle::extract_coordinate(road *path)
{
    for(double i = 0;i <= 1;i += 0.01){
        //m_path_to_follow<<mapToScene(path->path().pointAtPercent(i));
        m_path_to_follow<<QPointF(path->m_path_4.pointAtPercent(i));
    }
    qDebug()<<m_path_to_follow;
}

void Vehicle::initialize()
{
    m_destination = m_path_to_follow[0];
    rotate_to_point(m_destination);
    setPos(m_destination);
}

QPointF Vehicle::current_index()
{
    return m_path_to_follow[m_point_index];
}

QPointF Vehicle::initial_path()
{
    return m_path_to_follow[0];
}

void Vehicle::advance()
{
    QLineF line(pos(),m_destination);
    int angle = -qRadiansToDegrees(qAsin(line.dy()/line.length()));
    if(int(line.length()) <= 1){
        m_point_index++;
        if(m_point_index >= m_path_to_follow.size()){
            return;
        }
        m_destination = m_path_to_follow[m_point_index];
        rotate_to_point(m_destination);
    }
    qDebug()<<angle;
    if(angle < 89 && angle >0){
        m_speed -= 0.01;
    }else{
        m_speed += 0.01;
    }
    qDebug()<<m_speed;
    double theta = rotation();
    double dy = m_speed*qSin(qDegreesToRadians(theta));
    double dx = m_speed*qCos(qDegreesToRadians(theta));
    setPos(x()+dx,y()+dy);

}

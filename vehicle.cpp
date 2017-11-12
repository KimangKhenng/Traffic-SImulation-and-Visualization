#include "vehicle.h"
#include <math.h>
#include <QPainter>
#include <QDebug>
#include <QtWidgets>
#include "road.h"
#include <qmath.h>
#include <exception>
#include "mainwindow.h"
//Declear static Macro variable
static const double Pi = 3.14159265358979323846264338327950288419717;
//static double TwoPi = 2.0*Pi;

Vehicle::Vehicle(QGraphicsItem *parent):QGraphicsItem(parent),m_angle(0),m_speed(0),m_color(qrand()%256,qrand()%256,qrand()%256)
  ,m_point_index(0),m_on_action_state(false),m_step_count(0),m_driving_state(false)
{
    m_sightseeing = new QGraphicsRectItem(QRectF(30,5,GAPACCAPANCE,10),this);
    m_sightseeing->setOpacity(0);
    setTransformOriginPoint(10,5);
    setFlag(QGraphicsItem::ItemIsMovable);
}

Vehicle::~Vehicle()
{
    delete m_sightseeing;
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

void Vehicle::extract_coordinate(QPainterPath path)
{
    for(double i = 0;i <= 1;i += 0.01){
        //m_path_to_follow<<mapToScene(path->path().pointAtPercent(i));
        m_path_to_follow<<QPointF(path.pointAtPercent (i));
        m_step_count++;
    }
    //qDebug()<<m_path_to_follow;
}

void Vehicle::setDirection(Direction dir)
{
    m_dir = dir;
}

void Vehicle::initialize()
{
    m_destination = m_path_to_follow[0];
    rotate_to_point(m_destination);
    setPos(m_destination);
}
void Vehicle::setRegion(region r)
{
    m_region = r;
}
bool Vehicle::is_on_action()
{
    return m_on_action_state;
}

bool Vehicle::is_in_stop_point()
{
    if(m_point_index > 35 && m_point_index < 40){
            return true;
        }
        else{
            return false;
        }
}

void Vehicle::setActionOn()
{
    m_on_action_state = true;
}

void Vehicle::setActionOff()
{
    m_on_action_state = false;
}

void Vehicle::reset_speed()
{
    m_speed = 0;
}

void Vehicle::decelerate()
{
    m_speed -= 0.025;
    if(m_speed < 0){
        m_speed += 0.025;
    }
}

void Vehicle::accerlerate()
{
    m_speed += 0.01;
}

QList<QPointF> Vehicle::get_path()
{
    return m_path_to_follow;
}
bool Vehicle::Isinthejunction()
{
    if(m_point_index > 40){
        return true;
    }
    else{
        return false;
    }
}
QPointF Vehicle::get_position() const
{
    return this->pos ();
}

int Vehicle::get_current_index() const
{
    return m_point_index;
}

QPointF Vehicle::get_initial_path() const
{
    return m_path_to_follow[0];
}

void Vehicle::stop_advance()
{
    m_speed = 0;
}


void Vehicle::advance(int phase)
{
    Q_UNUSED(phase)
    if(m_on_action_state){
        accerlerate ();
    }else{
        return;
    }
//    }
    //qDebug()<<"Distance =" <<distance_to_other_vehicle (m_next);
    //qDebug()<<"Size of list" << m_car_list->size ();
    //qDebug()<<"Current Position"<<pos();
//    if(distance_to_other_vehicle (m_next) <= 50 && distance_to_other_vehicle (m_next) != -1){
//        decelerate ();
//    }
//    if(distance_to_other_vehicle (m_next) >= 100 && distance_to_other_vehicle (m_next) != -1){
//        accerlerate ();
//    }
//    if(is_no_car_infront ()){
//        accerlerate ();
//    }
    //With Traffic
//    if(m_traffic_widget->get_current_state () == m_traffic_widget->get_red () || m_traffic_widget->get_current_state () == m_traffic_widget->get_red_yellow ()){
//        if(is_in_stop_point ()){
//            m_driving_state = false;
//            stop_advance ();
//            }
//        if(distance_to_other_vehicle (getCollding()) <= 25 && distance_to_other_vehicle (getCollding()) != -1){
//            m_driving_state = false;
//            stop_advance ();
//            }
//        }
//     if(m_traffic_widget->get_current_state () == m_traffic_widget->get_green () || m_traffic_widget->get_current_state () == m_traffic_widget->get_green_yellow ()){
//         if(distance_to_other_vehicle (getCollding()) <= 25 && distance_to_other_vehicle (getCollding()) != -1){
//             m_driving_state = false;
//             stop_advance ();
//             }
//         if(distance_to_other_vehicle (getCollding()) > 25 &&  m_driving_state == false ){
//            m_driving_state = true;
//            accerlerate ();
//            }
//    }
     // No Traffic
//     if(distance_to_other_vehicle (m_next) <= 25 && distance_to_other_vehicle (m_next) != -1){
//         m_driving_state = false;
//         stop_advance ();
//         }
//     if(distance_to_other_vehicle (m_next) <= 25 && distance_to_other_vehicle (m_next) != -1){
//         m_driving_state = false;
//         stop_advance ();
//         }
//     if(distance_to_other_vehicle (m_next) > 25 &&  m_driving_state == false ){
//        m_driving_state = true;
//        accerlerate ();
//        }
    //No traffic
//    if(!ifAllowed()){
//        m_driving_state = false;
//        stop_advance();
//    }
    if(hasInfront()){
        stop_advance();
    }
    QLineF line(pos(),m_destination);
    //qDebug()<<line.length ();
    if(int(line.length()) <= 1){
        m_point_index++;
        if(m_point_index >= m_path_to_follow.size()){
            return;
        }
        m_destination = m_path_to_follow[m_point_index];
        rotate_to_point(m_destination);
    }
    double theta = rotation();
    double dy = m_speed*qSin(qDegreesToRadians(theta));
    double dx = m_speed*qCos(qDegreesToRadians(theta));
    setPos(x()+dx,y()+dy);
    //qDebug()<<"Speed of"<<m_car_list->indexOf (this)<<" "<<m_speed;
    //qDebug()<<m_order_in_list;
    //qDebug()<<"Current Index"<<m_path_to_follow[m_point_index];
}
Vehicle *Vehicle::getCollding()
{
    Vehicle *next = nullptr;
    QList<QGraphicsItem *> list_of_collding_vehicle = m_sightseeing->collidingItems();
    for(int i = 0 ; i < list_of_collding_vehicle.size() ; ++i){
        next = dynamic_cast<Vehicle *>(list_of_collding_vehicle.at(i));
        if(next&&(next !=this)){
            return next;
        }
    }
    return nullptr;
}

bool Vehicle::hasInfront()
{
    Vehicle *next = nullptr;
    QList<QGraphicsItem *> list_of_collding_vehicle = m_sightseeing->collidingItems();
    for(int i = 0 ; i < list_of_collding_vehicle.size() ; ++i){
        next = dynamic_cast<Vehicle *>(list_of_collding_vehicle.at(i));
        if(next&&(next !=this)){
            return true;
        }
    }
    return false;
}

Direction Vehicle::getDir() const
{
    return m_dir;
}

void Vehicle::setDir(const Direction &dir)
{
    m_dir = dir;
}

void Vehicle::turnOnSightSeeing()
{
    m_sightseeing->setOpacity(1.0);
}

void Vehicle::turnOffSightSeeing()
{
    m_sightseeing->setOpacity(0.0);
}

region Vehicle::getRegion() const
{
    return m_region;
}

bool Vehicle::ifAllowed() const
{
    QList<QGraphicsItem *> item = scene()->items();
    QList<TrafficLight *> light_list;
    for(int i = 0 ; i < item.size() ; ++i){
        TrafficLight *light = dynamic_cast<TrafficLight *>(item.at(i));
        if(light){
            light_list.append(light);
        }
    }
    for(int i = 0 ; i < light_list.size() ; ++i){
        if(light_list.at(i)->getRegion() == this->getRegion()){
            return light_list.at(i)->checkDir(this->getDir());
        }
    }
    return false;
}

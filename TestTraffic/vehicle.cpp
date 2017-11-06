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
static double TwoPi = 2.0*Pi;

Vehicle::Vehicle():m_angle(0),m_speed(0),m_color(qrand()%256,qrand()%256,qrand()%256)
  ,m_point_index(0),m_on_action_state(false),m_step_count(0),m_order_in_list(0),m_driving_state(false),m_back(nullptr)
{
    setTransformOriginPoint(10,5);
    setFlag(QGraphicsItem::ItemIsMovable);
    m_internal_timer = new QTimer();
    QObject::connect (m_internal_timer,SIGNAL(timeout()),this,SLOT(advance()));
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

void Vehicle::initialize(Traffic_Light_widget *m_traffic)
{
    m_destination = m_path_to_follow[0];
    rotate_to_point(m_destination);
    setPos(m_destination);
    m_next = get_next_vehicle();
    //m_back = get_back_vehicle ();
    m_traffic_widget = m_traffic;
}

double Vehicle::distance_to_other_vehicle(Vehicle *car)
{
    if(car == nullptr){
        return -1;
    }
    double x = qAbs(get_position ().x ()- car->get_position ().x ());
    double y = qAbs(get_position ().y ()- car->get_position ().y ());
    return qSqrt (x*x + y*y);
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

void Vehicle::set_on_action(bool state)
{
    m_on_action_state = state;
}

bool Vehicle::is_no_car_infront()
{
    if(m_list->indexOf (this) == 0){
        return true;
    }
    return false;
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

bool Vehicle::is_on_the_same_path(Vehicle *vehicle)
{
    if(vehicle->get_path () == m_path_to_follow){
        return true;
    }
}

QList<QPointF> Vehicle::get_path()
{
    return m_path_to_follow;
}

Vehicle *Vehicle::get_next_vehicle()
{
    if(m_list->size () == 1){
        return nullptr;
    }
    else{
        //qDebug()<<"Error 1";
        return m_list->at (m_list->indexOf (this)-1);
    }
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
QPointF Vehicle::get_position()
{
    return this->pos ();
}

int Vehicle::get_current_index()
{
    return m_point_index;
}

QPointF Vehicle::get_initial_path()
{
    return m_path_to_follow[0];
}

QTimer *Vehicle::get_timer()
{
    return m_internal_timer;
}

void Vehicle::get_list_of_all(QList<Vehicle *> *car_list)
{
    m_list = car_list;
}

QList<Vehicle *> *Vehicle::get_list()
{
    return m_list;
}

void Vehicle::set_order_in_list(int x)
{
    m_order_in_list = x;
}

void Vehicle::stop_advance()
{
    m_speed = 0;
}

void Vehicle::remove_next()
{
    m_next = nullptr;
}

int Vehicle::get_index_in_list()
{
    qDebug()<<m_list->size ();
    return m_list->size ()-1;
}

Vehicle *Vehicle::get_back_vehicle()
{
    if(m_list->size () == 1){
        return nullptr;
    }else{
        //qDebug()<<"Error 2";
        //qDebug()<<m_list->size ();
        //qDebug()<<m_list->indexOf (this)+1;
        if((m_list->indexOf (this)+1) == m_list->size ()){
            return nullptr;
        }
        return m_list->at (m_list->indexOf (this)+1);
    }

}

void Vehicle::advance()
{
    if(is_on_action ()){
        m_driving_state = true;
        accerlerate ();
    }else{
        m_driving_state = false;
        stop_advance ();
    }
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
    if(m_traffic_widget->get_current_state () == m_traffic_widget->get_red () || m_traffic_widget->get_current_state () == m_traffic_widget->get_red_yellow ()){
        if(is_in_stop_point ()){
            m_driving_state = false;
            stop_advance ();
            }
        if(distance_to_other_vehicle (m_next) <= 25 && distance_to_other_vehicle (m_next) != -1){
            m_driving_state = false;
            stop_advance ();
            }
        }
     if(m_traffic_widget->get_current_state () == m_traffic_widget->get_green () || m_traffic_widget->get_current_state () == m_traffic_widget->get_green_yellow ()){
         if(distance_to_other_vehicle (m_next) <= 25 && distance_to_other_vehicle (m_next) != -1){
             m_driving_state = false;
             stop_advance ();
             }
         if(distance_to_other_vehicle (m_next) > 25 &&  m_driving_state == false ){
            m_driving_state = true;
            accerlerate ();
            }
    }
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

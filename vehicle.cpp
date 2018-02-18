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
  ,m_point_index(0),m_on_action_state(false),m_step_count(0),m_driving_state(false),m_mode(VEHICLEMETHOD::SIGHTSEEING)
  ,m_Is_deletable(false)
{
    //m_internal_timer = new QTimer;
    m_sightseeing = new QGraphicsRectItem(QRectF(30,5,GAPACCAPANCE,10),this);
    m_sightseeing->setOpacity(0);
    this->setTransformOriginPoint(10,5);
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    //this->connect(m_internal_timer,SIGNAL(timeout()),this,SLOT(forward()));
}

Vehicle::~Vehicle()
{
    delete m_sightseeing;
    //delete m_internal_timer;
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
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setPen(Qt::NoPen);
    painter->setBrush(m_color);
    painter->drawRect(boundingRect());
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
    if(m_point_index > 34 && m_point_index < 39){
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
    if(this->is_in_stop_point()){
        if(isContainedSignal()){
            if(!ifAllowed()){
                stop_advance();
                return;
            }
        }
    }
    if(m_mode == VEHICLEMETHOD::SIGHTSEEING){
        if(hasInfront()){
            stop_advance();
            return;
        }
    }
    QLineF line(pos(),m_destination);
    //qDebug()<<"Length"<<line.length();
    if(int(line.length()) <= 1.0){
        m_point_index++;
        if(m_point_index >= m_path_to_follow.size()){
            m_Is_deletable = true;
            return;
        }
        m_destination = m_path_to_follow[m_point_index];
        rotate_to_point(m_destination);
    }
    double theta = rotation();
    double dy = m_speed*qSin(qDegreesToRadians(theta));
    double dx = m_speed*qCos(qDegreesToRadians(theta));
    setPos(x()+dx,y()+dy);
}

void Vehicle::forward()
{
    if(m_on_action_state){
        accerlerate ();
    }else{
        return;
    }
    if(this->is_in_stop_point()){
        if(isContainedSignal()){
            if(!ifAllowed()){
                stop_advance();
                return;
            }
        }
    }
    if(m_mode == VEHICLEMETHOD::SIGHTSEEING){
        if(hasInfront()){
            stop_advance();
            return;
        }
    }
    QLineF line(pos(),m_destination);
    //qDebug()<<"Length"<<line.length();
    if(int(line.length()) <= 1.0){
        if(m_point_index >= m_path_to_follow.size()){
            return;
        }
        m_point_index++;
        m_destination = m_path_to_follow[m_point_index];
        rotate_to_point(m_destination);
    }
    double theta = rotation();
    double dy = m_speed*qSin(qDegreesToRadians(theta));
    double dx = m_speed*qCos(qDegreesToRadians(theta));
    setPos(x()+dx,y()+dy);

//    setPos(x()+m_speed*qSin(qDegreesToRadians(rotation())),y()+m_speed*qCos(qDegreesToRadians(rotation())));

    //qDebug()<<"Point Size"<<m_path_to_follow.size();
    //qDebug()<<"Point Index"<<m_point_index;
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

void Vehicle::setMode(const VEHICLEMETHOD &mode)
{
    m_mode = mode;
}

bool Vehicle::isDeletable() const
{
    return m_Is_deletable;
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

//void Vehicle::turnOnEngine()
//{
//    if(m_internal_timer->isActive()){
//        return;
//    }
//    m_internal_timer->start(TIME_UNIT);
//    m_on_action_state = true;
//}

//void Vehicle::turnOffEngine()
//{
//    m_internal_timer->stop();
//}

bool Vehicle::isContainedSignal() const
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
        if(light_list.at(i)->getMode() == TRAFFICMODE::HAS_SIGNAL){
            return true;
        }
    }
    return false;
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

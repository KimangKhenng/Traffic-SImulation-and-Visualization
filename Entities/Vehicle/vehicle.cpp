#include "vehicle.h"
#include "UI/simulationscene.h"
#include <QGraphicsSceneHoverEvent>

//Declear static Macro variable
//static const double Pi = 3.14159265358979323846264338327950288419717;
//static double TwoPi = 2.0*Pi;

Vehicle::Vehicle(QGraphicsItem *parent)
    :QGraphicsPixmapItem(parent)
    ,m_angle(0)
    ,m_speed(0)
    ,m_acceleration(ACCER)/*,m_color(qrand()%256,qrand()%256,qrand()%256)*/
    ,m_point_index(0)
    ,m_step_count(0)
    ,m_driving_state(false)
    ,m_mode(VEHICLEMETHOD::SIGHTSEEING)
    ,m_Is_deletable(false)
    ,m_leader(nullptr)
{
    //m_internal_timer = new QTimer;
    m_sightseeing = new VehicleSight(QRectF(30,5,GAPACCAPANCE * 4,10),this);
    m_sightseeing_small = new VehicleSight(QRectF(30,5,GAPACCAPANCE,10),this);
    m_sightseeing_small->setPen(QPen(QColor(Qt::red)));
    m_sightseeing_small->setOpacity(0);
    m_sightseeing->setOpacity(0);
    setTransformOriginPoint(10,5);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable);

    //this->setCacheMode(QGraphicsItem::ItemCoordinateCache);
    setOffset(10,5);
    setPixmap(generateImage().scaled(25,13,Qt::KeepAspectRatio,
                                           Qt::TransformationMode::SmoothTransformation));
}

Vehicle::~Vehicle()
{
    //qDebug()<<"Delete "<<this->objectName();
    delete m_sightseeing;
    delete m_sightseeing_small;
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

//void Vehicle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
//{
//    Q_UNUSED(option);
//    Q_UNUSED(widget);
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(m_color);
//    painter->drawRect(boundingRect());
//}

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

bool Vehicle::is_in_stop_point()
{
    if(m_point_index > 34 && m_point_index < 39){
            return true;
    }else{
            return false;
    }
}





void Vehicle::reset_speed()
{
    m_speed = 0;
}

void Vehicle::decelerate(QPointF rhs)
{

}

void Vehicle::accelerate()
{
    m_speed += ACCER;
}

void Vehicle::accelerate(Vehicle *leader)
{
    m_acceleration = 3*(leader->getSpeed()-this->getSpeed())/distanceToOtherVehicle(leader);
    //qDebug()<<"Acc: "<<m_acceleration;
    m_speed += m_acceleration;
}

QList<QPointF> Vehicle::get_path() const
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

bool Vehicle::isInsideIntersection()
{
    if(m_point_index > 35 && m_point_index < 55){
            return true;
    }else{
            return false;
    }
}

qreal Vehicle::getSpeed() const
{
    return m_speed;
}

void Vehicle::turnOffInteraction()
{
    setAcceptHoverEvents(false);
    setFlag(QGraphicsItem::ItemIsMovable,false);
}

void Vehicle::turnOnInteraction()
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
}

void Vehicle::advance(int phase)
{
    Q_UNUSED(phase)
    if(this->is_in_stop_point()){
        if(this->isContainedSignal()){
            if(!this->ifAllowed()){
                stop_advance();
                return;
            }
        }
    }
    if( m_mode == VEHICLEMETHOD::SIGHTSEEING){
        if(hasInfront()){
            if(isAboutToCrash()){
                stop_advance();
                return;
            }
            accelerate(m_leader);
        }else{
            m_leader = nullptr;
            accelerate();
        }
    }else{
        m_leader = nullptr;
        m_acceleration = ACCER;
        accelerate();
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

void Vehicle::update(const VEHICLEMETHOD &mode)
{
    if(this->is_in_stop_point()){
        if(this->isContainedSignal()){
            if(!this->ifAllowed()){
                stop_advance();
                return;
            }
        }
    }
    if(mode == VEHICLEMETHOD::SIGHTSEEING){
        if(hasInfront()){
            if(isAboutToCrash()){
                stop_advance();
                return;
            }
            accelerate(m_leader);
        }else{
            m_leader = nullptr;
            accelerate();
        }
    }else{
        m_leader = nullptr;
        m_acceleration = ACCER;
        accelerate();
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

Vehicle *Vehicle::nextVehicle()
{
    Vehicle *next = nullptr;
    QList<QGraphicsItem *> list_of_collding_vehicle = m_sightseeing->collidingItems();
    for(int i = 0 ; i < list_of_collding_vehicle.size() ; ++i){
        next = dynamic_cast<Vehicle *>(list_of_collding_vehicle.at(i));
        if(next&&(next !=this)){
            return next;
        }
    }
    return this;

}

SimulationScene *Vehicle::myScene() const
{
    SimulationScene* scene = dynamic_cast<SimulationScene*>(this->scene());
    if(scene){
        return scene;
    }
    return nullptr;
}

double Vehicle::distanceToOtherVehicle(QGraphicsItem *v) const
{
    return sqrt((v->x() - this->x())*(v->x() - this->x()) + (v->y() - this->y())*(v->y() - this->y()) );
}

void Vehicle::adjustSpeedIntersection()
{
    //qDebug()<<"True";
    if(isInsideIntersection()){
        m_speed -= ACCER/10;
        if(qFuzzyCompare(m_speed,0.0)){
            accelerate();
        }
    }else{
        accelerate();
    }
}

void Vehicle::adjustSpeedIntersection(Vehicle *leader)
{
    if(isInsideIntersection()){
        m_speed -= ACCER/10;
        if(qFuzzyCompare(m_speed,0.0)){
            accelerate();
        }
    }else{
        accelerate(leader);
    }
}


bool Vehicle::hasInfront()
{
    //VehicleSight *next = nullptr;
    Vehicle* leader = nullptr;
    QList<QGraphicsItem *> list_of_collding_vehicle = m_sightseeing->collidingItems();
    for(int i = 0 ; i < list_of_collding_vehicle.size() ; ++i){
        leader = dynamic_cast<Vehicle *>(list_of_collding_vehicle.at(i));
        if(leader&&(leader !=this)){
            m_leader = leader;
            this->m_sightseeing->setPen(QPen(QColor(Qt::red)));
            //qDebug()<<"True";
            return true;
        }
    }
    this->m_sightseeing->setPen(QPen(QColor(Qt::black)));
    //m_acceleration = 0.01;
    return false;
}

bool Vehicle::isAboutToCrash() const
{
    Vehicle* leader = nullptr;
    QList<QGraphicsItem *> list_of_collding_vehicle = m_sightseeing_small->collidingItems();
    for(int i = 0 ; i < list_of_collding_vehicle.size() ; ++i){
        leader = dynamic_cast<Vehicle *>(list_of_collding_vehicle.at(i));
        if(leader&&(leader !=this)){
            this->m_sightseeing_small->setPen(QPen(QColor(Qt::red)));
            //qDebug()<<"True";
            //m_sightseeing_small->setOpacity(1);
            return true;
        }
    }
    //m_sightseeing_small->setOpacity(0);
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

//void Vehicle::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
//{
//    qDebug()<<"Car's Position: "<<this->pos();
//}

void Vehicle::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    //QGraphicsItem::hoverEnterEvent(event);
}

void Vehicle::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    setCursor(Qt::ArrowCursor);
}

void Vehicle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ClosedHandCursor);
}




QPixmap Vehicle::generateImage() const
{
    switch (qrand()%18) {
    case 0:
        return QPixmap(":/cars/Image/Cars/Asset 1.png");
    case 1:
        return QPixmap(":/cars/Image/Cars/Asset 2.png");
    case 2:
        return QPixmap(":/cars/Image/Cars/Asset 3.png");
    case 3:
        return QPixmap(":/cars/Image/Cars/Asset 4.png");
    case 4:
        return QPixmap(":/cars/Image/Cars/Asset 5.png");
    case 5:
        return QPixmap(":/cars/Image/Cars/Asset 6.png");
    case 6:
        return QPixmap(":/cars/Image/Cars/Asset 7.png");
    case 7:
        return QPixmap(":/cars/Image/Cars/Asset 8.png");
    case 8:
        return QPixmap(":/cars/Image/Cars/Asset 9.png");
    case 9:
        return QPixmap(":/cars/Image/Cars/Asset 10.png");
    case 10:
        return QPixmap(":/cars/Image/Cars/Asset 11.png");
    case 11:
        return QPixmap(":/cars/Image/Cars/Asset 12.png");
    case 12:
        return QPixmap(":/cars/Image/Cars/Asset 13.png");
    case 13:
        return QPixmap(":/cars/Image/Cars/Asset 14.png");
    case 14:
        return QPixmap(":/cars/Image/Cars/Asset 15.png");
    case 15:
        return QPixmap(":/cars/Image/Cars/Asset 16.png");
    case 16:
        return QPixmap(":/cars/Image/Cars/Asset 17.png");
    case 17:
        return QPixmap(":/cars/Image/Cars/Asset 18.png");
    }
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
//    }else{
//        this->connect(m_internal_timer,SIGNAL(timeout()),this,SLOT(forward()));
//        m_internal_timer->start(TIME_UNIT);
//    }
//    m_on_action_state = true;
//}

//void Vehicle::turnOffEngine()
//{
//    this->disconnect(m_internal_timer,SIGNAL(timeout()),this,SLOT(forward()));
//    m_internal_timer->stop();
//    m_on_action_state = false;
//}

bool Vehicle::isContainedSignal() const
{

//    QList<QGraphicsItem *> item = scene()->items();
    QList<TrafficLight *> light_list = myScene()->getTrafficLight();
//    for(int i = 0 ; i < item.size() ; ++i){
//        TrafficLight *light = dynamic_cast<TrafficLight *>(item.at(i));
//        if(light){
//            light_list.append(light);
//        }
//    }
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
    //QList<QGraphicsItem *> item = scene()->items();
    QList<TrafficLight *> light_list = myScene()->getTrafficLight();
//    for(int i = 0 ; i < item.size() ; ++i){
//        TrafficLight *light = dynamic_cast<TrafficLight *>(item.at(i));
//        if(light){
//            light_list.append(light);
//        }
//    }
    for(int i = 0 ; i < light_list.size() ; ++i){
        if(light_list.at(i)->getRegion() == this->getRegion()){
            return light_list.at(i)->checkDir(this->getDir());
        }
    }
    return false;
}

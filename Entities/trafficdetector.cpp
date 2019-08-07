#include "trafficdetector.h"

QRectF TrafficDetector::boundingRect() const
{
    return QRectF(0,0,12,static_cast<qreal>(m_detector_length));
}

void TrafficDetector::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    if(m_is_active){
        painter->setPen(QColor("#2ecc71"));
    }else{
        painter->setPen(QColor("#e74c3c"));
    }
    painter->drawRect(boundingRect());
    painter->setOpacity(0.5);
}

TrafficDetector::TrafficDetector(float length, QGraphicsItem *parent)
    :QGraphicsItem(parent)
    ,m_detector_length(length)
    ,m_flow(0)
    ,m_number_of_vehicle(0)
    ,m_density(0)
    ,m_saturation_flow_rate(0)
    ,m_is_active(false)
    ,m_isOn(true)
{
    setTransformOriginPoint(QPointF(15/2,static_cast<qreal>(m_detector_length)/2));
    m_timer = new QElapsedTimer;
    //m_counter = new QTimer();

}

TrafficDetector::~TrafficDetector()
{
    delete m_timer;
}

void TrafficDetector::advance(int phase)
{
    Q_UNUSED(phase);
    if(m_isOn){
        if(this->getNumbersOfVehicles() > 0){
            m_is_active = true;
        }else{
            m_timer->restart();
            //qDebug()<<"Hello";
            m_is_active = false;
        }
        update(boundingRect());
    }else{
        return;
    }

//    QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
//    //qDebug()<<"Size "<<collding_vehicles.size();
//    for(int i = 0 ; i < collding_vehicles.size() ; ++i){
//        Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
//        if(collding){
//            m_is_active = true;
//        }else{
//            m_timer->restart();
//            //qDebug()<<"Hello";
//            m_is_active = false;
//        }
//    }
//    qDebug()<<m_is_active;
//    qDebug()<<"Number "<<getNumbersOfVehicles();
//    qDebug()<<"Flow "<<getFlow();
//    qDebug()<<"Headway"<<getHeadWay();
//    qDebug()<<"Density "<<getDensity();
//    qDebug()<<"Hello";

}

void TrafficDetector::forward()
{
    if(m_isOn){
        if(this->getNumbersOfVehicles() > 0){
            m_is_active = true;
        }else{
            m_timer->restart();
            //qDebug()<<"Hello";
            m_is_active = false;
        }
        update(boundingRect());
    }else{
        return;
    }

//    //qDebug()<<"Size "<<collding_vehicles.size();
//    for(int i = 0 ; i < collding_vehicles.size() ; ++i){
//        Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
//        if(collding){
//            m_is_active = true;
//        }else{
//            m_timer->restart();
//            //qDebug()<<"Hello";
//            m_is_active = false;
//        }
//    }

}

//bool TrafficDetector::getIs_active() const
//{
//    return m_is_active;
//}

QElapsedTimer *TrafficDetector::getTimer() const
{
    return m_timer;
}
float TrafficDetector::getFlow() const
{
    if(m_is_active){
        //qDebug()<<"Number "<<(static_cast<float>(m_timer->elapsed()));
        return (getNumbersOfVehicles()/(static_cast<float>(m_timer->elapsed())))*1000;
    }else{
        return 0;
    }
}

bool TrafficDetector::isContainedVehicles() const
{
    return m_is_active;
}

int TrafficDetector::getNumbersOfVehicles() const
{
//    if(m_is_active){
//        QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
//        int j = 0;
//        for(int i = 0 ; i < collding_vehicles.size() ; ++i){
//            Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
//            if(collding){
//                j++;
//            }
//        }
//        return j;
//    }else{
//        return 0;
//    }
    QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
    int j = 0;
    for(int i = 0 ; i < collding_vehicles.size() ; ++i){
        Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
        if(collding){
            j++;
        }
    }
    //qDebug()<<"Collided Item: "<<collding_vehicles.size()<<"Vehicles: "<<j
;    return j;

}

float TrafficDetector::getDensity() const
{
    return getNumbersOfVehicles()/(m_detector_length/m_detector_length);
}

float TrafficDetector::getHeadWay() const
{
    if(m_is_active){
//        qDebug()<<"Number "<<(m_timer->elapsed());
        return ((static_cast<float>(m_timer->elapsed()))/getNumbersOfVehicles())/1000;
    }else{
        return 0;
    }
}

void TrafficDetector::turnOffDisplay()
{
    setOpacity(0.0);
}

void TrafficDetector::turnOnDisplay()
{
    setOpacity(1.0);
}

void TrafficDetector::turnOn()
{
    m_isOn = true;
    m_timer->start();
}

void TrafficDetector::turnOff()
{
    m_isOn = false;
    m_timer->invalidate();
}

//void TrafficDetector::startEngine()
//{
//    if(m_counter->isActive()){
//        return;
//    }else{
//        this->connect(m_counter,SIGNAL(timeout()),this,SLOT(forward()));
//        m_counter->start(TIME_UNIT);
//    }
//    m_is_active = true;
//}

//void TrafficDetector::stopEngine()
//{
//    this->disconnect(m_counter,SIGNAL(timeout()),this,SLOT(forward()));
//    this->m_counter->stop();
//    m_is_active = false;
//}

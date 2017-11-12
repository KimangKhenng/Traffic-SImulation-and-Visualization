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
        painter->setPen(Qt::green);
    }else{
        painter->setPen(Qt::red);
    }
    painter->drawRect(boundingRect());
    painter->setOpacity(0.5);
}

TrafficDetector::TrafficDetector(float length, QGraphicsItem *parent):QGraphicsItem(parent),m_detector_length(length)
  ,m_flow(0),m_number_of_vehicle(0),m_density(0),m_saturation_flow_rate(0),m_is_active(false)
{
    setTransformOriginPoint(QPointF(15/2,static_cast<qreal>(m_detector_length)/2));
    m_timer = new QElapsedTimer;
    m_timer->start();
}

TrafficDetector::~TrafficDetector()
{
    delete m_timer;
}

void TrafficDetector::advance(int phase)
{
    Q_UNUSED(phase)
    QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
    //qDebug()<<"Size "<<collding_vehicles.size();
    for(int i = 0 ; i < collding_vehicles.size() ; ++i){
        Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
        if(collding){
            m_is_active = true;
        }else{
            m_timer->restart();
            //qDebug()<<"Hello";
            m_is_active = false;
        }
    }
//    qDebug()<<m_is_active;
//    qDebug()<<"Number "<<getNumbersOfVehicles();
//    qDebug()<<"Flow "<<getFlow();
//    qDebug()<<"Headway"<<getHeadWay();
//    qDebug()<<"Density "<<getDensity();
//    qDebug()<<"Hello";
    update(boundingRect());
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

bool TrafficDetector::isContainedVehicles()
{
    isActive();
    return m_is_active;
}

int TrafficDetector::getNumbersOfVehicles() const
{
    if(m_is_active){
        QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
        int j = 0;
        for(int i = 0 ; i < collding_vehicles.size() ; ++i){
            Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
            if(collding){
                j++;
            }
        }
        return j;
    }else{
        return 0;
    }

}

float TrafficDetector::getDensity() const
{
    return getNumbersOfVehicles()/(m_detector_length);
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

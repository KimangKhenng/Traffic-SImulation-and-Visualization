#include "trafficdetector.h"

QRectF TrafficDetector::boundingRect() const
{
    return QRectF(0,0,20,static_cast<qreal>(m_detector_length));
}

void TrafficDetector::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawRect(boundingRect());
    painter->setOpacity(0.5);
}

TrafficDetector::TrafficDetector(float length,int time, QGraphicsItem *parent):QGraphicsItem(parent),m_detector_length(length)
  ,m_flow(0),m_number_of_vehicle(0),m_density(0),m_saturation_flow_rate(0),m_time(time)
{
    m_timer = new QElapsedTimer;
    m_timer->start();
}

void TrafficDetector::restartTime()
{
    m_timer->restart();
}

float TrafficDetector::getFlow() const
{
    return getNumbersOfVehicles()/static_cast<float>(m_timer->elapsed());
}

int TrafficDetector::getNumbersOfVehicles() const
{
    QList<QGraphicsItem *> collding_vehicles = this->collidingItems();
    for(int i = 0 , j = 0 ; i < collding_vehicles.size() ; ++i){
        Vehicle *collding = dynamic_cast<Vehicle *>(collding_vehicles.at(i));
        if(collding){
            j++;
        }
        return j;
    }
    return 0;
}

float TrafficDetector::getDensity() const
{

}

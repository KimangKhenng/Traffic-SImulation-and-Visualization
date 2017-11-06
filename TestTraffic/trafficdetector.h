#ifndef TRAFFICDETECTOR_H
#define TRAFFICDETECTOR_H

#include <QtCore>
#include <QtWidgets>
#include "vehicle.h"
class TrafficDetector : public QObject,public QGraphicsItem
{
    Q_OBJECT
    Q_INTERFACES(QGraphicsItem)
public:
    //@Override
    QRectF boundingRect() const Q_DECL_OVERRIDE;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) Q_DECL_OVERRIDE;
    //Override
    TrafficDetector(float length,int time, QGraphicsItem *parent = 0);
    void restartTime();
    float getFlow() const;
    int getNumbersOfVehicles() const;
    float getDensity() const;
    float getSaturationFlowRate() const;
    float getAverageSpeed() const;
private:
    float m_detector_length;
    float m_flow;
    int m_number_of_vehicle;
    float m_density;
    float m_saturation_flow_rate;
    QElapsedTimer *m_timer;
    int m_time;

};

#endif // TRAFFICDETECTOR_H

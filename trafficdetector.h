#ifndef TRAFFICDETECTOR_H
#define TRAFFICDETECTOR_H

#define LENGTH 80

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
    TrafficDetector(float length, QGraphicsItem *parent = 0);
    ~TrafficDetector();
    float getFlow() const;
    bool isContainedVehicles();
    int getNumbersOfVehicles() const;
    float getDensity() const;
    float getSaturationFlowRate() const;
    float getAverageSpeed() const;
    float getHeadWay() const;
    void turnOffDisplay();
    void turnOnDisplay();
    void startEngine();
    void stopEngine();
    QElapsedTimer *getTimer() const;
    bool getIs_active() const;
public slots:
    void advance(int phase) Q_DECL_OVERRIDE;
    //void forward();
private:
    float m_detector_length;
    float m_flow;
    int m_number_of_vehicle;
    float m_density;
    float m_saturation_flow_rate;
    QElapsedTimer *m_timer;
    //QTimer *m_counter;
    bool m_is_active;
    QVector<float> m_flow_data;
    QVector<int> m_number_data;
    QVector<float> m_density_data;
    QVector<float> m_headway_data;

};

#endif // TRAFFICDETECTOR_H

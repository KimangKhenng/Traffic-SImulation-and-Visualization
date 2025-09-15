#ifndef SIMULATIONSCENE_H
#define SIMULATIONSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSvgItem>
#include <omp.h>
#include <QtConcurrent/QtConcurrent>
#include "Entities/Vehicle/vehicle.h"
#include "Entities/trafficdetector.h"
#include "Entities/trafficcontroller.h"
#include "Utilities/spatialgrid.h"
class SimulationScene: public QGraphicsScene
{

public:
    SimulationScene(QGraphicsScene *parent = nullptr);
    ~SimulationScene();
    uint getNumber(const region &x) const;
    QList<Vehicle *> getVehicle() const;
    QList<Vehicle *> getVehicle(const region &r) const;
    TrafficLight* getTrafficLight(const region &r) const;
    QList<TrafficLight *> getTrafficLight() const;
    QList<TrafficDetector *> getDetector() const;
    /*!
     * \brief Add vehicle to the simulation scene
     * \param vehicle = vehicle to be added
     */
    void addVehicle(Vehicle* vehicle);
    /*!
     * \brief add Detector to the simulation scene
     * \param detector to be added
     */
    void addDetector(TrafficDetector* detector);

    void addLight(TrafficLight* light);
    void removeVehicle(Vehicle* ve);
    void setGoThrough(bool x);
    void resetScene();
    void showTrafficLight();
    void HideTrafficLight();
    void showIntersectionPath(const bool &show);
    void showDetectors();
    void hideDetectors();
    void turnOffDetectors();
    void turnOnDetectors();
    void showVehiclesVision();
    void hideVehiclesVision();
    TrafficController *getController() const;
    void updateScene(const VEHICLEMETHOD &seeing);
    void turnOffInteraction();
    void turnOnInteraction();
    
    /*!
     * \brief Get vehicles near a specific position using spatial grid optimization
     * \param position The center position to search around
     * \param queryRect The search area around the position
     * \return List of vehicles in the query area
     */
    QList<Vehicle*> getNearbyVehicles(const QPointF& position, const QRectF& queryRect) const;
    
    /*!
     * \brief Get the spatial grid instance
     * \return Pointer to the spatial grid
     */
    SpatialGrid* getSpatialGrid() const;

private:
    QList<Vehicle* > m_Vehicles;
    TrafficController *m_Controller;
    QGraphicsSvgItem *m_path;
    SpatialGrid *m_spatialGrid;

//protected:
//    virtual void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
};

#endif // SIMULATIONSCENE_H

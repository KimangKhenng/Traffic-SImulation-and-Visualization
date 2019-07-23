#ifndef ROADINTERSECTIONSIMULATION_H
#define ROADINTERSECTIONSIMULATION_H

#include "UI/simulationscene.h"
#include "Utilities/generator.h"
#include <QObject>
#include <QTimer>
#include <omp.h>
class RoadIntersectionSimulation : public QObject
{
    Q_OBJECT
public:
    RoadIntersectionSimulation();
    ~RoadIntersectionSimulation();
    void startSimulation();
    void stopSimulation();
public slots:
    void updateVehicle();
private:
    SimulationScene *m_Scene;
    Generator *m_Generator;
    bool m_SimulationState;
    bool m_TrafficLightOn;
    bool m_VehicleSightSeeingOn;
    bool m_VisualizationOn;
    QTimer *m_SimulationTimer;

};

#endif // ROADINTERSECTIONSIMULATION_H

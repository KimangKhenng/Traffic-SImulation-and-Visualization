#ifndef ROADINTERSECTIONSIMULATION_H
#define ROADINTERSECTIONSIMULATION_H

#include "Utilities/generator.h"
#include <QObject>
#include <QGraphicsView>

static const float TIME_STEP = 1/60;
class Generator;
class RoadIntersectionSimulation : public QObject
{
    Q_OBJECT
public:
    RoadIntersectionSimulation();
    ~RoadIntersectionSimulation();
    void startSimulation();
    void initialize(QGraphicsView *view,
                    const int &B_NS = 3500,
                    const int &B_SN = 2000,
                    const int &B_WE = 1900,
                    const int &B_EW = 3000,
                    const int &RED_LIGHT = 5000,
                    const int &GREEN_LIGHT = 3500,
                    const int &LEFT_GREEN_LIGHT = 1500,
                    const int &YELLOW_LIGHT = 500,
                    const GENMETHOD &METh = GENMETHOD::GEN_3,
                    const VEHICLEMETHOD &MODE = VEHICLEMETHOD::SIGHTSEEING);
    void stopSimulation();
    void pauseSimulation();
    void turnOffInteraction();
    void turnOnInteraction();

    SimulationScene *Scene() const;

    SimulationState State() const;

    void showRoad();
    void hideRoad();
    void showDetectors();
    void hideDetectors();
    void showVehiclesVision();
    void hideVehiclesVision();
    void showTraffic();
    void hideTraffic();
    void turnOnGoThrough();
    void turnOffGoThrough();
    void setGenerationMethod(GENMETHOD method = GENMETHOD::GEN_3);

public slots:
    void updateVehicle();
private:
    //Simulation Entities

    SimulationScene *m_Scene;
    Generator *m_Generator;
    SimulationState m_State;
    bool m_TrafficLightOn;
    bool m_VehicleSightSeeingOn;
    bool m_VisualizationOn;
    QTimer *m_SimulationTimer;
};

#endif // ROADINTERSECTIONSIMULATION_H

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
    RoadIntersectionSimulation(QGraphicsView *view);
    ~RoadIntersectionSimulation();
    void initialize(const int &B_NS = 3500,
                    const int &B_SN = 2000,
                    const int &B_WE = 1900,
                    const int &B_EW = 3000,
                    const int &RED_LIGHT = 5000,
                    const int &GREEN_LIGHT = 3500,
                    const int &LEFT_GREEN_LIGHT = 1500,
                    const int &YELLOW_LIGHT = 500,
                    const GENMETHOD &METh = GENMETHOD::GEN_3,
                    const VEHICLEMETHOD &MODE = VEHICLEMETHOD::SIGHTSEEING);
    void startSimulation();
    void stopSimulation();
    void pauseSimulation();
    void turnOffInteraction();
    void turnOnInteraction();
    void startDemo();

    SimulationScene *Scene() const;

    SimulationState State() const;

    QPixmap updatedViewinOneFrame();

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

    void autoInitialize();

    void initializeFrominput(double north_south,
                             double south_north,
                             double west_east,
                             double east_west,
                             double red_ligt,
                             double green_light,
                             double left_green);

signals:
    void updatedOneFrame();
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

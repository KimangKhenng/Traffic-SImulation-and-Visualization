#include "roadintersectionsimulation.h"
#include <QDebug>
RoadIntersectionSimulation::RoadIntersectionSimulation(QGraphicsView *view)
    :m_Scene(new SimulationScene)
    ,m_State(UNINITIALIZED)
    ,m_TrafficLightOn(false)
    ,m_VehicleSightSeeingOn(false)
    ,m_VisualizationOn(false)
    ,m_SimulationTimer(new QTimer)
{
    m_Generator = new Generator(m_Scene);
    QObject::connect(m_SimulationTimer,SIGNAL(timeout()),this,SLOT(updateVehicle()));
    view->setScene(m_Scene);
    m_Scene->setSceneRect(0,0,800,600);
}

RoadIntersectionSimulation::~RoadIntersectionSimulation()
{
    delete m_Scene;
    delete m_Generator;
    delete m_SimulationTimer;
}

void RoadIntersectionSimulation::startSimulation(const int &B_NS,
                                                 const int &B_SN,
                                                 const int &B_WE,
                                                 const int &B_EW,
                                                 const int &RED_LIGHT,
                                                 const int &GREEN_LIGHT,
                                                 const int &LEFT_GREEN_LIGHT,
                                                 const int &YELLOW_LIGHT, const GENMETHOD &METh, const VEHICLEMETHOD &MODE)
{


    m_Generator->setTimer(B_NS,B_SN,B_EW,B_WE);
    m_Generator->setMethod(METh);
    m_Generator->setMode(MODE);
    m_Scene->getController()->setLightDuration(GREEN_LIGHT,LEFT_GREEN_LIGHT,YELLOW_LIGHT,RED_LIGHT);
    m_Scene->getController()->startTrafficLightAll();
    m_Scene->showTrafficLight();
    m_SimulationTimer->start(TIME_STEP);
    m_Generator->startGenerator();
    m_State = SimulationState::STARTED;
}

void RoadIntersectionSimulation::initialize(const int &B_NS, const int &B_SN, const int &B_WE, const int &B_EW, const int &RED_LIGHT, const int &GREEN_LIGHT, const int &LEFT_GREEN_LIGHT, const int &YELLOW_LIGHT, const GENMETHOD &METh, const VEHICLEMETHOD &MODE)
{
    m_BirthRateNorthSouth = B_NS;
    m_BirthRateSouthNorth = B_SN;
    m_BirthRateWestEast = B_WE;
    m_BirthRateEastWest = B_EW;
    m_RedLightDuration = RED_LIGHT;
    m_GreenLightDuration = GREEN_LIGHT;
    m_LeftGreenLightDuration = LEFT_GREEN_LIGHT;
    m_YellowLightDuration = YELLOW_LIGHT;
    m_GenerationMethod = METh;
    m_VehicleMode = MODE;
    m_State = SimulationState::INITIALIZED;
}

void RoadIntersectionSimulation::stopSimulation()
{
    m_SimulationTimer->stop();
    m_Generator->stopGenerator();
    m_Scene->getController()->stopTrafficLightAll();
    m_State = SimulationState::STOPPED;
}

void RoadIntersectionSimulation::pauseSimulation()
{

}

void RoadIntersectionSimulation::updateVehicle()
{
    m_Scene->updateScene(VEHICLEMETHOD::SIGHTSEEING);
}

SimulationState RoadIntersectionSimulation::State() const
{
    return m_State;
}

void RoadIntersectionSimulation::showRoad()
{
    m_Scene->showIntersectionPath(true);

}

void RoadIntersectionSimulation::hideRoad()
{
    m_Scene->showIntersectionPath(false);
}

void RoadIntersectionSimulation::showDetectors()
{
    m_Scene->showDetectors();
}

void RoadIntersectionSimulation::hideDetectors()
{
    m_Scene->hideDetectors();
}

void RoadIntersectionSimulation::showVehiclesVision()
{
    m_Scene->showVehiclesVision();
    m_Generator->setVisionOn(true);

}

void RoadIntersectionSimulation::hideVehiclesVision()
{
    m_Scene->hideVehiclesVision();
    m_Generator->setVisionOn(false);
}

void RoadIntersectionSimulation::showTraffic()
{
    m_Scene->showTrafficLight();
}

void RoadIntersectionSimulation::hideTraffic()
{
    m_Scene->HideTrafficLight();
}

void RoadIntersectionSimulation::turnOnGoThrough()
{
    m_Generator->setMode(VEHICLEMETHOD::GO_THROUGH);
    m_Scene->setGoThrough(true);
}

void RoadIntersectionSimulation::turnOffGoThrough()
{
    m_Generator->setMode(VEHICLEMETHOD::SIGHTSEEING);
    m_Scene->setGoThrough(false);
}

SimulationScene *RoadIntersectionSimulation::Scene() const
{
    return m_Scene;
}

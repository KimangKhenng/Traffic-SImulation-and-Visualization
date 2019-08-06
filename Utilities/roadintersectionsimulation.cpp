#include "roadintersectionsimulation.h"
#include <QDebug>
RoadIntersectionSimulation::RoadIntersectionSimulation()
    :m_State(UNINITIALIZED)
    ,m_TrafficLightOn(false)
    ,m_VehicleSightSeeingOn(false)
    ,m_VisualizationOn(false)
    ,m_SimulationTimer(new QTimer)
{

    connect(m_SimulationTimer,&QTimer::timeout,this,&RoadIntersectionSimulation::updateVehicle);
}

RoadIntersectionSimulation::~RoadIntersectionSimulation()
{
    delete m_Scene;
    delete m_Generator;
    delete m_SimulationTimer;
}

void RoadIntersectionSimulation::startSimulation()
{
    if(m_State == SimulationState::INITIALIZED || m_State == SimulationState::PAUSED){
        m_SimulationTimer->start(TIME_STEP);
        m_Generator->startGenerator();
        m_Scene->getController()->startTrafficLightAll();
        m_Scene->getController()->turnOnDetector();
        m_Scene->showTrafficLight();
        m_State = SimulationState::STARTED;
    }
    if(m_State == SimulationState::STARTED){
        return;
    }
}

void RoadIntersectionSimulation::initialize(QGraphicsView *view,const int &B_NS, const int &B_SN, const int &B_WE, const int &B_EW, const int &RED_LIGHT, const int &GREEN_LIGHT, const int &LEFT_GREEN_LIGHT, const int &YELLOW_LIGHT, const GENMETHOD &METh, const VEHICLEMETHOD &MODE)
{
    //Initialize Component
    if(m_State == SimulationState::UNINITIALIZED){
        m_Scene = new SimulationScene();

        m_Generator = new Generator(m_Scene);
        view->setScene(m_Scene);
        m_Scene->setSceneRect(0,0,800,600);
        //Give value to components
        m_Generator->setTimer(B_NS,B_SN,B_EW,B_WE);
        m_Generator->setMethod(METh);
        m_Generator->setMode(MODE);
        m_Scene->getController()->setLightDuration(GREEN_LIGHT,LEFT_GREEN_LIGHT,YELLOW_LIGHT,RED_LIGHT);
        m_Scene->getController()->turnOnLightInteraction();
        m_State = SimulationState::INITIALIZED;
    }
}

void RoadIntersectionSimulation::stopSimulation()
{
    if(m_State == SimulationState::STARTED || m_State == SimulationState::PAUSED){
        pauseSimulation();
        delete m_Scene;
        delete m_Generator;
        m_State = SimulationState::STOPPED;
    }
}

void RoadIntersectionSimulation::pauseSimulation()
{
    if(m_State == SimulationState::STARTED){
        m_SimulationTimer->stop();
        //this->disconnect(m_SimulationTimer);
        m_Generator->stopGenerator();
        m_Scene->getController()->stopTrafficLightAll();
        m_Scene->getController()->turnOffDetector();
        m_State = SimulationState::PAUSED;
    }
}

void RoadIntersectionSimulation::turnOffInteraction()
{
    m_Scene->turnOffInteraction();
    m_Generator->setInteraction(false);
}

void RoadIntersectionSimulation::turnOnInteraction()
{
    m_Scene->turnOnInteraction();
    m_Generator->setInteraction(true);
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

void RoadIntersectionSimulation::setGenerationMethod(GENMETHOD method)
{
    m_Generator->setMethod(method);
}

SimulationScene *RoadIntersectionSimulation::Scene() const
{
    return m_Scene;
}

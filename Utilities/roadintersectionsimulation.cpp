#include "roadintersectionsimulation.h"

RoadIntersectionSimulation::RoadIntersectionSimulation()
    :m_Scene(new SimulationScene)
    ,m_Generator(new Generator(m_Scene))
    ,m_SimulationState(false)
    ,m_TrafficLightOn(false)
    ,m_VehicleSightSeeingOn(false)
    ,m_VisualizationOn(false)
    ,m_SimulationTimer(new QTimer)
{
    connect(m_SimulationTimer,SIGNAL(timeout()),this,SLOT(updateVehicle()));
    m_Scene->setSceneRect(0,0,800,600);
}

RoadIntersectionSimulation::~RoadIntersectionSimulation()
{
    delete m_Scene;
    delete m_Generator;
    delete m_SimulationTimer;
}

void RoadIntersectionSimulation::updateVehicle()
{
    if(m_SimulationState){
        m_Scene->advance();
    }
}

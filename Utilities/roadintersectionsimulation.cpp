#include "roadintersectionsimulation.h"
#include <QDebug>
#include <QElapsedTimer>

RoadIntersectionSimulation::RoadIntersectionSimulation(QGraphicsView *view)
    :m_State(UNINITIALIZED)
    ,m_TrafficLightOn(false)
    ,m_VehicleSightSeeingOn(false)
    ,m_VisualizationOn(false)
    ,m_SimulationTimer(nullptr)
    ,m_Scene(nullptr)
    ,m_view(nullptr)
    ,m_Generator(nullptr)
    ,m_Metrics(nullptr)
{
    // Initialize timer first
    m_SimulationTimer = new QTimer(this);
    
    // Initialize scene
    m_Scene = new SimulationScene();
    if (!m_Scene) {
        qDebug() << "ERROR: Failed to create SimulationScene";
        return;
    }
    
    m_Scene->setSceneRect(0,0,800,600);
    
    if (view) {
        view->setScene(m_Scene);
        m_view = view;
    } else {
        qDebug() << "WARNING: Null view passed to constructor";
    }
    
    // Initialize performance metrics
    m_Metrics = new PerformanceMetrics(this);
    if (!m_Metrics) {
        qDebug() << "ERROR: Failed to create PerformanceMetrics";
        return;
    }
    
    connect(m_SimulationTimer,&QTimer::timeout,this,&RoadIntersectionSimulation::updateVehicle);
}

RoadIntersectionSimulation::~RoadIntersectionSimulation()
{
    // Stop timer first to prevent any further calls
    if (m_SimulationTimer) {
        m_SimulationTimer->stop();
        delete m_SimulationTimer;
        m_SimulationTimer = nullptr;
    }
    
    // Stop generator before deleting
    if (m_Generator) {
        m_Generator->stopGenerator();
        delete m_Generator;
        m_Generator = nullptr;
    }
    
    // Delete scene
    if (m_Scene) {
        delete m_Scene;
        m_Scene = nullptr;
    }
    
    // m_Metrics will be deleted automatically by Qt parent-child relationship
}

void RoadIntersectionSimulation::startSimulation()
{
    qDebug() << "Starting simulation. Current state:" << m_State;
    
    if(m_State == SimulationState::INITIALIZED || m_State == SimulationState::PAUSED){
        m_SimulationTimer->start(33); // ~30 FPS (1000ms/30 ≈ 33ms) - less aggressive than 60 FPS
        
        if (m_Generator) {
            m_Generator->startGenerator();
        }
        
        if (m_Scene && m_Scene->getController()) {
            m_Scene->getController()->startTrafficLightAll();
            m_Scene->getController()->turnOnDetector();
            m_Scene->showTrafficLight();
        }
        
        m_State = SimulationState::STARTED;
        qDebug() << "Simulation started successfully. State:" << m_State;
    }
    else if(m_State == SimulationState::STARTED){
        qDebug() << "Simulation already started";
        return;
    }
    else {
        qDebug() << "Cannot start simulation from state:" << m_State;
    }
}

void RoadIntersectionSimulation::initialize(const int &B_NS,
                                            const int &B_SN,
                                            const int &B_WE,
                                            const int &B_EW,
                                            const int &RED_LIGHT,
                                            const int &GREEN_LIGHT,
                                            const int &LEFT_GREEN_LIGHT,
                                            const int &YELLOW_LIGHT,
                                            const GENMETHOD &METh,
                                            const VEHICLEMETHOD &MODE)
{
    qDebug() << "Initializing simulation. Current state:" << m_State;
    
    //Initialize Component
    if(m_State == SimulationState::UNINITIALIZED){
        // Ensure scene is properly set up
        if(!m_Scene){
            m_Scene = new SimulationScene();
            m_Scene->setSceneRect(0,0,800,600);
            m_view->setScene(m_Scene);
        }
        
        // Clean up any existing generator
        if (m_Generator) {
            delete m_Generator;
            m_Generator = nullptr;
        }
        
        m_Generator = new Generator(m_Scene);

        //Give value to components
        if (m_Generator) {
            m_Generator->setTimer(B_NS,B_SN,B_EW,B_WE);
            m_Generator->setMethod(METh);
            m_Generator->setMode(MODE);
        }
        
        if (m_Scene && m_Scene->getController()) {
            m_Scene->getController()->setLightDuration(GREEN_LIGHT,LEFT_GREEN_LIGHT,YELLOW_LIGHT,RED_LIGHT);
            m_Scene->getController()->turnOnLightInteraction();
        }
        
        m_State = SimulationState::INITIALIZED;
        qDebug() << "Simulation initialized successfully. State:" << m_State;
    }
    else {
        qDebug() << "Simulation already initialized or in wrong state:" << m_State;
    }
}

void RoadIntersectionSimulation::initializeFrominput(SimulationInput input)
{
    initialize(input.B_NS,
               input.B_SN,
               input.B_WE,
               input.B_EW,
               input.RED_LIGHT,
               input.GREEN_LIGHT,
               input.LEFT_GREEN_LIGHT,
               input.YELLOW_LIGHT,
               input.METh,
               input.MODE);
    startSimulation();
    if(input.ShowTrafficLight == false){
        m_Scene->HideTrafficLight();
    }

}

void RoadIntersectionSimulation::stopSimulation()
{
    qDebug() << "Stopping simulation. Current state:" << m_State;
    
    if(m_State == SimulationState::STARTED || m_State == SimulationState::PAUSED){
        // Stop the timer first
        if (m_SimulationTimer) {
            m_SimulationTimer->stop();
        }
        
        // Stop the generator
        if (m_Generator) {
            m_Generator->stopGenerator();
        }
        
        // Stop traffic control
        if (m_Scene && m_Scene->getController()) {
            m_Scene->getController()->stopTrafficLightAll();
            m_Scene->getController()->turnOffDetector();
        }
        
        // Clear the scene but don't delete it
        if (m_Scene) {
            m_Scene->resetScene();
        }
        
        // Clean up generator
        if (m_Generator) {
            delete m_Generator;
            m_Generator = nullptr;
        }
        
        m_State = SimulationState::UNINITIALIZED;
        qDebug() << "Simulation stopped successfully. State:" << m_State;
    }
    else {
        qDebug() << "Cannot stop simulation from state:" << m_State;
    }
}

void RoadIntersectionSimulation::pauseSimulation()
{
    qDebug() << "Pausing simulation. Current state:" << m_State;
    
    if(m_State == SimulationState::STARTED){
        // Stop the timer
        if (m_SimulationTimer) {
            m_SimulationTimer->stop();
        }
        
        // Stop the generator
        if (m_Generator) {
            m_Generator->stopGenerator();
        }
        
        // Pause traffic control
        if (m_Scene && m_Scene->getController()) {
            m_Scene->getController()->stopTrafficLightAll();
            m_Scene->getController()->turnOffDetector();
        }
        
        m_State = SimulationState::PAUSED;
        qDebug() << "Simulation paused successfully. State:" << m_State;
    }
    else {
        qDebug() << "Cannot pause simulation from state:" << m_State;
    }
}

void RoadIntersectionSimulation::restartSimulation()
{
    qDebug() << "Restarting simulation. Current state:" << m_State;
    
    // Stop the simulation first
    stopSimulation();
    
    // The simulation is now in UNINITIALIZED state
    // UI should trigger setup dialog to reinitialize and start
    qDebug() << "Simulation restart prepared. State:" << m_State;
}

void RoadIntersectionSimulation::turnOffInteraction()
{
    m_Scene->turnOffInteraction();
    m_Generator->setInteraction(false);
    m_Scene->turnOffDetectors();
}

void RoadIntersectionSimulation::turnOnInteraction()
{
    m_Scene->turnOnInteraction();
    m_Generator->setInteraction(true);
    m_Scene->turnOnDetectors();
}

void RoadIntersectionSimulation::startDemo()
{
    startSimulation();
    turnOffInteraction();
}

void RoadIntersectionSimulation::updateVehicle()
{
    // Safety checks
    if (!m_Scene || !m_Metrics) {
        return;
    }
    
    static QElapsedTimer updateTimer;
    static QElapsedTimer collisionTimer;
    
    // Start timing the update
    updateTimer.start();
    
    // Time collision detection specifically
    collisionTimer.start();
    m_Scene->updateScene(VEHICLEMETHOD::SIGHTSEEING);
    double collisionTime = collisionTimer.elapsed();
    
    // Record metrics
    m_Metrics->recordFrame();
    
    double updateTime = updateTimer.elapsed();
    m_Metrics->recordUpdateTime(updateTime);
    m_Metrics->recordCollisionTime(collisionTime);
    
    // Collect vehicle metrics
    QList<Vehicle*> vehicles = m_Scene->getVehicle();
    int totalVehicles = vehicles.size();
    int activeVehicles = 0;
    int queuedVehicles = 0;
    
    // Analyze vehicle states and speeds
    for (Vehicle* vehicle : vehicles) {
        if (vehicle) {
            double speed = vehicle->getSpeed();
            m_Metrics->recordVehicleSpeed(speed);
            
            if (speed > 0.1) { // Consider vehicles with minimal speed as active
                activeVehicles++;
            } else {
                queuedVehicles++;
            }
        }
    }
    
    m_Metrics->updateVehicleCounts(totalVehicles, activeVehicles, queuedVehicles);
    
    // Update spatial grid metrics if available (less frequently to avoid spam)
    static int updateCounter = 0;
    if (++updateCounter % 60 == 0) { // Only every 60 frames (~1 second at 60 FPS)
        if (m_Scene->getSpatialGrid()) {
            QString gridInfo = m_Scene->getSpatialGrid()->getDebugInfo();
            // Could log this info if needed, but not every frame
        }
    }
    
    // Estimate memory usage (rough approximation)
    double estimatedMemory = totalVehicles * 0.1 + 50.0; // 0.1MB per vehicle + 50MB base
    m_Metrics->updateMemoryUsage(estimatedMemory);
    
    // Calculate congestion level based on queued vs active vehicles
    double congestionLevel = 0.0;
    if (totalVehicles > 0) {
        congestionLevel = static_cast<double>(queuedVehicles) / totalVehicles;
    }
    m_Metrics->updateCongestionLevel(congestionLevel);
    
    emit updatedOneFrame();
}

void RoadIntersectionSimulation::autoInitialize()
{
    initialize();
    startSimulation();
}

SimulationState RoadIntersectionSimulation::State() const
{
    return m_State;
}

bool RoadIntersectionSimulation::canStart() const
{
    return (m_State == SimulationState::INITIALIZED || m_State == SimulationState::PAUSED);
}

bool RoadIntersectionSimulation::canPause() const
{
    return (m_State == SimulationState::STARTED);
}

bool RoadIntersectionSimulation::canStop() const
{
    return (m_State == SimulationState::STARTED || m_State == SimulationState::PAUSED);
}

QPixmap RoadIntersectionSimulation::updatedViewinOneFrame()
{
    QPixmap image;
    startSimulation();
    image = m_Scene->views().at(0)->grab();
    pauseSimulation();
    return image;

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

int RoadIntersectionSimulation::VehiclesNumber() const
{
    if(m_Scene){
        return m_Scene->getVehicle().size();
    }
    return 0;
}

PerformanceMetrics* RoadIntersectionSimulation::getMetrics() const
{
    return m_Metrics;
}

SimulationScene *RoadIntersectionSimulation::Scene() const
{
    return m_Scene;
}

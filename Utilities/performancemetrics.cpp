#include "performancemetrics.h"
#include <QDebug>
#include <QCoreApplication>
#include <QtMath>
#include <QProcess>

PerformanceMetrics::PerformanceMetrics(QObject *parent)
    : QObject(parent)
    , m_currentFPS(0.0)
    , m_averageUpdateTime(0.0)
    , m_averageCollisionTime(0.0)
    , m_currentMemoryUsage(0.0)
    , m_totalVehicles(0)
    , m_activeVehicles(0)
    , m_queuedVehicles(0)
    , m_averageSpeed(0.0)
    , m_throughputPerMinute(0.0)
    , m_averageWaitTime(0.0)
    , m_congestionLevel(0.0)
    , m_spatialGridCellsOccupied(0)
    , m_spatialGridTotalCells(0)
    , m_spatialGridEfficiency(0.0)
    , m_vehiclesPassed(0)
{
    // Initialize queue lengths
    for (int i = 0; i < 4; ++i) {
        m_queueLengths[i] = 0;
    }
    
    // Start timers
    m_frameTimer.start();
    m_startTime.start();
    
    // Setup update timer
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &PerformanceMetrics::updateCalculations);
    m_updateTimer->start(UPDATE_INTERVAL_MS);
    
    qDebug() << "PerformanceMetrics initialized";
}

PerformanceMetrics::~PerformanceMetrics()
{
    qDebug() << "PerformanceMetrics destroyed";
}

void PerformanceMetrics::recordFrame()
{
    QMutexLocker locker(&m_metricsMutex);
    
    qint64 currentTime = m_frameTimer.elapsed();
    m_frameTimes.enqueue(currentTime);
    
    // Keep only recent samples
    while (m_frameTimes.size() > MAX_SAMPLE_SIZE) {
        m_frameTimes.dequeue();
    }
    
    m_frameTimer.restart();
}

void PerformanceMetrics::recordUpdateTime(double updateTimeMs)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_updateTimes.enqueue(updateTimeMs);
    while (m_updateTimes.size() > MAX_SAMPLE_SIZE) {
        m_updateTimes.dequeue();
    }
}

void PerformanceMetrics::recordCollisionTime(double collisionTimeMs)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_collisionTimes.enqueue(collisionTimeMs);
    while (m_collisionTimes.size() > MAX_SAMPLE_SIZE) {
        m_collisionTimes.dequeue();
    }
}

void PerformanceMetrics::updateMemoryUsage(double memoryMB)
{
    QMutexLocker locker(&m_metricsMutex);
    m_currentMemoryUsage = memoryMB;
}

void PerformanceMetrics::updateVehicleCounts(int totalVehicles, int activeVehicles, int queuedVehicles)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_totalVehicles = totalVehicles;
    m_activeVehicles = activeVehicles;
    m_queuedVehicles = queuedVehicles;
}

void PerformanceMetrics::recordVehicleSpeed(double speed)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_vehicleSpeeds.enqueue(speed);
    while (m_vehicleSpeeds.size() > MAX_SAMPLE_SIZE * 10) { // Keep more speed samples
        m_vehicleSpeeds.dequeue();
    }
}

void PerformanceMetrics::recordVehicleThroughput()
{
    QMutexLocker locker(&m_metricsMutex);
    
    qint64 currentTime = m_startTime.elapsed();
    m_throughputTimestamps.enqueue(currentTime);
    m_vehiclesPassed++;
    
    // Clean old timestamps (older than 1 minute)
    while (!m_throughputTimestamps.isEmpty() && 
           currentTime - m_throughputTimestamps.first() > 60000) {
        m_throughputTimestamps.dequeue();
    }
}

void PerformanceMetrics::recordWaitTime(double waitTimeMs)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_waitTimes.enqueue(waitTimeMs);
    while (m_waitTimes.size() > MAX_SAMPLE_SIZE) {
        m_waitTimes.dequeue();
    }
}

void PerformanceMetrics::updateQueueLengths(int queueNS, int queueSN, int queueEW, int queueWE)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_queueLengths[0] = queueNS;
    m_queueLengths[1] = queueSN;
    m_queueLengths[2] = queueEW;
    m_queueLengths[3] = queueWE;
}

void PerformanceMetrics::recordLightCycle(int direction, double greenTime, int vehiclesPassed)
{
    QMutexLocker locker(&m_metricsMutex);
    
    // Calculate light efficiency (vehicles per second during green)
    double efficiency = vehiclesPassed / (greenTime / 1000.0);
    
    // Could store historical light efficiency data here
    Q_UNUSED(direction)
    Q_UNUSED(efficiency)
}

void PerformanceMetrics::updateCongestionLevel(double congestionLevel)
{
    QMutexLocker locker(&m_metricsMutex);
    m_congestionLevel = qBound(0.0, congestionLevel, 1.0);
}

void PerformanceMetrics::updateSpatialGridStats(int cellsOccupied, int totalCells, double avgVehiclesPerCell)
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_spatialGridCellsOccupied = cellsOccupied;
    m_spatialGridTotalCells = totalCells;
    
    // Calculate spatial grid efficiency (percentage of cells occupied)
    if (totalCells > 0) {
        m_spatialGridEfficiency = static_cast<double>(cellsOccupied) / totalCells;
    } else {
        m_spatialGridEfficiency = 0.0;
    }
    
    Q_UNUSED(avgVehiclesPerCell) // Could be used for more detailed analysis
}

int PerformanceMetrics::getMaxQueueLength() const
{
    QMutexLocker locker(&m_metricsMutex);
    
    int maxQueue = 0;
    for (int i = 0; i < 4; ++i) {
        maxQueue = qMax(maxQueue, m_queueLengths[i]);
    }
    return maxQueue;
}

int PerformanceMetrics::getTotalQueueLength() const
{
    QMutexLocker locker(&m_metricsMutex);
    
    int totalQueue = 0;
    for (int i = 0; i < 4; ++i) {
        totalQueue += m_queueLengths[i];
    }
    return totalQueue;
}

QString PerformanceMetrics::getMetricsSummary() const
{
    QMutexLocker locker(&m_metricsMutex);
    
    QString summary;
    summary += QString("=== PERFORMANCE METRICS ===\n");
    summary += QString("FPS: %1\n").arg(m_currentFPS, 0, 'f', 1);
    summary += QString("Update Time: %1 ms\n").arg(m_averageUpdateTime, 0, 'f', 2);
    summary += QString("Collision Time: %1 ms\n").arg(m_averageCollisionTime, 0, 'f', 2);
    summary += QString("Memory Usage: %1 MB\n").arg(m_currentMemoryUsage, 0, 'f', 1);
    summary += QString("\n=== TRAFFIC FLOW ===\n");
    summary += QString("Total Vehicles: %1\n").arg(m_totalVehicles);
    summary += QString("Active Vehicles: %1\n").arg(m_activeVehicles);
    summary += QString("Queued Vehicles: %1\n").arg(m_queuedVehicles);
    summary += QString("Average Speed: %1\n").arg(m_averageSpeed, 0, 'f', 1);
    summary += QString("Throughput: %1 vehicles/min\n").arg(m_throughputPerMinute, 0, 'f', 1);
    summary += QString("Average Wait Time: %1 ms\n").arg(m_averageWaitTime, 0, 'f', 0);
    summary += QString("\n=== INTERSECTION ===\n");
    summary += QString("Max Queue: %1\n").arg(getMaxQueueLength());
    summary += QString("Total Queue: %1\n").arg(getTotalQueueLength());
    summary += QString("Congestion Level: %1%\n").arg(m_congestionLevel * 100, 0, 'f', 1);
    summary += QString("Grid Efficiency: %1%\n").arg(m_spatialGridEfficiency * 100, 0, 'f', 1);
    
    return summary;
}

void PerformanceMetrics::reset()
{
    QMutexLocker locker(&m_metricsMutex);
    
    m_frameTimes.clear();
    m_updateTimes.clear();
    m_collisionTimes.clear();
    m_vehicleSpeeds.clear();
    m_waitTimes.clear();
    m_throughputTimestamps.clear();
    
    m_currentFPS = 0.0;
    m_averageUpdateTime = 0.0;
    m_averageCollisionTime = 0.0;
    m_currentMemoryUsage = 0.0;
    
    m_totalVehicles = 0;
    m_activeVehicles = 0;
    m_queuedVehicles = 0;
    m_averageSpeed = 0.0;
    m_throughputPerMinute = 0.0;
    m_averageWaitTime = 0.0;
    
    for (int i = 0; i < 4; ++i) {
        m_queueLengths[i] = 0;
    }
    
    m_congestionLevel = 0.0;
    m_spatialGridCellsOccupied = 0;
    m_spatialGridTotalCells = 0;
    m_spatialGridEfficiency = 0.0;
    m_vehiclesPassed = 0;
    
    m_frameTimer.restart();
    m_startTime.restart();
    
    qDebug() << "PerformanceMetrics reset";
}

void PerformanceMetrics::updateCalculations()
{
    QMutexLocker locker(&m_metricsMutex);
    
    // Calculate FPS
    if (!m_frameTimes.isEmpty()) {
        double totalTime = 0;
        for (qint64 frameTime : m_frameTimes) {
            totalTime += frameTime;
        }
        if (totalTime > 0) {
            m_currentFPS = (m_frameTimes.size() * 1000.0) / totalTime;
        }
    }
    
    // Calculate averages
    m_averageUpdateTime = calculateAverage(m_updateTimes);
    m_averageCollisionTime = calculateAverage(m_collisionTimes);
    m_averageSpeed = calculateAverage(m_vehicleSpeeds);
    m_averageWaitTime = calculateAverage(m_waitTimes);
    
    // Calculate throughput per minute
    m_throughputPerMinute = static_cast<double>(m_throughputTimestamps.size());
    
    // Check for performance alerts
    if (m_currentFPS < 30.0 && m_currentFPS > 0) {
        emit performanceAlert("FPS", m_currentFPS, 30.0);
    }
    
    if (m_averageUpdateTime > 16.0) { // Should be under 16ms for 60 FPS
        emit performanceAlert("Update Time", m_averageUpdateTime, 16.0);
    }
    
    if (m_currentMemoryUsage > 500.0) { // Alert if over 500 MB
        emit performanceAlert("Memory Usage", m_currentMemoryUsage, 500.0);
    }
    
    emit metricsUpdated();
}

double PerformanceMetrics::calculateAverage(const QQueue<double>& queue) const
{
    if (queue.isEmpty()) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (double value : queue) {
        sum += value;
    }
    
    return sum / queue.size();
}

void PerformanceMetrics::cleanOldSamples()
{
    // This method could be used to clean samples older than a certain time
    // Currently, we're using queue size limits which is simpler
}
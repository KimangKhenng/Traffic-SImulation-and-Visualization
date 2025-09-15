#ifndef PERFORMANCEMETRICS_H
#define PERFORMANCEMETRICS_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QElapsedTimer>
#include <QQueue>
#include <QMutex>

/**
 * @brief The PerformanceMetrics class collects and manages various simulation performance indicators
 * 
 * This class provides comprehensive monitoring of:
 * - Real-time performance (FPS, update times, memory usage)
 * - Traffic flow metrics (vehicle counts, speeds, throughput)
 * - Intersection efficiency (queue lengths, wait times, congestion)
 * - System optimization (spatial grid effectiveness, collision detection performance)
 */
class PerformanceMetrics : public QObject
{
    Q_OBJECT
    
public:
    explicit PerformanceMetrics(QObject *parent = nullptr);
    ~PerformanceMetrics();
    
    // === Real-Time Performance Metrics ===
    
    /**
     * @brief Record a frame update for FPS calculation
     */
    void recordFrame();
    
    /**
     * @brief Record simulation update time
     * @param updateTimeMs Time taken for simulation update in milliseconds
     */
    void recordUpdateTime(double updateTimeMs);
    
    /**
     * @brief Record collision detection time
     * @param collisionTimeMs Time taken for collision detection in milliseconds
     */
    void recordCollisionTime(double collisionTimeMs);
    
    /**
     * @brief Update memory usage statistics
     * @param memoryMB Current memory usage in MB
     */
    void updateMemoryUsage(double memoryMB);
    
    // === Traffic Flow Metrics ===
    
    /**
     * @brief Update vehicle count statistics
     * @param totalVehicles Total vehicles in simulation
     * @param activeVehicles Currently moving vehicles
     * @param queuedVehicles Vehicles stopped at lights
     */
    void updateVehicleCounts(int totalVehicles, int activeVehicles, int queuedVehicles);
    
    /**
     * @brief Record vehicle speed for average calculation
     * @param speed Current vehicle speed
     */
    void recordVehicleSpeed(double speed);
    
    /**
     * @brief Record a vehicle passing through the intersection
     */
    void recordVehicleThroughput();
    
    /**
     * @brief Record vehicle wait time at traffic light
     * @param waitTimeMs Time waited in milliseconds
     */
    void recordWaitTime(double waitTimeMs);
    
    // === Intersection Efficiency Metrics ===
    
    /**
     * @brief Update queue lengths for all directions
     * @param queueNS North-South queue length
     * @param queueSN South-North queue length
     * @param queueEW East-West queue length
     * @param queueWE West-East queue length
     */
    void updateQueueLengths(int queueNS, int queueSN, int queueEW, int queueWE);
    
    /**
     * @brief Record traffic light state change
     * @param direction Direction of the light
     * @param greenTime Duration of green phase in ms
     * @param vehiclesPassed Number of vehicles that passed during green
     */
    void recordLightCycle(int direction, double greenTime, int vehiclesPassed);
    
    /**
     * @brief Update congestion level (0.0 = free flow, 1.0 = gridlock)
     * @param congestionLevel Current congestion level
     */
    void updateCongestionLevel(double congestionLevel);
    
    // === Spatial Grid Optimization Metrics ===
    
    /**
     * @brief Update spatial grid statistics
     * @param cellsOccupied Number of occupied grid cells
     * @param totalCells Total number of grid cells
     * @param avgVehiclesPerCell Average vehicles per occupied cell
     */
    void updateSpatialGridStats(int cellsOccupied, int totalCells, double avgVehiclesPerCell);
    
    // === Getters for Current Metrics ===
    
    double getCurrentFPS() const { return m_currentFPS; }
    double getAverageUpdateTime() const { return m_averageUpdateTime; }
    double getAverageCollisionTime() const { return m_averageCollisionTime; }
    double getCurrentMemoryUsage() const { return m_currentMemoryUsage; }
    
    int getTotalVehicleCount() const { return m_totalVehicles; }
    int getActiveVehicleCount() const { return m_activeVehicles; }
    int getQueuedVehicleCount() const { return m_queuedVehicles; }
    double getAverageSpeed() const { return m_averageSpeed; }
    double getThroughputPerMinute() const { return m_throughputPerMinute; }
    double getAverageWaitTime() const { return m_averageWaitTime; }
    
    int getMaxQueueLength() const;
    int getTotalQueueLength() const;
    double getCongestionLevel() const { return m_congestionLevel; }
    
    double getSpatialGridEfficiency() const { return m_spatialGridEfficiency; }
    
    /**
     * @brief Get comprehensive metrics summary
     * @return String containing formatted metrics summary
     */
    QString getMetricsSummary() const;
    
    /**
     * @brief Reset all metrics to initial state
     */
    void reset();

signals:
    /**
     * @brief Emitted when metrics are updated (every second)
     */
    void metricsUpdated();
    
    /**
     * @brief Emitted when performance threshold is exceeded
     * @param metric Name of the metric
     * @param value Current value
     * @param threshold Threshold that was exceeded
     */
    void performanceAlert(const QString& metric, double value, double threshold);

private slots:
    void updateCalculations();

private:
    // Performance tracking
    QElapsedTimer m_frameTimer;
    QElapsedTimer m_startTime;
    QQueue<qint64> m_frameTimes;
    QQueue<double> m_updateTimes;
    QQueue<double> m_collisionTimes;
    QQueue<double> m_vehicleSpeeds;
    QQueue<double> m_waitTimes;
    
    // Current metrics
    double m_currentFPS;
    double m_averageUpdateTime;
    double m_averageCollisionTime;
    double m_currentMemoryUsage;
    
    int m_totalVehicles;
    int m_activeVehicles;
    int m_queuedVehicles;
    double m_averageSpeed;
    double m_throughputPerMinute;
    double m_averageWaitTime;
    
    int m_queueLengths[4]; // NS, SN, EW, WE
    double m_congestionLevel;
    
    // Spatial grid metrics
    int m_spatialGridCellsOccupied;
    int m_spatialGridTotalCells;
    double m_spatialGridEfficiency;
    
    // Throughput tracking
    QQueue<qint64> m_throughputTimestamps;
    int m_vehiclesPassed;
    
    // Update timer
    QTimer *m_updateTimer;
    
    // Thread safety
    mutable QMutex m_metricsMutex;
    
    // Constants
    static const int MAX_SAMPLE_SIZE = 60; // Keep 60 samples for averaging
    static const int UPDATE_INTERVAL_MS = 1000; // Update every second
    
    // Helper methods
    double calculateAverage(const QQueue<double>& queue) const;
    void cleanOldSamples();
};

#endif // PERFORMANCEMETRICS_H
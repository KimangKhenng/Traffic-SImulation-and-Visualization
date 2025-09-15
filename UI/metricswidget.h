#ifndef METRICSWIDGET_H
#define METRICSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QProgressBar>
#include <QGroupBox>
#include <QTimer>
#include <QFont>
#include "Utilities/performancemetrics.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MetricsWidget; }
QT_END_NAMESPACE

/**
 * @brief The MetricsWidget class provides a comprehensive real-time display of simulation metrics
 * 
 * This widget shows:
 * - Performance indicators (FPS, update times, memory usage)
 * - Traffic flow metrics (vehicle counts, speeds, throughput)
 * - Intersection statistics (queue lengths, congestion, efficiency)
 * - System optimization metrics (spatial grid performance)
 */
class MetricsWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MetricsWidget(QWidget *parent = nullptr);
    ~MetricsWidget();
    
    /**
     * @brief Connect to a PerformanceMetrics instance for data updates
     * @param metrics The metrics instance to connect to
     */
    void setMetricsSource(PerformanceMetrics *metrics);
    
    /**
     * @brief Set widget visibility and update behavior
     * @param visible True to show and update metrics
     */
    void setMetricsVisible(bool visible);
    
    /**
     * @brief Set update frequency for the metrics display
     * @param intervalMs Update interval in milliseconds (default: 500ms)
     */
    void setUpdateInterval(int intervalMs);

public slots:
    /**
     * @brief Update all displayed metrics from the connected source
     */
    void updateMetrics();
    
    /**
     * @brief Handle performance alerts by highlighting affected metrics
     * @param metric Name of the metric with alert
     * @param value Current value
     * @param threshold Threshold that was exceeded
     */
    void onPerformanceAlert(const QString& metric, double value, double threshold);

private slots:
    void resetAlertColors();

private:
    private:
    void setupUI();
    void updatePerformanceMetrics();
    void updateTrafficFlowMetrics();
    void updateIntersectionMetrics();
    void updateSystemMetrics();
    void setupStyles();
    
    QString formatValue(double value, int decimals = 1, const QString& unit = "") const;
    void setLabelAlert(QLabel* label, bool alert = true);

private:
    Ui::MetricsWidget *ui;
    PerformanceMetrics *m_metrics;
    
    // Update timer
    QTimer *m_updateTimer;
    QTimer *m_alertTimer;
    
    // Styling
    QString m_normalStyle;
    QString m_alertStyle;
    
    // Constants
    static const int DEFAULT_UPDATE_INTERVAL = 500; // 500ms
    static const int ALERT_DURATION = 3000; // 3 seconds
};

#endif // METRICSWIDGET_H
#include "metricswidget.h"
#include "ui_metricswidget.h"
#include "performancemetrics.h"
#include <QTimer>
#include <QString>

MetricsWidget::MetricsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MetricsWidget)
    , m_metrics(nullptr)
    , m_updateTimer(new QTimer(this))
    , m_alertTimer(new QTimer(this))
{
    ui->setupUi(this);
    
    // Setup update timer
    m_updateTimer->setInterval(DEFAULT_UPDATE_INTERVAL);
    connect(m_updateTimer, &QTimer::timeout, this, &MetricsWidget::updateMetrics);
    m_updateTimer->start(DEFAULT_UPDATE_INTERVAL);
    
    // Setup alert timer
    m_alertTimer->setSingleShot(true);
    connect(m_alertTimer, &QTimer::timeout, this, &MetricsWidget::resetAlertColors);
    
    // Set initial size and properties
    setMinimumSize(300, 400);
    setMaximumSize(400, 600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    
    setupStyles();
    
    // Apply main styling
    setStyleSheet(
        "QGroupBox {"
        "    font-weight: bold;"
        "    border: 2px solid #cccccc;"
        "    border-radius: 5px;"
        "    margin-top: 1ex;"
        "    padding-top: 5px;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 5px 0 5px;"
        "}"
        "QProgressBar {"
        "    border: 1px solid #cccccc;"
        "    border-radius: 3px;"
        "    text-align: center;"
        "}"
        "QProgressBar::chunk {"
        "    background-color: #4CAF50;"
        "    border-radius: 2px;"
        "}"
    );
}

MetricsWidget::~MetricsWidget()
{
    delete ui;
}

void MetricsWidget::setMetricsSource(PerformanceMetrics *metrics)
{
    m_metrics = metrics;
    
    if (m_metrics) {
        connect(m_metrics, &PerformanceMetrics::metricsUpdated,
                this, &MetricsWidget::updateMetrics);
        connect(m_metrics, &PerformanceMetrics::performanceAlert,
                this, &MetricsWidget::onPerformanceAlert);
    }
}

void MetricsWidget::setMetricsVisible(bool visible)
{
    setVisible(visible);
    if (visible && m_updateTimer) {
        m_updateTimer->start();
    } else if (m_updateTimer) {
        m_updateTimer->stop();
    }
}

void MetricsWidget::setUpdateInterval(int intervalMs)
{
    if (m_updateTimer) {
        m_updateTimer->setInterval(intervalMs);
    }
}

void MetricsWidget::updateMetrics()
{
    if (!m_metrics) return;
    
    updatePerformanceMetrics();
    updateTrafficFlowMetrics();
    updateIntersectionMetrics();
    updateSystemMetrics();
}

void MetricsWidget::updatePerformanceMetrics()
{
    if (!m_metrics) return;
    
    // Update FPS
    ui->fpsValue->setText(formatValue(m_metrics->getCurrentFPS(), 1));
    
    // Update update time
    ui->updateTimeValue->setText(formatValue(m_metrics->getAverageUpdateTime(), 2, " ms"));
    
    // Update collision time
    ui->collisionTimeValue->setText(formatValue(m_metrics->getAverageCollisionTime(), 2, " ms"));
    
    // Update memory usage
    double memory = m_metrics->getCurrentMemoryUsage();
    ui->memoryValue->setText(formatValue(memory, 1, " MB"));
    ui->memoryBar->setValue(static_cast<int>(memory));
}

void MetricsWidget::updateTrafficFlowMetrics()
{
    if (!m_metrics) return;
    
    // Update vehicle counts
    ui->totalVehiclesValue->setText(QString::number(m_metrics->getTotalVehicleCount()));
    ui->activeVehiclesValue->setText(QString::number(m_metrics->getActiveVehicleCount()));
    ui->queuedVehiclesValue->setText(QString::number(m_metrics->getQueuedVehicleCount()));
    
    // Update speed and throughput
    ui->avgSpeedValue->setText(formatValue(m_metrics->getAverageSpeed(), 1));
    ui->throughputValue->setText(formatValue(m_metrics->getThroughputPerMinute(), 1, "/min"));
    
    // Update wait time (convert from ms to seconds)
    ui->avgWaitValue->setText(formatValue(m_metrics->getAverageWaitTime() / 1000.0, 1, " s"));
}

void MetricsWidget::updateIntersectionMetrics()
{
    if (!m_metrics) return;
    
    // Update queue information
    ui->maxQueueValue->setText(QString::number(m_metrics->getMaxQueueLength()));
    ui->totalQueueValue->setText(QString::number(m_metrics->getTotalQueueLength()));
    
    // Update congestion level
    double congestion = m_metrics->getCongestionLevel() * 100;
    ui->congestionValue->setText(formatValue(congestion, 1, "%"));
    ui->congestionBar->setValue(static_cast<int>(congestion));
}

void MetricsWidget::updateSystemMetrics()
{
    if (!m_metrics) return;
    
    // Update spatial grid efficiency
    double efficiency = m_metrics->getSpatialGridEfficiency() * 100;
    ui->gridEfficiencyValue->setText(formatValue(efficiency, 1, "%"));
    ui->gridEfficiencyBar->setValue(static_cast<int>(efficiency));
    
    // Grid cells info would need to be accessible from metrics
    ui->occupiedCellsValue->setText("N/A");
}

void MetricsWidget::onPerformanceAlert(const QString& metric, double value, double threshold)
{
    Q_UNUSED(threshold);
    
    // Highlight the relevant metric label
    if (metric == "FPS") {
        setLabelAlert(ui->fpsValue);
    } else if (metric == "Update Time") {
        setLabelAlert(ui->updateTimeValue);
    } else if (metric == "Memory Usage") {
        setLabelAlert(ui->memoryValue);
    }
    
    // Start alert timer to reset colors
    m_alertTimer->start(ALERT_DURATION);
}

void MetricsWidget::resetAlertColors()
{
    // Reset all value labels to normal style
    ui->fpsValue->setStyleSheet(m_normalStyle);
    ui->updateTimeValue->setStyleSheet(m_normalStyle);
    ui->collisionTimeValue->setStyleSheet(m_normalStyle);
    ui->memoryValue->setStyleSheet(m_normalStyle);
}

void MetricsWidget::setupStyles()
{
    // Normal style for value labels
    m_normalStyle = "QLabel { color: #333333; }";
    
    // Alert style for value labels
    m_alertStyle = "QLabel { color: #ff4444; background-color: #ffeeee; border: 1px solid #ff4444; border-radius: 3px; padding: 2px; }";
    
    // Apply normal style to all value labels
    ui->fpsValue->setStyleSheet(m_normalStyle);
    ui->updateTimeValue->setStyleSheet(m_normalStyle);
    ui->collisionTimeValue->setStyleSheet(m_normalStyle);
    ui->memoryValue->setStyleSheet(m_normalStyle);
    ui->totalVehiclesValue->setStyleSheet(m_normalStyle);
    ui->activeVehiclesValue->setStyleSheet(m_normalStyle);
    ui->queuedVehiclesValue->setStyleSheet(m_normalStyle);
    ui->avgSpeedValue->setStyleSheet(m_normalStyle);
    ui->throughputValue->setStyleSheet(m_normalStyle);
    ui->avgWaitValue->setStyleSheet(m_normalStyle);
    ui->maxQueueValue->setStyleSheet(m_normalStyle);
    ui->totalQueueValue->setStyleSheet(m_normalStyle);
    ui->congestionValue->setStyleSheet(m_normalStyle);
    ui->gridEfficiencyValue->setStyleSheet(m_normalStyle);
    ui->occupiedCellsValue->setStyleSheet(m_normalStyle);
}

QString MetricsWidget::formatValue(double value, int decimals, const QString& unit) const
{
    return QString("%1%2").arg(value, 0, 'f', decimals).arg(unit);
}

void MetricsWidget::setLabelAlert(QLabel* label, bool alert)
{
    if (alert) {
        label->setStyleSheet(m_alertStyle);
    } else {
        label->setStyleSheet(m_normalStyle);
    }
}
#include "metricswidget.h"
#include "ui_metricswidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPalette>
#include <QStyleOption>
#include <QPainter>

MetricsWidget::MetricsWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MetricsWidget)
    , m_metrics(nullptr)
{
    ui->setupUi(this);
    setupUI();
    
    // Setup update timer
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &MetricsWidget::updateMetrics);
    m_updateTimer->start(DEFAULT_UPDATE_INTERVAL);
    
    // Setup alert timer
    m_alertTimer = new QTimer(this);
    m_alertTimer->setSingleShot(true);
    connect(m_alertTimer, &QTimer::timeout, this, &MetricsWidget::resetAlertColors);
    
    // Set initial size and properties
    setMinimumSize(300, 400);
    setMaximumSize(400, 600);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    
    // Apply styling
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
    // Cleanup is handled automatically by Qt parent-child relationship
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

void MetricsWidget::setupUI()
{
    m_mainLayout = new QGridLayout(this);
    m_mainLayout->setSpacing(5);
    m_mainLayout->setContentsMargins(5, 5, 5, 5);
    
    // Setup fonts
    m_headerFont = font();
    m_headerFont.setBold(true);
    m_headerFont.setPointSize(font().pointSize() + 1);
    
    m_valueFont = font();
    m_valueFont.setFamily("Courier New"); // Monospaced for better alignment
    
    // Setup styles
    m_normalStyle = "color: black;";
    m_alertStyle = "color: red; font-weight: bold;";
    
    createPerformanceGroup();
    createTrafficFlowGroup();
    createIntersectionGroup();
    createSystemGroup();
    
    // Add groups to main layout
    m_mainLayout->addWidget(m_performanceGroup, 0, 0);
    m_mainLayout->addWidget(m_trafficGroup, 1, 0);
    m_mainLayout->addWidget(m_intersectionGroup, 2, 0);
    m_mainLayout->addWidget(m_systemGroup, 3, 0);
    
    // Add stretch to push everything to top
    m_mainLayout->setRowStretch(4, 1);
}

void MetricsWidget::createPerformanceGroup()
{
    m_performanceGroup = new QGroupBox("Performance", this);
    QGridLayout *layout = new QGridLayout(m_performanceGroup);
    
    int row = 0;
    
    // FPS
    m_fpsLabel = new QLabel("FPS:");
    m_fpsLabel->setFont(m_headerFont);
    m_fpsValue = new QLabel("0.0");
    m_fpsValue->setFont(m_valueFont);
    layout->addWidget(m_fpsLabel, row, 0);
    layout->addWidget(m_fpsValue, row++, 1);
    
    // Update Time
    m_updateTimeLabel = new QLabel("Update Time:");
    m_updateTimeLabel->setFont(m_headerFont);
    m_updateTimeValue = new QLabel("0.00 ms");
    m_updateTimeValue->setFont(m_valueFont);
    layout->addWidget(m_updateTimeLabel, row, 0);
    layout->addWidget(m_updateTimeValue, row++, 1);
    
    // Collision Time
    m_collisionTimeLabel = new QLabel("Collision Time:");
    m_collisionTimeLabel->setFont(m_headerFont);
    m_collisionTimeValue = new QLabel("0.00 ms");
    m_collisionTimeValue->setFont(m_valueFont);
    layout->addWidget(m_collisionTimeLabel, row, 0);
    layout->addWidget(m_collisionTimeValue, row++, 1);
    
    // Memory Usage
    m_memoryLabel = new QLabel("Memory:");
    m_memoryLabel->setFont(m_headerFont);
    m_memoryValue = new QLabel("0.0 MB");
    m_memoryValue->setFont(m_valueFont);
    m_memoryBar = new QProgressBar();
    m_memoryBar->setRange(0, 1000); // 0-1000 MB range
    layout->addWidget(m_memoryLabel, row, 0);
    layout->addWidget(m_memoryValue, row++, 1);
    layout->addWidget(m_memoryBar, row++, 0, 1, 2);
}

void MetricsWidget::createTrafficFlowGroup()
{
    m_trafficGroup = new QGroupBox("Traffic Flow", this);
    QGridLayout *layout = new QGridLayout(m_trafficGroup);
    
    int row = 0;
    
    // Total Vehicles
    m_totalVehiclesLabel = new QLabel("Total Vehicles:");
    m_totalVehiclesLabel->setFont(m_headerFont);
    m_totalVehiclesValue = new QLabel("0");
    m_totalVehiclesValue->setFont(m_valueFont);
    layout->addWidget(m_totalVehiclesLabel, row, 0);
    layout->addWidget(m_totalVehiclesValue, row++, 1);
    
    // Active Vehicles
    m_activeVehiclesLabel = new QLabel("Active:");
    m_activeVehiclesLabel->setFont(m_headerFont);
    m_activeVehiclesValue = new QLabel("0");
    m_activeVehiclesValue->setFont(m_valueFont);
    layout->addWidget(m_activeVehiclesLabel, row, 0);
    layout->addWidget(m_activeVehiclesValue, row++, 1);
    
    // Queued Vehicles
    m_queuedVehiclesLabel = new QLabel("Queued:");
    m_queuedVehiclesLabel->setFont(m_headerFont);
    m_queuedVehiclesValue = new QLabel("0");
    m_queuedVehiclesValue->setFont(m_valueFont);
    layout->addWidget(m_queuedVehiclesLabel, row, 0);
    layout->addWidget(m_queuedVehiclesValue, row++, 1);
    
    // Average Speed
    m_avgSpeedLabel = new QLabel("Avg Speed:");
    m_avgSpeedLabel->setFont(m_headerFont);
    m_avgSpeedValue = new QLabel("0.0");
    m_avgSpeedValue->setFont(m_valueFont);
    layout->addWidget(m_avgSpeedLabel, row, 0);
    layout->addWidget(m_avgSpeedValue, row++, 1);
    
    // Throughput
    m_throughputLabel = new QLabel("Throughput:");
    m_throughputLabel->setFont(m_headerFont);
    m_throughputValue = new QLabel("0.0/min");
    m_throughputValue->setFont(m_valueFont);
    layout->addWidget(m_throughputLabel, row, 0);
    layout->addWidget(m_throughputValue, row++, 1);
    
    // Wait Time
    m_waitTimeLabel = new QLabel("Wait Time:");
    m_waitTimeLabel->setFont(m_headerFont);
    m_waitTimeValue = new QLabel("0.0 s");
    m_waitTimeValue->setFont(m_valueFont);
    layout->addWidget(m_waitTimeLabel, row, 0);
    layout->addWidget(m_waitTimeValue, row++, 1);
}

void MetricsWidget::createIntersectionGroup()
{
    m_intersectionGroup = new QGroupBox("Intersection", this);
    QGridLayout *layout = new QGridLayout(m_intersectionGroup);
    
    int row = 0;
    
    // Max Queue Length
    m_maxQueueLabel = new QLabel("Max Queue:");
    m_maxQueueLabel->setFont(m_headerFont);
    m_maxQueueValue = new QLabel("0");
    m_maxQueueValue->setFont(m_valueFont);
    layout->addWidget(m_maxQueueLabel, row, 0);
    layout->addWidget(m_maxQueueValue, row++, 1);
    
    // Total Queue Length
    m_totalQueueLabel = new QLabel("Total Queue:");
    m_totalQueueLabel->setFont(m_headerFont);
    m_totalQueueValue = new QLabel("0");
    m_totalQueueValue->setFont(m_valueFont);
    layout->addWidget(m_totalQueueLabel, row, 0);
    layout->addWidget(m_totalQueueValue, row++, 1);
    
    // Congestion Level
    m_congestionLabel = new QLabel("Congestion:");
    m_congestionLabel->setFont(m_headerFont);
    m_congestionValue = new QLabel("0.0%");
    m_congestionValue->setFont(m_valueFont);
    m_congestionBar = new QProgressBar();
    m_congestionBar->setRange(0, 100);
    layout->addWidget(m_congestionLabel, row, 0);
    layout->addWidget(m_congestionValue, row++, 1);
    layout->addWidget(m_congestionBar, row++, 0, 1, 2);
    
    // Individual Queue Lengths
    QLabel *queueHeader = new QLabel("Queue Lengths:");
    queueHeader->setFont(m_headerFont);
    layout->addWidget(queueHeader, row++, 0, 1, 2);
    
    // NS Queue
    m_queueNSLabel = new QLabel("N-S:");
    m_queueNSValue = new QLabel("0");
    m_queueNSValue->setFont(m_valueFont);
    layout->addWidget(m_queueNSLabel, row, 0);
    layout->addWidget(m_queueNSValue, row++, 1);
    
    // SN Queue
    m_queueSNLabel = new QLabel("S-N:");
    m_queueSNValue = new QLabel("0");
    m_queueSNValue->setFont(m_valueFont);
    layout->addWidget(m_queueSNLabel, row, 0);
    layout->addWidget(m_queueSNValue, row++, 1);
    
    // EW Queue
    m_queueEWLabel = new QLabel("E-W:");
    m_queueEWValue = new QLabel("0");
    m_queueEWValue->setFont(m_valueFont);
    layout->addWidget(m_queueEWLabel, row, 0);
    layout->addWidget(m_queueEWValue, row++, 1);
    
    // WE Queue
    m_queueWELabel = new QLabel("W-E:");
    m_queueWEValue = new QLabel("0");
    m_queueWEValue->setFont(m_valueFont);
    layout->addWidget(m_queueWELabel, row, 0);
    layout->addWidget(m_queueWEValue, row++, 1);
}

void MetricsWidget::createSystemGroup()
{
    m_systemGroup = new QGroupBox("System Optimization", this);
    QGridLayout *layout = new QGridLayout(m_systemGroup);
    
    int row = 0;
    
    // Grid Efficiency
    m_gridEfficiencyLabel = new QLabel("Grid Efficiency:");
    m_gridEfficiencyLabel->setFont(m_headerFont);
    m_gridEfficiencyValue = new QLabel("0.0%");
    m_gridEfficiencyValue->setFont(m_valueFont);
    m_gridEfficiencyBar = new QProgressBar();
    m_gridEfficiencyBar->setRange(0, 100);
    layout->addWidget(m_gridEfficiencyLabel, row, 0);
    layout->addWidget(m_gridEfficiencyValue, row++, 1);
    layout->addWidget(m_gridEfficiencyBar, row++, 0, 1, 2);
    
    // Grid Cells
    m_gridCellsLabel = new QLabel("Grid Cells:");
    m_gridCellsLabel->setFont(m_headerFont);
    m_gridCellsValue = new QLabel("0/0");
    m_gridCellsValue->setFont(m_valueFont);
    layout->addWidget(m_gridCellsLabel, row, 0);
    layout->addWidget(m_gridCellsValue, row++, 1);
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
    m_fpsValue->setText(formatValue(m_metrics->getCurrentFPS(), 1));
    m_updateTimeValue->setText(formatValue(m_metrics->getAverageUpdateTime(), 2, " ms"));
    m_collisionTimeValue->setText(formatValue(m_metrics->getAverageCollisionTime(), 2, " ms"));
    
    double memory = m_metrics->getCurrentMemoryUsage();
    m_memoryValue->setText(formatValue(memory, 1, " MB"));
    m_memoryBar->setValue(static_cast<int>(memory));
}

void MetricsWidget::updateTrafficFlowMetrics()
{
    m_totalVehiclesValue->setText(QString::number(m_metrics->getTotalVehicleCount()));
    m_activeVehiclesValue->setText(QString::number(m_metrics->getActiveVehicleCount()));
    m_queuedVehiclesValue->setText(QString::number(m_metrics->getQueuedVehicleCount()));
    m_avgSpeedValue->setText(formatValue(m_metrics->getAverageSpeed(), 1));
    m_throughputValue->setText(formatValue(m_metrics->getThroughputPerMinute(), 1, "/min"));
    m_waitTimeValue->setText(formatValue(m_metrics->getAverageWaitTime() / 1000.0, 1, " s"));
}

void MetricsWidget::updateIntersectionMetrics()
{
    m_maxQueueValue->setText(QString::number(m_metrics->getMaxQueueLength()));
    m_totalQueueValue->setText(QString::number(m_metrics->getTotalQueueLength()));
    
    double congestion = m_metrics->getCongestionLevel() * 100;
    m_congestionValue->setText(formatValue(congestion, 1, "%"));
    m_congestionBar->setValue(static_cast<int>(congestion));
    
    // Individual queues would need to be implemented in PerformanceMetrics
    // For now, showing placeholder values
    m_queueNSValue->setText("0");
    m_queueSNValue->setText("0");
    m_queueEWValue->setText("0");
    m_queueWEValue->setText("0");
}

void MetricsWidget::updateSystemMetrics()
{
    double efficiency = m_metrics->getSpatialGridEfficiency() * 100;
    m_gridEfficiencyValue->setText(formatValue(efficiency, 1, "%"));
    m_gridEfficiencyBar->setValue(static_cast<int>(efficiency));
    
    // Grid cells info would need to be accessible from metrics
    m_gridCellsValue->setText("N/A");
}

void MetricsWidget::onPerformanceAlert(const QString& metric, double value, double threshold)
{
    Q_UNUSED(threshold);
    
    // Highlight the relevant metric label
    if (metric == "FPS") {
        setLabelAlert(m_fpsValue);
    } else if (metric == "Update Time") {
        setLabelAlert(m_updateTimeValue);
    } else if (metric == "Memory Usage") {
        setLabelAlert(m_memoryValue);
    }
    
    // Start alert timer to reset colors
    m_alertTimer->start(ALERT_DURATION);
}

void MetricsWidget::resetAlertColors()
{
    // Reset all value labels to normal style
    m_fpsValue->setStyleSheet(m_normalStyle);
    m_updateTimeValue->setStyleSheet(m_normalStyle);
    m_collisionTimeValue->setStyleSheet(m_normalStyle);
    m_memoryValue->setStyleSheet(m_normalStyle);
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
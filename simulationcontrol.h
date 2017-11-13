#ifndef SIMULATIONCONTROL_H
#define SIMULATIONCONTROL_H

#include <QWidget>
#include "mainwindow.h"
#include "vehicle.h"
namespace Ui {
class SimulationControl;
}
class MainWindow;
class SimulationControl : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControl(QWidget *parent = 0);
    ~SimulationControl();

private slots:
    void on_m_setup_button_clicked();
    void on_m_setup_birth_rate_button_clicked();
    void on_m_stop_clicked();
    void on_m_auto_traffic_clicked();
    void on_m_random_birth_clicked();

private:
    Ui::SimulationControl *ui;
    QList<QTimer> m_timer;
};

#endif // SIMULATIONCONTROL_H

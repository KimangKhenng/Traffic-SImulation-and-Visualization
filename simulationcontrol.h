#ifndef SIMULATIONCONTROL_H
#define SIMULATIONCONTROL_H

#include "mainwindow.h"
#include "vehicle.h"
#include "generator.h"

namespace Ui {
class SimulationControl;
}
class MainWindow;
class SimulationControl : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControl(QWidget *parent = nullptr);
    ~SimulationControl();
    void initialize(QWidget *widget);
    Generator *generator() const;

private slots:
    void on_m_setup_button_clicked();
    void on_m_setup_birth_rate_button_clicked();
    void on_m_stop_clicked();
    void on_m_auto_traffic_clicked();
    void on_m_random_birth_clicked();

private:
    MainWindow *m_w;
    Ui::SimulationControl *ui;
    QList<QTimer> m_timer;
    Generator *m_generator;
};

#endif // SIMULATIONCONTROL_H

#ifndef SIMULATIONCONTROLWIDGET_H
#define SIMULATIONCONTROLWIDGET_H

#include <QWidget>
#include "Utilities/roadintersectionsimulation.h"
namespace Ui {
class SimulationControlWidget;
}

class SimulationControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControlWidget(QWidget *parent = 0);
    void installSimulation(RoadIntersectionSimulation *instance);
    ~SimulationControlWidget();


private slots:
    void on_start_simulation_button_clicked();

    void on_random_setup_clicked();

    void on_help_setup_button_clicked();

private:
    Ui::SimulationControlWidget *ui;
    RoadIntersectionSimulation *m_Simulation;
};

#endif // SIMULATIONCONTROLWIDGET_H

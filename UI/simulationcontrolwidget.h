#ifndef SIMULATIONCONTROLWIDGET_H
#define SIMULATIONCONTROLWIDGET_H

#include "Utilities/roadintersectionsimulation.h"
namespace Ui {
class SimulationControlWidget;
}

class SimulationControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControlWidget(QWidget *parent = 0);
//    void installSimulation(RoadIntersectionSimulation *instance);
    ~SimulationControlWidget();


private slots:
    void on_start_simulation_button_clicked();

    void on_random_setup_clicked();

    void on_help_setup_button_clicked();

signals:
    void inputedReady(double north_south,
                      double south_north,
                      double west_east,
                      double east_west,
                      double red_ligt,
                      double green_light,
                      double left_green);
    void helpClicked();
    void randomClicked();

private:
    Ui::SimulationControlWidget *ui;
//    RoadIntersectionSimulation *m_Simulation;
};

#endif // SIMULATIONCONTROLWIDGET_H

#include "simulationcontrolwidget.h"
#include "ui_simulationcontrolwidget.h"
#include <QDebug>
SimulationControlWidget::SimulationControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControlWidget)
{
    ui->setupUi(this);
}

void SimulationControlWidget::installSimulation(RoadIntersectionSimulation *instance)
{
    m_Simulation = instance;
}

SimulationControlWidget::~SimulationControlWidget()
{
    delete ui;
}

void SimulationControlWidget::on_start_simulation_button_clicked()
{

}

void SimulationControlWidget::on_random_setup_clicked()
{

}

void SimulationControlWidget::on_help_setup_button_clicked()
{

}

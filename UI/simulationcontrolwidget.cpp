#include "simulationcontrolwidget.h"
#include "ui_simulationcontrolwidget.h"
#include <QDebug>
SimulationControlWidget::SimulationControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControlWidget)
{
    ui->setupUi(this);
}

//void SimulationControlWidget::installSimulation(RoadIntersectionSimulation *instance)
//{
//    m_Simulation = instance;

//}

SimulationControlWidget::~SimulationControlWidget()
{
    delete ui;
}

void SimulationControlWidget::on_start_simulation_button_clicked()
{
    emit inputedReady(ui->north_south_input->value(),
                      ui->south_north_input->value(),
                      ui->west_east_input->value(),
                      ui->east_west_input->value(),
                      ui->red_light_input->value(),
                      ui->green_light_input->value(),
                      ui->left_green_light_input->value());
    hide();
}

void SimulationControlWidget::on_random_setup_clicked()
{
    emit randomClicked();
    hide();
}

void SimulationControlWidget::on_help_setup_button_clicked()
{
    emit helpClicked();
    hide();
}

#include "simulationcontrol.h"
#include "ui_simulationcontrol.h"

SimulationControl::SimulationControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControl)
{
    ui->setupUi(this);
}

SimulationControl::~SimulationControl()
{
    delete ui;
}

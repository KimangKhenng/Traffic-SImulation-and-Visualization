#include "simulationcontrolwidget.h"
#include "ui_simulationcontrolwidget.h"
#include <QDebug>
SimulationControlWidget::SimulationControlWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControlWidget)
{
    ui->setupUi(this);
}

SimulationControlWidget::~SimulationControlWidget()
{
    delete ui;
}

void SimulationControlWidget::on_pushButton_clicked()
{
    qDebug()<<"Test!";
}

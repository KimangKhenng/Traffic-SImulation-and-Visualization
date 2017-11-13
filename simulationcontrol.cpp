#include "simulationcontrol.h"
#include "ui_simulationcontrol.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
SimulationControl::SimulationControl(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationControl)

{
    ui->setupUi(this);
    this->setFixedSize (300,200);
    this->setWindowTitle ("Simulation Controller");
    ui->m_green->setValidator(new QIntValidator(0, 10000, ui->m_green));
    ui->m_red->setValidator(new QIntValidator(0, 10000, ui->m_red));
    ui->m_yellow->setValidator(new QIntValidator(0, 1000, ui->m_yellow));
    ui->m_road_1->setValidator(new QIntValidator(0, 100, ui->m_road_1));
    ui->m_road_2->setValidator(new QIntValidator(0, 100, ui->m_road_2));
    ui->m_road_3->setValidator(new QIntValidator(0, 100, ui->m_road_3));
    ui->m_road_4->setValidator(new QIntValidator(0, 100, ui->m_road_4));
}

SimulationControl::~SimulationControl()
{
    qDebug()<<"Hello";
    if(dynamic_cast<MainWindow *>(this->parentWidget())){
        (dynamic_cast<MainWindow *>(this->parentWidget()))->trunSimControlCheckOff();
    }
    delete ui;
}

void SimulationControl::on_m_setup_button_clicked()
{

}

void SimulationControl::on_m_setup_birth_rate_button_clicked()
{

}

void SimulationControl::on_m_stop_clicked()
{

}

void SimulationControl::on_m_auto_traffic_clicked()
{

}

void SimulationControl::on_m_random_birth_clicked()
{
    if(dynamic_cast<MainWindow *>(this->parentWidget())){
        (dynamic_cast<MainWindow *>(this->parentWidget()))->set_up_random();
    }
}

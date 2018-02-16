#include "simulationcontrol.h"
#include "ui_simulationcontrol.h"
#include "ui_mainwindow.h"
#include "mainwindow.h"
#include <QDebug>
SimulationControl::SimulationControl(QWidget *parent) :
    QWidget(parent),m_w(nullptr),
    ui(new Ui::SimulationControl)

{

    ui->setupUi(this);
    setWindowFlags(Qt::Widget);
    //this->setFixedSize (300,200);
    this->setWindowTitle ("Simulation Controller");
    ui->m_green->setValidator(new QIntValidator(0, 10000, ui->m_green));
    ui->m_red->setValidator(new QIntValidator(0, 10000, ui->m_red));
    ui->m_yellow->setValidator(new QIntValidator(0, 1000, ui->m_yellow));
    ui->m_road_1->setValidator(new QIntValidator(0, 100, ui->m_road_1));
    ui->m_road_2->setValidator(new QIntValidator(0, 100, ui->m_road_2));
    ui->m_road_3->setValidator(new QIntValidator(0, 100, ui->m_road_3));
    ui->m_road_4->setValidator(new QIntValidator(0, 100, ui->m_road_4));
    //qDebug()<<"Hello";



    setWindowTitle(QApplication::translate("toplevel", "Simulation Control"));

    //setWindowFlags(Qt::Window);
}

SimulationControl::~SimulationControl()
{
    delete ui;
}

void SimulationControl::initialize(MainWindow *widget)
{
    m_generator = new Generator();
    if(dynamic_cast<MainWindow *>(widget)){
        m_w = dynamic_cast<MainWindow *>(widget);
        m_generator->setScene(m_w->scene());
        m_generator->setMethod(m_w->getCurrentMethod());
        m_generator->setMode(m_w->getCurrentVehicleMethod());
        //qDebug()<<"Hello";
    }
}

void SimulationControl::on_m_setup_button_clicked()
{

}

void SimulationControl::on_m_setup_birth_rate_button_clicked()
{
    m_generator->setTimer(4000/(ui->m_road_1->text().toInt())
                          ,4000/(ui->m_road_2->text().toInt())
                          ,4000/(ui->m_road_3->text().toInt())
                          ,4000/(ui->m_road_4->text().toInt())
                          );
    m_generator->startGenerator();
    m_w->turnOnSimulationState();
    ui->m_road_1->setText("0");
    ui->m_road_2->setText("0");
    ui->m_road_3->setText("0");
    ui->m_road_4->setText("0");

}

void SimulationControl::on_m_stop_clicked()
{

}

void SimulationControl::on_m_auto_traffic_clicked()
{

}

void SimulationControl::on_m_random_birth_clicked()
{
    m_generator->startAutoGeneraion();
    m_w->turnOnSimulationState();
}

Generator *SimulationControl::generator() const
{
    return m_generator;
}

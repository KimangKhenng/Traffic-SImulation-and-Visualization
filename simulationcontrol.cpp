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

void SimulationControl::get_main_windows(MainWindow *window)
{
    m_main_window = window;
}

SimulationControl::~SimulationControl()
{
    delete ui;
}

void SimulationControl::on_m_setup_button_clicked()
{

    for(int i = 0;i<m_main_window->get_traffic_list ()->size ();i++){
        m_main_window->get_traffic_list ()->at (i)->set_duration (ui->m_red->text ().toInt (),
                                                                  ui->m_yellow->text ().toInt (),
                                                                  ui->m_green->text ().toInt ());
        m_main_window->get_traffic_list ()->at (i)->set_up ();
        m_main_window->get_traffic_list ()->at (i)->start ();
    }
}

void SimulationControl::on_m_setup_birth_rate_button_clicked()
{

}

void SimulationControl::on_m_stop_clicked()
{
    //Check if already running
    for(int i = 0 ; i <m_main_window->get_traffic_list ()->size ();i++){
        qDebug()<<m_main_window->get_traffic_list ()->at (i)->is_running ();
        if(m_main_window->get_traffic_list ()->at (i)->is_running () == true){
            m_main_window->get_traffic_list ()->at (i)->stop ();
        }
    }
}

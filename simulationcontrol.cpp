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

void SimulationControl::get_traffic_list(QList<Traffic_Light_widget *> *m_traffic)
{
    m_traffic_widget_list = m_traffic;
}

SimulationControl::~SimulationControl()
{
    delete ui;
}

void SimulationControl::on_m_setup_button_clicked()
{

    for(int i = 0;i<m_main_window->get_traffic_list ()->size ();i++){
        if(m_main_window->get_traffic_list ()->at (i)->get_check_state ()){
        m_main_window->get_traffic_list ()->at (i)->set_duration (ui->m_red->text ().toInt (),
                                                                  ui->m_yellow->text ().toInt (),
                                                                  ui->m_green->text ().toInt ());
        m_main_window->get_traffic_list ()->at (i)->set_up ();
        m_main_window->get_traffic_list ()->at (i)->set_initial_state_nornal ();
        m_main_window->get_traffic_list ()->at (i)->start ();
        }
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

void SimulationControl::on_m_auto_traffic_clicked()
{
    for(int i = 0;i<m_main_window->get_traffic_list ()->size ();i++){
    m_main_window->get_traffic_list ()->at (i)->set_duration (5000,
                                                              1000,
                                                              5000);
    }
    // Initialize first traffic
    m_main_window->get_traffic_list ()->at (0)->set_up ();
    m_main_window->get_traffic_list ()->at (0)->set_initial_state (false,true);
    m_main_window->get_traffic_list ()->at (0)->start ();
    // Initialize second traffic
    m_main_window->get_traffic_list ()->at (1)->set_up ();
    m_main_window->get_traffic_list ()->at (1)->set_initial_state (true,false);
    m_main_window->get_traffic_list ()->at (1)->start ();
    // Initialize third traffic
    m_main_window->get_traffic_list ()->at (2)->set_up ();
    m_main_window->get_traffic_list ()->at (2)->set_initial_state (false,true);
    m_main_window->get_traffic_list ()->at (2)->start ();
    // Initialize fourth traffic
    m_main_window->get_traffic_list ()->at (3)->set_up ();
    m_main_window->get_traffic_list ()->at (3)->set_initial_state (true,false);
    m_main_window->get_traffic_list ()->at (3)->start ();

}

void SimulationControl::on_m_random_birth_clicked()
{
    on_m_auto_traffic_clicked ();
    m_main_window->set_up_random ();
}

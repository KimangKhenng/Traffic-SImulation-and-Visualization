#include "simulationcontrol.h"
#include "ui_simulationcontrol.h"

SimulationControl::SimulationControl(QWidget *parent) :
    QWidget(parent),m_w(nullptr),
    ui(new Ui::SimulationControl)

{

    ui->setupUi(this);
    setWindowFlags(Qt::Widget);
    //this->setFixedSize (300,200);
    this->setWindowTitle ("Simulation Controller");
    ui->m_green->setValidator(new QIntValidator(0, 10000, ui->m_green));
    //ui->m_red->setValidator(new QIntValidator(0, 10000, ui->m_red));
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

void SimulationControl::initialize(QWidget *widget)
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

void SimulationControl::stopGenerating()
{
    m_generator->stopGenerator();
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
//    ui->m_road_1->setText("0");
//    ui->m_road_2->setText("0");
//    ui->m_road_3->setText("0");
//    ui->m_road_4->setText("0");

}

void SimulationControl::on_m_stop_clicked()
{
    m_w->getController()->stopTrafficLightAll();
}

void SimulationControl::on_m_auto_traffic_clicked()
{
    m_w->getController()->setLightDuration(5000,3000,500,6000);
}

void SimulationControl::on_m_random_birth_clicked()
{
    m_generator->startAutoGeneraion();
    m_w->turnOnSimulationState();
    m_w->getController()->setLightDuration(3000,2000,500,6000);
    m_w->getController()->startTrafficLightAll();
    // Ui Stuff
    m_w->set3LaneCheck(true);
    m_w->setGenMethod(GENMETHOD::GEN_3);
    m_w->setGoThroguht(false);
    m_w->setSimMode(VEHICLEMETHOD::SIGHTSEEING);
    m_w->setTrafficState(true);
//    m_w->getUi()->m_3_lanes->setChecked(true);
//    m_w->getUi()->m_simulation_control_widget->generator()->setMethod(GENMETHOD::GEN_3);
//    m_w->getUi()->m_go_though->setChecked(false);
//    m_w->getUi()->m_simulation_control_widget->generator()->setMode(VEHICLEMETHOD::SIGHTSEEING);
//    m_w->getUi()->m_no_traffic->setChecked(true);
    //m_w->getUi()->m_visualize_panel_check_box->setChecked(true);
    m_w->showTraffic(true);
    //m_w->getUi()->m_visualize_frame->show();

}


void SimulationControl::on_m_setup_birth_rate_button_3_clicked()
{

}

Generator *SimulationControl::generator() const
{
    return m_generator;
}

void SimulationControl::setMethod(const GENMETHOD &m)
{
    m_generator->setMethod(m);
}

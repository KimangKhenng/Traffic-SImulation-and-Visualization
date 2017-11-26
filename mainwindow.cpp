#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <time.h>
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),m_road(nullptr),m_simulate_state(false)
  ,m_sightseeing(false),m_simulation_control_widget(nullptr),m_data_widget(nullptr)
{
        ui->setupUi(this);
        setWindowTitle ("Intersection Road Simulation and Visulization");
        set_up ();
        ui->stackedWidget->setCurrentIndex(0);
        m_machine_state = new QTimer();
        this->connect (m_machine_state,SIGNAL(timeout()),this,SLOT(check_state()));
        //QObject::connect(m_machine_state,SIGNAL(timeout()),m_scene,SLOT(advance()));
        m_machine_state->start(TIME_UNIT);
        srand(time(NULL));
}
void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if(event->key () == Qt::Key_Space){
        if(m_simulate_state){
            on_pause_clicked ();
        }else{
            on_play_clicked ();
        }
    }
}
void MainWindow::turnOnSimulationState()
{
    m_simulate_state = true;
}

void MainWindow::turnOffSimulationState()
{
    m_simulate_state = false;
}

void MainWindow::trunSimControlCheckOff()
{
    ui->m_control_button->setCheckState(Qt::CheckState::Unchecked);
}

GENMETHOD MainWindow::getCurrentMethod()
{
    if(ui->m_3_lanes->isChecked()){
        return GENMETHOD::GEN_3;
    }
    if(ui->m_5_lanes->isChecked()){
        return GENMETHOD::GEN_5;
    }
    if(ui->m_no_turn->isChecked()){
        return GENMETHOD::NO_TURN;
    }
    return GENMETHOD::NO_TURN;
}

VEHICLEMETHOD MainWindow::getCurrentVehicleMethod()
{
    if(ui->m_go_though->isChecked()){
        return VEHICLEMETHOD::GO_THROUGH;
    }
    return VEHICLEMETHOD::SIGHTSEEING;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_state()
{
//    qDebug()<<"Simulation State"<<m_simulate_state;
    /////////////////
    /// \brief items
    ///Getting Item in Scene and Cast to Vehicles
    ////////////////
    QList<QGraphicsItem *> items = m_scene->items();
    QList<Vehicle *> car;
    QList<TrafficDetector *> detector;
    for(int i = 0 ; i < items.size() ; ++i){
        Vehicle *v = dynamic_cast<Vehicle *>(items.at(i));
        TrafficDetector *d = dynamic_cast<TrafficDetector *>(items.at(i));
        if(v){
            car.append(v);
        }
        if(d){
            detector.append(d);
        }
    }
    //qDebug()<<car.size();
    for(int i = 0 ; i<car.size() ; ++i){
        if(m_simulate_state){
            //car.at(i)->setActionOn();
            car.at(i)->turnOnEngine();
        }else{
            //car.at(i)->setActionOff();
            car.at(i)->turnOffEngine();
        }
        if(this->m_sightseeing){
            car.at(i)->turnOnSightSeeing();
        }else{
            car.at(i)->turnOffSightSeeing();
        }
        if(car.at(i)->get_current_index() >= 99){
            //m_scene->removeItem(car.at(i));
            delete car.at(i);
        }
    }
    for(int i = 0 ; i < detector.size() ; ++i){
        if(m_simulate_state){
            //car.at(i)->setActionOn();
            detector.at(i)->startEngine();
        }else{
            //car.at(i)->setActionOff();
            detector.at(i)->stopEngine();
        }
    }
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_play_clicked()
{

    m_simulate_state = true;


}
void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_open_simulation_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_reset_clicked()
{
//    m_car_list_1->clear ();
    m_scene->clear();
    m_simulation_control_widget->generator()->stopGenerator();
}

void MainWindow::on_pause_clicked()
{
    m_simulate_state = false;
}

void MainWindow::on_stop_clicked()
{
//    m_car_list_1->first ()->get_timer ()->stop ();
}

void MainWindow::set_up()
{
    //Add Road and Background to scene
    QGraphicsPixmapItem *m_picture = new QGraphicsPixmapItem(QPixmap(":/image/Image/road-image.png").scaled (600,600));
    QGraphicsSvgItem *m_terrain = new QGraphicsSvgItem(":/image/Image/terrain.svg");
    m_path = new QGraphicsSvgItem(":/image/Image/road-path.svg");
    m_terrain->moveBy (-60,0);
    m_picture->moveBy(30,0);
    m_path->moveBy (15,-15);
    m_path->setScale (0.7);
    m_path->setZValue (-1);
    m_path->setOpacity(0);
    m_picture->setZValue (-2);
    m_terrain->setZValue (-3);
    m_scene = new SimulationScene();
    m_road = new road();
    m_scene->addItem (m_picture);
    m_scene->addItem (m_terrain);
    m_scene->addItem (m_path);
    m_scene->addText ("1",QFont("Century",18))->setPos (450,180);
    m_scene->addText ("2",QFont("Century",18))->setPos (150,180);
    m_scene->addText ("3",QFont("Century",18))->setPos (180,380);
    m_scene->addText ("4",QFont("Century",18))->setPos (400,420);
    //Add path for vehicle
    m_scene->setSceneRect(0,0,800,600);
    //Add traffic
    m_controller = new TrafficController();
    for(int i = 0 ; i < m_controller->getDetector()->size() ; ++i){
        m_controller->getDetector()->at(i)->setOpacity(0);
    }
    m_scene->addItem(m_controller);
    m_traffic_light = new QList<TrafficLight *>();
    for(int i = 0 ; i < 4 ; ++i){
        m_traffic_light->append(new TrafficLight());
        m_traffic_light->at(i)->setUpFacilities();
    }
    m_controller->setTraffic_light(m_traffic_light);
    //Arrange Traffic Light
    //TrafficLight 1
    m_traffic_light->at(0)->setPos(400,380);
    m_traffic_light->at(0)->setRegion(region::REGION_S_N);
    //TrafficLight 2
    m_traffic_light->at(1)->setRotation(90);
    m_traffic_light->at(1)->setPos(260,380);
    m_traffic_light->at(1)->setRegion(region::REGION_W_E);
    //TrafficLight 3
    m_traffic_light->at(2)->setPos(250,240);
    m_traffic_light->at(2)->setRotation(180);
    m_traffic_light->at(2)->setRegion(region::REGION_N_S);
//    m_traffic_light->at(2)->setTransform(QTransform::fromScale(1, -1));
    //TrafficLight 4
    m_traffic_light->at(3)->setPos(410,230);
    m_traffic_light->at(3)->setRotation(270);
    m_traffic_light->at(3)->setRegion(region::REGION_E_W);
    //m_traffic_light->at(3)->setTransform(QTransform::fromScale(-1, 1));
    for(int i = 0 ; i < m_traffic_light->size() ; ++i){
        for(int j = 0 ; j < m_traffic_light->at(i)->getLight()->size() ; j++){
            m_traffic_light->at(i)->getLight()->at(j)->setScale(0.8);
        }
    }
    //Add Control Widget
//    m_control_sim = new QGraphicsProxyWidget();
//    m_control_sim->setWidget (m_simulation_control_widget);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsMovable);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsFocusable);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsPanel);
//    m_control_sim->setPos (500,0);
//    m_scene->addItem (m_control_sim);
//    m_data_control = new QGraphicsProxyWidget();
    //m_data_control->setFlags (QGraphicsItem::ItemIsSelectable);
//    m_data_control->setWidget (m_data_widget);
//    m_scene->addItem (m_data_control);
//    m_data_control->setPos (500,400);
    //AddSecen
    ui->graphicsView->setScene(m_scene);
//    ui->graphicsView->Initializer();
    m_simulation_control_widget = new SimulationControl(this);
}

void MainWindow::set_up_demo()
{


}
void MainWindow::on_m_road_check_button_toggled(bool checked)
{
    if(checked){
        m_path->setOpacity(1.0);
    }else{
        m_path->setOpacity(0.0);
    }
}

void MainWindow::on_m_detector_button_clicked(bool checked)
{
    if(checked){
        m_controller->turnOnDetector();
    }else{
        m_controller->turnOffDetector();
    }
}

void MainWindow::on_m_sightseeing_button_clicked(bool checked)
{
    if(checked){
        m_sightseeing = true;
    }else{
        m_sightseeing = false;
    }
}

void MainWindow::on_m_data_widget_clicked(bool checked)
{
    if(checked){
        if(!m_data_widget){
            //qDebug()<<"Hello";
            m_data_widget = new DataWidget(this);
//            m_data_widget->setDetector(m_controller->getDetector());
            m_data_widget->setController(m_controller);
            m_data_widget->setEtimer(m_controller->getTimer());
            m_data_widget->show();
        }else{
            //qDebug()<<"Hi";
            m_data_widget->show();
        }
    }else{
        m_data_widget->hide();
    }
}

void MainWindow::on_m_control_button_clicked(bool checked)
{
    if(checked){
        if(!m_simulation_control_widget){
            //qDebug()<<"Hello";
            m_simulation_control_widget = new SimulationControl(this);
            m_simulation_control_widget->show();
        }else{
            //qDebug()<<"Hi";
            m_simulation_control_widget->show();
        }
    }else{
        m_simulation_control_widget->hide();
    }
}

void MainWindow::on_m_aboutus_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_m_manul_control_button_clicked(bool checked)
{
    if(checked){
        for(int i = 0 ; i < m_traffic_light->size() ; ++i){
            m_traffic_light->at(i)->setManualControl();
        }
    }else{

    }
}

void MainWindow::on_m_5_lanes_clicked()
{
    m_simulation_control_widget->generator()->setMethod(GENMETHOD::GEN_5);
}

void MainWindow::on_m_3_lanes_clicked()
{
    m_simulation_control_widget->generator()->setMethod(GENMETHOD::GEN_3);
}

SimulationScene *MainWindow::scene() const
{
    return m_scene;
}

void MainWindow::on_m_no_traffic_clicked(bool checked)
{
    if(checked){
        for(int i = 0 ; i < m_traffic_light->size() ; ++i){
            m_traffic_light->at(i)->setMode(TRAFFICMODE::HAS_SIGNAL);
            m_scene->addItem(m_traffic_light->at(i));
        }
    }else{
        for(int i = 0 ; i < m_traffic_light->size() ; ++i){
            m_traffic_light->at(i)->setMode(TRAFFICMODE::NO_SIGNAL);
            m_scene->removeItem(m_traffic_light->at(i));
        }
    }
}

bool MainWindow::getSimulate_state() const
{
    return m_simulate_state;
}

TrafficController *MainWindow::getController() const
{
    return m_controller;
}

void MainWindow::on_m_no_turn_clicked()
{
    m_simulation_control_widget->generator()->setMethod(GENMETHOD::NO_TURN);
}


void MainWindow::on_m_go_though_clicked(bool checked)
{
    if(checked){
        m_simulation_control_widget->generator()->setMode(VEHICLEMETHOD::GO_THROUGH);
    }else{
        m_simulation_control_widget->generator()->setMode(VEHICLEMETHOD::SIGHTSEEING);
    }

}

void MainWindow::changeVehicleMode(const VEHICLEMETHOD &mode)
{

}

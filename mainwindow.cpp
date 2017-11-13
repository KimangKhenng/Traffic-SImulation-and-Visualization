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
        QObject::connect(m_machine_state,SIGNAL(timeout()),m_scene,SLOT(advance()));
        m_machine_state->start(10);
        srand(time(NULL));
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    qDebug()<<event->size();
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
    //qDebug()<<m_traffic_widget_list->at (0)->get_current_state ()->objectName ();
}

//QList<Traffic_Light_widget *> *MainWindow::get_traffic_list()
//{
//    return m_traffic_widget_list;
//}

void MainWindow::set_duration_for_1_traffic(int red, int yellow, int green)
{
//    m_traffic_widget_list->at (0)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (0)->set_up ();
    //m_traffic_widget_list->at (0)->start ();
}

void MainWindow::set_duration_for_2_traffic(int red, int yellow, int green)
{
//    m_traffic_widget_list->at (1)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (1)->set_up ();
    //m_traffic_widget_list->at (1)->start ();
}

void MainWindow::set_duration_for_3_traffic(int red, int yellow, int green)
{
//    m_traffic_widget_list->at (2)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (2)->set_up ();
    //m_traffic_widget_list->at (2)->start ();
}

void MainWindow::set_duration_for_4_traffic(int red, int yellow, int green)
{
//    m_traffic_widget_list->at (3)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (3)->set_up ();
    //m_traffic_widget_list->at (3)->start ();
}

void MainWindow::set_up_random()
{
    m_simulate_state = true;
    QTimer *t1 = new QTimer();
    connect(t1,SIGNAL(timeout()),this,SLOT(random_of_1()));
    t1->start (2000);
    QTimer *t2 = new QTimer();
    connect(t2,SIGNAL(timeout()),this,SLOT(random_of_2()));
    t2->start (3000);
    QTimer *t3 = new QTimer();
    connect(t3,SIGNAL(timeout()),this,SLOT(random_of_3()));
    t3->start (3500);
    QTimer *t4 = new QTimer();
    connect(t4,SIGNAL(timeout()),this,SLOT(random_of_4()));
    t4->start (2500);

}

void MainWindow::trunSimControlCheckOff()
{
    ui->m_control_button->setCheckState(Qt::CheckState::Unchecked);
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
    for(int i = 0 ; i < items.size() ; ++i){
        Vehicle *v = dynamic_cast<Vehicle *>(items.at(i));
        if(v){
            car.append(v);
        }
    }
    //qDebug()<<car.size();
    for(int i = 0 ; i<car.size() ; ++i){
        if(m_simulate_state){
            car.at(i)->setActionOn();
        }else{
            car.at(i)->setActionOff();
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
}


void MainWindow::random_of_1()
{
    switch (rand()%4){
    case 0:
        m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_E_W));
        break;
    case 1:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,1));
        break;
    case 2:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,2));
        break;
    case 3:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_E_W,3));
        break;
    case 4:
        m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_E_W));
        break;
    }
}

void MainWindow::random_of_2()
{
    switch (rand()%4){
    case 0:
        m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_N_S));
        break;
    case 1:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,1));
        break;
    case 2:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,2));
        break;
    case 3:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_N_S,3));
        break;
    case 4:
        m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_N_S));
        break;
    }
}

void MainWindow::random_of_3()
{
    switch (rand()%4){
    case 0:
        m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_W_E));
        break;
    case 1:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,1));
        break;
    case 2:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,2));
        break;
    case 3:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_W_E,3));
        break;
    case 4:
        m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_W_E));
        break;
    }
}

void MainWindow::random_of_4()
{
    switch (rand()%4){
    case 0:
        m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(REGION_S_N));
        break;
    case 1:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,1));
        break;
    case 2:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,2));
        break;
    case 3:
        m_scene->addItem(VehiclesGenerator::getThroughVehicle(REGION_S_N,3));
        break;
    case 4:
        m_scene->addItem(VehiclesGenerator::getLeftTurningVehicle(REGION_S_N));
        break;
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

}

void MainWindow::on_m_control_button_clicked(bool checked)
{
    if(checked){
        if(!m_simulation_control_widget){
            qDebug()<<"Hello";
            m_simulation_control_widget = new SimulationControl(this);
            m_simulation_control_widget->setWindowTitle(QApplication::translate("toplevel", "Simulation Control"));
            m_simulation_control_widget->setWindowFlags(Qt::Window);
            m_simulation_control_widget->show();
        }else{
            qDebug()<<"Hi";
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

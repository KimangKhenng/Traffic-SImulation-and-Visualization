#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QGraphicsSvgItem>
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),m_road(nullptr),m_simulate_state(false)
{
        ui->setupUi(this);
        setWindowTitle ("Intersection Road Simulation and Visulization");
        m_simulation_control_widget = new SimulationControl();
        m_simulation_control_widget->get_main_windows (this);
        m_loading_screen = new QSplashScreen(QPixmap(":/image/Image/Loading.png"));
        m_data_widget = new DataWidget();
        //m_scene = new QGraphicsScene();
        //ui->graphicsView->Initializer();
        ui->stackedWidget->setCurrentIndex(0);
        m_machine_state = new QTimer();
        m_car_list = new QList<Vehicle *>();
        m_traffic_widget_list = new QList<Traffic_Light_widget *>();
        this->connect (m_machine_state,SIGNAL(timeout()),this,SLOT(check_state()));

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
    if(event->key () == Qt::Key_Enter){
        on_vehicles_clicked ();
    }
    if(event->key () == Qt::Key_R){
        on_road_clicked ();
    }
    qDebug()<<m_traffic_widget_list->at (0)->get_current_state ()->objectName ();
}

QList<Traffic_Light_widget *> *MainWindow::get_traffic_list()
{
    return m_traffic_widget_list;
}

void MainWindow::set_duration_for_1_traffic(int red, int yellow, int green)
{
    m_traffic_widget_list->at (0)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (0)->set_up ();
    //m_traffic_widget_list->at (0)->start ();
}

void MainWindow::set_duration_for_2_traffic(int red, int yellow, int green)
{
    m_traffic_widget_list->at (1)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (1)->set_up ();
    //m_traffic_widget_list->at (1)->start ();
}

void MainWindow::set_duration_for_3_traffic(int red, int yellow, int green)
{
    m_traffic_widget_list->at (2)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (2)->set_up ();
    //m_traffic_widget_list->at (2)->start ();
}

void MainWindow::set_duration_for_4_traffic(int red, int yellow, int green)
{
    m_traffic_widget_list->at (3)->set_duration (red,yellow,green);
    //m_traffic_widget_list->at (3)->set_up ();
    //m_traffic_widget_list->at (3)->start ();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_state()
{
    if(m_simulate_state){
        for(int i = 0 ; i<m_car_list->size ();i++){
            if(!m_car_list->at (i)->is_on_action ()){
            m_car_list->at (i)->get_timer ()->start (10);
            m_car_list->at (i)->set_on_action (true);
            }
        }
    }
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_play_clicked()
{
    qDebug()<<m_car_list->size ();
    if(m_car_list->empty ()){
        return;
    }
    m_simulate_state = true;
    m_machine_state->start (10);

    for(int i = 0 ; i<m_car_list->size ();i++){
        if(!m_car_list->at (i)->is_on_action ()){
        m_car_list->at (i)->get_timer ()->start (10);
        m_car_list->at (i)->set_on_action (true);
        }
    }
}

void MainWindow::on_vehicles_clicked()
{
    if(!m_road){
        return;
    }
    Vehicle *m_car = new Vehicle();
    m_car_list->append (m_car);
    m_car->set_order_in_list (m_car_list->indexOf (m_car));
    m_car->get_list_of_all (m_car_list);
    m_car->extract_coordinate(m_road->get_4_5 ());
    m_car->initialize ();
    m_scene->addItem(m_car);
    m_car->setPos(m_car->get_initial_path());

}

void MainWindow::on_road_clicked()
{
    //m_road->moveBy (15,0);
    //m_road->setPos(m_road->mapToScene(m_scene->sceneRect().x(),m_scene->sceneRect().y()));
}

void MainWindow::on_trafficLight_clicked()
{
    //First Traffic
    m_traffic_widget_1 = new Traffic_Light_widget();
    m_traffic_widget_list->append (m_traffic_widget_1);
    //m_traffic_widget_1->set_duration (300,100,300);
    //m_traffic_widget_1->set_up ();
    //m_traffic_widget_1->start ();
    QGraphicsProxyWidget *m_re_1 = new QGraphicsProxyWidget();
    m_re_1->setWidget (m_traffic_widget_1);
    //m_re_1->setRotation (90);
    m_re_1->setPos (400,140);
    m_scene->addItem (m_re_1);
    //Second Traffic
    m_traffic_widget_2 = new Traffic_Light_widget();
    m_traffic_widget_list->append (m_traffic_widget_2);
    //m_traffic_widget_2->set_duration (300,100,300);
    //m_traffic_widget_2->set_up ();
    //m_traffic_widget_2->start ();
    QGraphicsProxyWidget *m_re_2 = new QGraphicsProxyWidget();
    m_re_2->setWidget (m_traffic_widget_2);
    m_re_2->setRotation (90);
    m_re_2->setPos (260,180);
    m_scene->addItem (m_re_2);
    //Third Traffic
    m_traffic_widget_3 = new Traffic_Light_widget();
    m_traffic_widget_list->append (m_traffic_widget_3);
    //m_traffic_widget_3->set_duration (300,100,300);
    //m_traffic_widget_3->set_up ();
    //m_traffic_widget_3->start ();
    QGraphicsProxyWidget *m_re_3 = new QGraphicsProxyWidget();
    m_re_3->setWidget (m_traffic_widget_3);
    //m_re_3->setRotation (90);
    m_re_3->setPos (220,380);
    m_scene->addItem (m_re_3);
    //Fourth Traffic
    m_traffic_widget_4 = new Traffic_Light_widget();
    m_traffic_widget_list->append (m_traffic_widget_4);
    //m_traffic_widget_4->set_duration (300,100,300);
    //m_traffic_widget_4->set_up ();
    //m_traffic_widget_4->start ();
    QGraphicsProxyWidget *m_re_4 = new QGraphicsProxyWidget();
    m_re_4->setWidget (m_traffic_widget_4);
    m_re_4->setRotation (90);
    m_re_4->setPos (480,380);
    m_scene->addItem (m_re_4);

}

void MainWindow::on_matherials_clicked()
{

}

void MainWindow::on_terrains_clicked()
{

}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_open_simulation_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    set_up ();
}

void MainWindow::on_exit_clicked()
{
    QApplication::quit();
}

void MainWindow::on_reset_clicked()
{
    m_car_list->clear ();
    m_scene->clear();
}

void MainWindow::on_pause_clicked()
{
    m_simulate_state = false;
    for(int i = 0 ; i<m_car_list->size ();i++){
        m_car_list->at (i)->get_timer ()->stop ();
        m_car_list->at (i)->set_on_action (false);
    }
}

void MainWindow::on_stop_clicked()
{
    m_car_list->first ()->get_timer ()->stop ();
}

void MainWindow::set_up()
{

    //Add Road and Background to scene
    QGraphicsPixmapItem *m_picture = new QGraphicsPixmapItem(QPixmap(":/image/Image/road-image.png").scaled (600,600));
    QGraphicsSvgItem *m_terrain = new QGraphicsSvgItem(":/image/Image/terrain.svg");
    QGraphicsSvgItem *m_path = new QGraphicsSvgItem(":/image/Image/road-path.svg");
    m_terrain->moveBy (-60,0);
    m_picture->moveBy(30,0);
    m_path->moveBy (15,-15);
    m_path->setScale (0.7);
    m_path->setZValue (-1);
    m_picture->setZValue (-2);
    m_terrain->setZValue (-3);
    m_scene = new SimulationScene();
    m_road = new road();
    m_scene->addItem (m_picture);
    m_scene->addItem (m_terrain);
    m_scene->addItem (m_path);
    //Add path for vehicle
    m_scene->setSceneRect(0,0,800,600);
    //Add traffic
    on_trafficLight_clicked ();
    //Add Control Widget
    m_control_sim = new QGraphicsProxyWidget();
    m_control_sim->setWidget (m_simulation_control_widget);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsMovable);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsFocusable);
    //m_control_sim->setFlags (QGraphicsItem::ItemIsPanel);
    m_control_sim->setPos (500,0);
    m_scene->addItem (m_control_sim);
    m_data_control = new QGraphicsProxyWidget();
    //m_data_control->setFlags (QGraphicsItem::ItemIsSelectable);
    m_data_control->setWidget (m_data_widget);
    m_scene->addItem (m_data_control);
    m_data_control->setPos (500,400);
    //AddSecen
    ui->graphicsView->setScene(m_scene);
}

void MainWindow::set_up_demo()
{

}


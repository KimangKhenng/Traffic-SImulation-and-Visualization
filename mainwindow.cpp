#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtWidgets>
#include <QGraphicsSvgItem>
MainWindow::MainWindow(QWidget *parent) :QMainWindow(parent),ui(new Ui::MainWindow),m_road(nullptr),m_simulate_state(false)
{
        ui->setupUi(this);
        setWindowTitle ("Intersection Road Simulation and Visulization");
        m_data_widget = new DataWidget();
        //m_scene = new SimulationScene;
        m_scene = new QGraphicsScene();
        m_scene->setSceneRect(0,0,800,600);
        ui->graphicsView->setScene(m_scene);
        //ui->graphicsView->Initializer();
        ui->stackedWidget->setCurrentIndex(0);
        m_machine_state = new QTimer();
        m_car_list = new QList<Vehicle *>();
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
    m_car->extract_coordinate(m_road);
    m_car->initialize ();
    m_scene->addItem(m_car);
    m_car->setPos(m_car->get_initial_path());

}

void MainWindow::on_road_clicked()
{
    m_road = new road(m_scene);
    m_scene->addItem(m_road);
    m_road->moveBy (15,0);
    //m_road->setPos(m_road->mapToScene(m_scene->sceneRect().x(),m_scene->sceneRect().y()));
}

void MainWindow::on_trafficLight_clicked()
{

}

void MainWindow::on_matherials_clicked()
{

}

void MainWindow::on_terrains_clicked()
{
    QGraphicsPixmapItem *m_picture = new QGraphicsPixmapItem(QPixmap(":/image/Image/road-image.png").scaled (600,600));
    QGraphicsSvgItem *m_terrain = new QGraphicsSvgItem(":/image/Image/terrain.svg");
    m_terrain->moveBy (-100,0);
    m_picture->setZValue (-1);
    m_terrain->setZValue (-2);
    m_scene->addItem (m_picture);
    m_scene->addItem (m_terrain);
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

void MainWindow::on_data_clicked()
{
    m_data_widget->show();
}

void MainWindow::on_stop_clicked()
{
    m_car_list->first ()->get_timer ()->stop ();
}

void MainWindow::on_m_control_clicked()
{

}

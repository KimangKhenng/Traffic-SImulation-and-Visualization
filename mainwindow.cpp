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
        m_car_list_1 = new QList<Vehicle *>();
        m_car_list_2 = new QList<Vehicle *>();
        m_car_list_3 = new QList<Vehicle *>();
        m_car_list_4 = new QList<Vehicle *>();
        m_car_list_5 = new QList<Vehicle *>();
        m_car_list_6 = new QList<Vehicle *>();
        m_car_list_7 = new QList<Vehicle *>();
        m_car_list_8 = new QList<Vehicle *>();
        m_car_list_9 = new QList<Vehicle *>();
        m_car_list_10 = new QList<Vehicle *>();
        m_car_list_11 = new QList<Vehicle *>();
        m_car_list_12 = new QList<Vehicle *>();
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
    //qDebug()<<m_traffic_widget_list->at (0)->get_current_state ()->objectName ();
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

void MainWindow::set_up_random()
{
    m_simulate_state = true;
    m_machine_state->start (10);
    QTimer *t1 = new QTimer();
    connect(t1,SIGNAL(timeout()),this,SLOT(random_of_1()));
    t1->start (3000);
    QTimer *t2 = new QTimer();
    connect(t2,SIGNAL(timeout()),this,SLOT(random_of_2()));
    t2->start (3000);
    QTimer *t3 = new QTimer();
    connect(t3,SIGNAL(timeout()),this,SLOT(random_of_3()));
    t3->start (3000);
    QTimer *t4 = new QTimer();
    connect(t4,SIGNAL(timeout()),this,SLOT(random_of_4()));
    t4->start (3000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::check_state()
{
    // List 1
    for(int i = 0 ; i<m_car_list_1->size ();i++){
        if(m_car_list_1->at (i)->get_current_index () >= 100){
            if(m_car_list_1->at (i)->get_back_vehicle () == nullptr){
                //m_car_list_1->removeAt (i);
                //delete m_car_list_1->at (i);
                m_car_list_1->clear ();
                return;
            }
            m_car_list_1->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_1->at (i));
            m_car_list_1->removeAt (i);
            //delete m_car_list_1->at (i);
        }
    }
    // List 2
    for(int i = 0 ; i<m_car_list_2->size ();i++){
        if(m_car_list_2->at (i)->get_current_index () >= 100){
            if(m_car_list_2->at (i)->get_back_vehicle () == nullptr){
                m_car_list_2->clear ();
                return;
            }
            m_car_list_2->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_2->at (i));
            m_car_list_2->removeAt (i);
            //delete m_car_list_2->at (i);
        }
    }
    // List 3
    for(int i = 0 ; i<m_car_list_3->size ();i++){
        if(m_car_list_3->at (i)->get_current_index () >= 100){
            if(m_car_list_3->at (i)->get_back_vehicle () == nullptr){
                m_car_list_3->clear ();
                return;
            }
            m_car_list_3->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_3->at (i));
            m_car_list_3->removeAt (i);
            //delete m_car_list_3->at (i);
        }
    }
    //List 4
    for(int i = 0 ; i<m_car_list_4->size ();i++){
        if(m_car_list_4->at (i)->get_current_index () >= 100){
            if(m_car_list_4->at (i)->get_back_vehicle () == nullptr){
                m_car_list_4->clear ();
                return;
            }
            m_car_list_4->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_4->at (i));
            m_car_list_4->removeAt (i);
            //delete m_car_list_4->at (i);
        }
    }
    //List 5
    for(int i = 0 ; i<m_car_list_5->size ();i++){
        if(m_car_list_5->at (i)->get_current_index () >= 100){
            if(m_car_list_5->at (i)->get_back_vehicle () == nullptr){
                m_car_list_5->clear ();
                return;
            }
            m_car_list_5->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_5->at (i));
            m_car_list_5->removeAt (i);
            //delete m_car_list_5->at (i);
        }
    }
    //List 6
    for(int i = 0 ; i<m_car_list_6->size ();i++){
        if(m_car_list_6->at (i)->get_current_index () >= 100){
            if(m_car_list_6->at (i)->get_back_vehicle () == nullptr){
                m_car_list_6->clear ();
                return;
            }
            m_car_list_6->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_6->at (i));
            m_car_list_6->removeAt (i);
            //delete m_car_list_6->at (i);
        }
    }
    //List 7
    for(int i = 0 ; i<m_car_list_7->size ();i++){
        if(m_car_list_7->at (i)->get_current_index () >= 100){
            if(m_car_list_7->at (i)->get_back_vehicle () == nullptr){
                m_car_list_7->clear ();
                return;
            }
            m_car_list_7->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_7->at (i));
            m_car_list_7->removeAt (i);
            //delete m_car_list_7->at (i);
        }
    }
    //List 8
    for(int i = 0 ; i<m_car_list_8->size ();i++){
        if(m_car_list_8->at (i)->get_current_index () >= 100){
            if(m_car_list_8->at (i)->get_back_vehicle () == nullptr){
                m_car_list_8->clear ();
                return;
            }
            m_car_list_8->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_8->at (i));
            m_car_list_8->removeAt (i);
            //delete m_car_list_8->at (i);
        }
    }
    //List 9
    for(int i = 0 ; i<m_car_list_9->size ();i++){
        if(m_car_list_9->at (i)->get_current_index () >= 100){
            if(m_car_list_9->at (i)->get_back_vehicle () == nullptr){
                m_car_list_9->clear ();m_car_list_3->clear ();
                return;
            }
            m_car_list_9->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_9->at (i));
            m_car_list_9->removeAt (i);
            //delete m_car_list_9->at (i);
        }
    }
    //List 10
    for(int i = 0 ; i<m_car_list_10->size ();i++){
        if(m_car_list_10->at (i)->get_current_index () >= 100){
            if(m_car_list_10->at (i)->get_back_vehicle () == nullptr){
                m_car_list_10->clear ();
                return;
            }
            m_car_list_10->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_10->at (i));
            m_car_list_10->removeAt (i);
            //delete m_car_list_10->at (i);
        }
    }
    //List 11
    for(int i = 0 ; i<m_car_list_11->size ();i++){
        if(m_car_list_11->at (i)->get_current_index () >= 100){
            if(m_car_list_11->at (i)->get_back_vehicle () == nullptr){
                m_car_list_11->clear ();
                return;
            }
            m_car_list_11->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_11->at (i));
            m_car_list_11->removeAt (i);
            //delete m_car_list_11->at (i);
        }
    }
    //List 12
    for(int i = 0 ; i<m_car_list_12->size ();i++){
        if(m_car_list_12->at (i)->get_current_index () >= 100){
            if(m_car_list_12->at (i)->get_back_vehicle () == nullptr){
                m_car_list_12->clear ();
                return;
            }
            m_car_list_12->at (i)->get_back_vehicle ()->remove_next ();
            m_scene->removeItem (m_car_list_12->at (i));
            m_car_list_12->removeAt (i);
            //delete m_car_list_12->at (i);
        }
    }
    if(m_simulate_state){
        for(int i = 0 ; i<m_car_list_1->size ();i++){
            if(!m_car_list_1->at (i)->is_on_action ()){
            m_car_list_1->at (i)->get_timer ()->start (10);
            m_car_list_1->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_2->size ();i++){
            if(!m_car_list_2->at (i)->is_on_action ()){
            m_car_list_2->at (i)->get_timer ()->start (10);
            m_car_list_2->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_3->size ();i++){
            if(!m_car_list_3->at (i)->is_on_action ()){
            m_car_list_3->at (i)->get_timer ()->start (10);
            m_car_list_3->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_4->size ();i++){
            if(!m_car_list_4->at (i)->is_on_action ()){
            m_car_list_4->at (i)->get_timer ()->start (10);
            m_car_list_4->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_5->size ();i++){
            if(!m_car_list_5->at (i)->is_on_action ()){
            m_car_list_5->at (i)->get_timer ()->start (10);
            m_car_list_5->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_6->size ();i++){
            if(!m_car_list_6->at (i)->is_on_action ()){
            m_car_list_6->at (i)->get_timer ()->start (10);
            m_car_list_6->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_7->size ();i++){
            if(!m_car_list_7->at (i)->is_on_action ()){
            m_car_list_7->at (i)->get_timer ()->start (10);
            m_car_list_7->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_8->size ();i++){
            if(!m_car_list_8->at (i)->is_on_action ()){
            m_car_list_8->at (i)->get_timer ()->start (10);
            m_car_list_8->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_9->size ();i++){
            if(!m_car_list_9->at (i)->is_on_action ()){
            m_car_list_9->at (i)->get_timer ()->start (10);
            m_car_list_9->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_10->size ();i++){
            if(!m_car_list_10->at (i)->is_on_action ()){
            m_car_list_10->at (i)->get_timer ()->start (10);
            m_car_list_10->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_11->size ();i++){
            if(!m_car_list_11->at (i)->is_on_action ()){
            m_car_list_11->at (i)->get_timer ()->start (10);
            m_car_list_11->at (i)->set_on_action (true);
            }
        }
        for(int i = 0 ; i<m_car_list_12->size ();i++){
            if(!m_car_list_12->at (i)->is_on_action ()){
            m_car_list_12->at (i)->get_timer ()->start (10);
            m_car_list_12->at (i)->set_on_action (true);
            }
        }
        }
}


void MainWindow::random_of_1()
{
    Vehicle *m_car = new Vehicle();
    switch (qrand()%3){
    case 0:
        m_car_list_1->append (m_car);
        m_car->get_list_of_all (m_car_list_1);
        m_car->extract_coordinate(m_road->get_1_1 ());
        m_car->initialize (m_traffic_widget_1);
        m_scene->addItem(m_car_list_1->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 1:
        m_car_list_2->append (m_car);
        m_car->get_list_of_all (m_car_list_2);
        m_car->extract_coordinate(m_road->get_1_3 ());
        m_car->initialize (m_traffic_widget_1);
        m_scene->addItem(m_car_list_2->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 2:
        m_car_list_3->append (m_car);
        m_car->get_list_of_all (m_car_list_3);
        m_car->extract_coordinate(m_road->get_1_5 ());
        m_car->initialize (m_traffic_widget_1);
        m_scene->addItem(m_car_list_3->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    }
    if(m_car_list_1->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_1->size ();i++){
        if(!m_car_list_1->at (i)->is_on_action ()){
        m_car_list_1->at (i)->get_timer ()->start (10);
        m_car_list_1->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_2->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_2->size ();i++){
        if(!m_car_list_2->at (i)->is_on_action ()){
        m_car_list_2->at (i)->get_timer ()->start (10);
        m_car_list_2->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_3->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_3->size ();i++){
        if(!m_car_list_3->at (i)->is_on_action ()){
        m_car_list_3->at (i)->get_timer ()->start (10);
        m_car_list_3->at (i)->set_on_action (true);
        }
    }
}

void MainWindow::random_of_2()
{
    Vehicle *m_car = new Vehicle();
    switch (qrand()%3){
    case 0:
        m_car_list_4->append (m_car);
        m_car->get_list_of_all (m_car_list_4);
        m_car->extract_coordinate(m_road->get_2_1 ());
        m_car->initialize (m_traffic_widget_2);
        m_scene->addItem(m_car_list_4->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 1:
        m_car_list_5->append (m_car);
        m_car->get_list_of_all (m_car_list_5);
        m_car->extract_coordinate(m_road->get_2_3 ());
        m_car->initialize (m_traffic_widget_2);
        m_scene->addItem(m_car_list_5->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 2:
        m_car_list_6->append (m_car);
        m_car->get_list_of_all (m_car_list_6);
        m_car->extract_coordinate(m_road->get_2_5 ());
        m_car->initialize (m_traffic_widget_2);
        m_scene->addItem(m_car_list_6->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    }
    if(m_car_list_4->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_4->size ();i++){
        if(!m_car_list_4->at (i)->is_on_action ()){
        m_car_list_4->at (i)->get_timer ()->start (10);
        m_car_list_4->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_5->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_5->size ();i++){
        if(!m_car_list_5->at (i)->is_on_action ()){
        m_car_list_5->at (i)->get_timer ()->start (10);
        m_car_list_5->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_6->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_6->size ();i++){
        if(!m_car_list_6->at (i)->is_on_action ()){
        m_car_list_6->at (i)->get_timer ()->start (10);
        m_car_list_6->at (i)->set_on_action (true);
        }
    }
}

void MainWindow::random_of_3()
{
     Vehicle *m_car = new Vehicle();
    switch (qrand()%3){
    case 0:
        m_car_list_7->append (m_car);
        m_car->get_list_of_all (m_car_list_7);
        m_car->extract_coordinate(m_road->get_3_1 ());
        m_car->initialize (m_traffic_widget_3);
        m_scene->addItem(m_car_list_7->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 1:
        m_car_list_8->append (m_car);
        m_car->get_list_of_all (m_car_list_8);
        m_car->extract_coordinate(m_road->get_3_3 ());
        m_car->initialize (m_traffic_widget_3);
        m_scene->addItem(m_car_list_8->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 2:
        m_car_list_9->append (m_car);
        m_car->get_list_of_all (m_car_list_9);
        m_car->extract_coordinate(m_road->get_3_5 ());
        m_car->initialize (m_traffic_widget_3);
        m_scene->addItem(m_car_list_9->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    }
    if(m_car_list_7->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_7->size ();i++){
        if(!m_car_list_7->at (i)->is_on_action ()){
        m_car_list_7->at (i)->get_timer ()->start (10);
        m_car_list_7->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_8->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_8->size ();i++){
        if(!m_car_list_8->at (i)->is_on_action ()){
        m_car_list_8->at (i)->get_timer ()->start (10);
        m_car_list_8->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_9->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_9->size ();i++){
        if(!m_car_list_9->at (i)->is_on_action ()){
        m_car_list_9->at (i)->get_timer ()->start (10);
        m_car_list_9->at (i)->set_on_action (true);
        }
    }
}

void MainWindow::random_of_4()
{
    Vehicle *m_car = new Vehicle();
    switch (qrand()%3){
    case 0:
        m_car_list_10->append (m_car);
        m_car->get_list_of_all (m_car_list_10);
        m_car->extract_coordinate(m_road->get_4_1 ());
        m_car->initialize (m_traffic_widget_4);
        m_scene->addItem(m_car_list_10->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 1:
        m_car_list_11->append (m_car);
        m_car->get_list_of_all (m_car_list_11);
        m_car->extract_coordinate(m_road->get_4_3 ());
        m_car->initialize (m_traffic_widget_4);
        m_scene->addItem(m_car_list_11->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    case 2:
        m_car_list_12->append (m_car);
        m_car->get_list_of_all (m_car_list_12);
        m_car->extract_coordinate(m_road->get_4_5 ());
        m_car->initialize (m_traffic_widget_4);
        m_scene->addItem(m_car_list_12->last ());
        m_car->setPos(m_car->get_initial_path());
        break;
    }
    if(m_car_list_10->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_10->size ();i++){
        if(!m_car_list_10->at (i)->is_on_action ()){
        m_car_list_10->at (i)->get_timer ()->start (10);
        m_car_list_10->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_11->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_11->size ();i++){
        if(!m_car_list_11->at (i)->is_on_action ()){
        m_car_list_11->at (i)->get_timer ()->start (10);
        m_car_list_11->at (i)->set_on_action (true);
        }
    }
    if(m_car_list_12->empty ()){
        return;
    }
    for(int i = 0 ; i<m_car_list_12->size ();i++){
        if(!m_car_list_12->at (i)->is_on_action ()){
        m_car_list_12->at (i)->get_timer ()->start (10);
        m_car_list_12->at (i)->set_on_action (true);
        }
    }
}
void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_play_clicked()
{
    qDebug()<<m_car_list_1->size ();
    if(m_car_list_1->empty ()){
        return;
    }
    m_simulate_state = true;
    m_machine_state->start (10);

    for(int i = 0 ; i<m_car_list_1->size ();i++){
        if(!m_car_list_1->at (i)->is_on_action ()){
        m_car_list_1->at (i)->get_timer ()->start (10);
        m_car_list_1->at (i)->set_on_action (true);
        }
    }
}

void MainWindow::on_vehicles_clicked()
{

    Vehicle *m_car = new Vehicle();
    m_car_list_1->append (m_car);
    //m_car->set_order_in_list (m_car_list_1->indexOf (m_car));
    m_car->get_list_of_all (m_car_list_1);
    m_car->extract_coordinate(m_road->get_1_1 ());
    m_car->initialize (m_traffic_widget_1);
    m_scene->addItem(m_car_list_1->last ());
    m_car->setPos(m_car->get_initial_path());

}

void MainWindow::on_road_clicked()
{
    m_scene->addPath (m_road->get_1_1 ());
    //qDebug()<<QGraphicsPathItem(m_road->get_4_1 ()).boundingRect ();
}

void MainWindow::on_trafficLight_clicked()
{
    //First Traffic
    m_traffic_widget_1 = new Traffic_Light_widget();
    m_traffic_widget_list->append (m_traffic_widget_1);
    m_traffic_widget_1->get_other_widget (m_traffic_widget_list);
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
    m_traffic_widget_2->get_other_widget (m_traffic_widget_list);
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
    m_traffic_widget_3->get_other_widget (m_traffic_widget_list);
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
    m_traffic_widget_4->get_other_widget (m_traffic_widget_list);
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
    m_car_list_1->clear ();
    m_scene->clear();
}

void MainWindow::on_pause_clicked()
{
    m_simulate_state = false;
    for(int i = 0 ; i<m_car_list_1->size ();i++){
        m_car_list_1->at (i)->get_timer ()->stop ();
        m_car_list_1->at (i)->set_on_action (false);
    }
}

void MainWindow::on_stop_clicked()
{
    m_car_list_1->first ()->get_timer ()->stop ();
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
    m_scene->addText ("1",QFont("Century",18))->setPos (450,180);
    m_scene->addText ("2",QFont("Century",18))->setPos (150,180);
    m_scene->addText ("3",QFont("Century",18))->setPos (180,380);
    m_scene->addText ("4",QFont("Century",18))->setPos (400,420);
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

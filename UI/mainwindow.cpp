#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "UI/simulationcontrolwidget.h"

MainWindow::MainWindow(QWidget *parent)
    :QMainWindow(parent)
    ,ui(new Ui::MainWindow)
    ,m_simulate_state(false)
    ,m_sightseeing(false)
    ,m_visualize_state(false)
{
        ui->setupUi(this);
        setWindowTitle ("Intersection Road Simulation and Visulization");
        setWindowIcon(QIcon(":/icon/Image/Logo-AI.png"));
        set_up ();
        ui->stackedWidget->setCurrentIndex(0);
        m_machine_state = new QTimer();
        this->connect(m_machine_state,SIGNAL(timeout()),this,SLOT(check_state()));
        //QObject::connect(m_machine_state,SIGNAL(timeout()),m_scene,SLOT(advance()));
        m_machine_state->start(TIME_UNIT);
        ui->m_visualize_frame->hide();
        ui->m_visualzie_widget->setController(m_scene->getController());
        //ui->m_visualzie_widget->setEtimer(m_controller->getTimer());
        //ui->m_visualzie_widget->setMainWindows(this);
        //ui->m_visualzie_widget->initialize();
        //qDebug()<<"Passed";
        SimulationControlWidget *control = new SimulationControlWidget;
        control->show();
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

GENMETHOD MainWindow::getCurrentMethod() const
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

VEHICLEMETHOD MainWindow::getCurrentVehicleMethod() const
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
    //QList<QGraphicsItem *> items = m_scene->items();
    if(m_simulate_state){

        m_scene->advance();

        QList<Vehicle *> car = m_scene->getVehicle();
        //QList<TrafficDetector *> detector = m_scene->getDetector();
        for(int i = 0; i<car.size() ; ++i){
            //car.at(i)->turnOnEngine();
            if(this->m_sightseeing){
                car.at(i)->turnOnSightSeeing();
            }else{
                car.at(i)->turnOffSightSeeing();
            }
            if(car.at(i)->isDeletable()){
                //m_scene->removeItem(car.at(i));
                m_scene->removeVehicle(car.at(i));
//                m_scene->removeItem(car.at(i));
//                delete car.at(i);
            }
        }
        //m_controller->startTrafficLightAll();
    if(m_visualize_state){
       //double t1 = omp_get_wtime();
       ui->m_visualzie_widget->update_all();
       //double t2 = omp_get_wtime();
       //qDebug()<<"CTim"<<t2-t1;
    }
    }else{
        //m_scene->trunOffAllCar();
        ui->m_simulation_control_widget->generator()->stopGenerator();
    }

//    for(int i = 0 ; i < items.size() ; ++i){
//        Vehicle *v = dynamic_cast<Vehicle *>(items.at(i));
//        TrafficDetector *d = dynamic_cast<TrafficDetector *>(items.at(i));
//        if(v){
//            car.append(v);
//        }
//        if(d){
//            detector.append(d);
//        }
//    }
    //qDebug()<<car.size();
    //WorkerThread *thread = new WorkerThread(ui->m_visualzie_widget,this);
    //connect(thread, &WorkerThread::finished, thread, &QObject::deleteLater);
    //thread->start();

//    for(int i = 0 ; i < detector.size() ; ++i){
//        if(m_simulate_state){
//            //car.at(i)->setActionOn();
//            detector.at(i)->startEngine();
//        }else{
//            //car.at(i)->setActionOff();
//            detector.at(i)->stopEngine();
//        }
//    }
    //qDebug()<<"Number"<<m_scene->getVehicle().length();
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
//    ui->m_simulation_control_widget->generator()->stopGenerator();
//    this->turnOffSimulationState();
//    for(int i = 0 ; i < m_scene->getVehicle().length() ; i++){
//        delete m_scene->getVehicle().at(i);
//    }
    ui->m_simulation_control_widget->stopGenerating();
    ui->tool_panel->setEnabled(false);
    ui->tool_panel->update();

    m_simulate_state = false;
    m_visualize_state = false;
    m_scene->getController()->stopTrafficLightAll();
    m_scene->resetScene();

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

    //m_scene->addText ("1",QFont("Century",18))->setPos (450,180);
    //m_scene->addText ("2",QFont("Century",18))->setPos (150,180);
    //m_scene->addText ("3",QFont("Century",18))->setPos (180,380);
    //m_scene->addText ("4",QFont("Century",18))->setPos (400,420);
    //Add path for vehicle
    m_scene->setSceneRect(0,0,800,600);
//    m_traffic_light = new QList<TrafficLight *>();
//    for(int i = 0 ; i < 4 ; ++i){
//        m_traffic_light->append(new TrafficLight());
//        m_traffic_light->at(i)->setUpFacilities();
//    }
//    m_controller->setTraffic_light(m_traffic_light);
//    //Arrange Traffic Light
//    //TrafficLight 1
//    m_traffic_light->at(0)->setPos(400,380);
//    m_traffic_light->at(0)->setRegion(region::REGION_S_N);
//    //TrafficLight 2
//    m_traffic_light->at(1)->setRotation(90);
//    m_traffic_light->at(1)->setPos(260,380);
//    m_traffic_light->at(1)->setRegion(region::REGION_W_E);
//    //TrafficLight 3
//    m_traffic_light->at(2)->setPos(250,240);
//    m_traffic_light->at(2)->setRotation(180);
//    m_traffic_light->at(2)->setRegion(region::REGION_N_S);
//    m_traffic_light->at(2)->setTransform(QTransform::fromScale(1, -1));
//    //TrafficLight 4
//    m_traffic_light->at(3)->setPos(410,230);
//    m_traffic_light->at(3)->setRotation(270);
//    m_traffic_light->at(3)->setRegion(region::REGION_E_W);
//    //m_traffic_light->at(3)->setTransform(QTransform::fromScale(-1, 1));
//    for(int i = 0 ; i < m_traffic_light->size() ; ++i){
//        for(int j = 0 ; j < m_traffic_light->at(i)->getLight()->size() ; j++){
//            m_traffic_light->at(i)->getLight()->at(j)->setScale(0.8);
//        }
//    }
    //Add Control Widget
//    m_control_sim = new QGraphicsProxyWidget();
//    m_control_sim->setWidget (ui->m_simulation_control_widget);
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
    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
//    ui->graphicsView->Initializer();
    //ui->m_simulation_control_widget = new SimulationControl(this);
    ui->m_simulation_control_widget->initialize(this);
}

void MainWindow::set_up_demo()
{


}
void MainWindow::on_m_road_check_button_toggled(bool checked)
{

}

void MainWindow::on_m_detector_button_clicked(bool checked)
{
    if(checked){
        m_scene->getController()->turnOnDetector();
    }else{
        m_scene->getController()->turnOffDetector();
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





void MainWindow::on_m_aboutus_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}


void MainWindow::on_m_manul_control_button_clicked(bool checked)
{
    if(checked){

        m_scene->getController()->manualControl();

    }else{

        m_scene->getController()->startTrafficLightAll();

    }
}

void MainWindow::on_m_5_lanes_clicked()
{
    ui->m_simulation_control_widget->setMethod(GENMETHOD::GEN_5);
}

void MainWindow::on_m_3_lanes_clicked()
{
    ui->m_simulation_control_widget->setMethod(GENMETHOD::GEN_3);
}

SimulationScene *MainWindow::scene() const
{
    return m_scene;
}

void MainWindow::on_m_no_traffic_clicked(bool checked)
{
    showTraffic(checked);
}

bool MainWindow::getSimulate_state() const
{
    return m_simulate_state;
}

void MainWindow::showTraffic(bool checked)
{
    if(checked){
        m_scene->showTrafficLight();
    }else{
        m_scene->HideTrafficLight();
    }
}

void MainWindow::set3LaneCheck(const bool &b)
{
    ui->m_3_lanes->setChecked(b);
}

void MainWindow::setGenMethod(const GENMETHOD &gen)
{
    ui->m_simulation_control_widget->generator()->setMethod(gen);
}

void MainWindow::setGoThroguht(const bool &b)
{
    ui->m_go_though->setChecked(b);
}

void MainWindow::setSimMode(const VEHICLEMETHOD &m)
{
    ui->m_simulation_control_widget->generator()->setMode(m);
}

void MainWindow::setTrafficState(const bool &b)
{
    ui->m_no_traffic->setChecked(b);
}

TrafficController *MainWindow::getController() const
{
    return m_scene->getController();
}

void MainWindow::on_m_no_turn_clicked()
{
    ui->m_simulation_control_widget->generator()->setMethod(GENMETHOD::NO_TURN);
}


void MainWindow::on_m_go_though_clicked(bool checked)
{
    if(checked){
        ui->m_simulation_control_widget->generator()->setMode(VEHICLEMETHOD::GO_THROUGH);
        m_scene->setGoThrough(true);
    }else{
        ui->m_simulation_control_widget->generator()->setMode(VEHICLEMETHOD::SIGHTSEEING);
        m_scene->setGoThrough(false);
    }

}
void MainWindow::on_m_drop_in_clicked()
{
//    m_scene->addItem(VehiclesGenerator::getRightTurningVehicle(region::REGION_E_W,VEHICLEMETHOD::SIGHTSEEING));
//    m_scene->getVehicle().at(0)->turnOnEngine();
//    this->turnOnSimulationState();
}

void MainWindow::on_actionPNG_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this,
           tr("Export PNG file"), "",
           tr("Portable Network Graphics (*.png);;All Files (*)"));
    if (fileName.isEmpty())
            return;
        else {
            QPixmap pixmap = QWidget::grab(ui->graphicsView->viewport()->rect());
            QPainter printer(&pixmap);
            printer.setRenderHint(QPainter::Antialiasing);
            ui->graphicsView->render(&printer,pixmap.rect(),ui->graphicsView->viewport()->rect(),Qt::KeepAspectRatio);
            printer.end();
            pixmap.save(fileName);
        }

}





void MainWindow::on_m_tool_panel_check_box_clicked(bool checked)
{
    if(checked){
        ui->m_tool_panel_frame->show();
    }else{
        ui->m_tool_panel_frame->hide();
    }
}

void MainWindow::on_m_visualize_panel_check_box_clicked(bool checked)
{
    if(checked){
        ui->m_visualize_frame->show();
        m_visualize_state = true;
    }else{
        ui->m_visualize_frame->hide();
        m_visualize_state = false;
    }
}

void MainWindow::on_m_back_button_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_m_only_turn_clicked()
{
    ui->m_simulation_control_widget->generator()->setMethod(GENMETHOD::ONLY_TURN);
}

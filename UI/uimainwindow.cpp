#include "uimainwindow.h"
#include "ui_uimainwindow.h"

UIMainWindow::UIMainWindow(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::UIMainWindow)
    ,m_time_frame(0)
{
    ui->setupUi(this);

    ui->graphicsView->setResizeAnchor(QGraphicsView::AnchorViewCenter);
    ui->graphicsView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);



    m_Simulation = new RoadIntersectionSimulation(ui->graphicsView);

    connect(m_Simulation,&RoadIntersectionSimulation::updatedOneFrame,
            this,&UIMainWindow::updateStatus);
    //m_Simulation->initialize(ui->graphicsView);

    m_Demo = new RoadIntersectionSimulation(ui->m_demo_widget_1);
    m_Demo->initialize();
    m_Demo->startDemo();

    m_intro_page = new IntroPage(ui->m_first_page);

    //m_intro_page->AutoUpdate(true);

    connect(m_Demo,&RoadIntersectionSimulation::updatedOneFrame,
            m_intro_page,&IntroPage::repaintWidget);

    connect(m_intro_page,&IntroPage::PlayClicked,
            this,&UIMainWindow::onPlayButtonClicked);
    connect(m_intro_page,&IntroPage::AboutClicked,
            this,&UIMainWindow::onAboutButtonClicked);
    connect(m_intro_page,&IntroPage::HelpClicked,
            this,&UIMainWindow::onHelpButtonClicked);
    connect(m_intro_page,&IntroPage::ExitClicked,
            this,&UIMainWindow::onExitButtonClicked);

    m_setup = new SimulationSetup;

    connect(m_setup,&SimulationSetup::inputReady,
            m_Simulation,&RoadIntersectionSimulation::initializeFrominput);
    connect(m_setup,&SimulationSetup::onRandomClicked,
            m_Simulation,&RoadIntersectionSimulation::initializeFrominput);
    connect(m_setup,&SimulationSetup::onHelpClicked,
            this,&UIMainWindow::onHelpButtonClicked);

//    ui->m_visualize_panel->setController(m_Simulation->Scene()->getController());
//    connect(m_Simulation,&RoadIntersectionSimulation::updatedOneFrame,
//            ui->m_visualize_panel,&VisualizePanel::update_all);


}

UIMainWindow::~UIMainWindow()
{
    delete ui;
    delete m_Simulation;
    delete m_Demo;
    delete m_intro_page;
}

void UIMainWindow::onExitButtonClicked()
{
    QApplication::exit();
}

void UIMainWindow::onAboutButtonClicked()
{
    ui->m_stacked_widget->setCurrentIndex(1);
    m_Demo->pauseSimulation();
}

void UIMainWindow::onPlayButtonClicked()
{
    ui->m_stacked_widget->setCurrentIndex(4);
    m_Demo->pauseSimulation();
    if(m_Simulation->State() == SimulationState::UNINITIALIZED){

        //EnableSimulationButton(false,false,false,false);
        //ui->m_simulation_page->setEnabled(false);
        m_setup->show();
    }
}

void UIMainWindow::onHelpButtonClicked()
{
    ui->m_stacked_widget->setCurrentIndex(2);
    m_Demo->pauseSimulation();
    ui->help_widget->startDemo();
}

void UIMainWindow::EnableSimulationButton(const bool &play,
                                          const bool &pause,
                                          const bool &stop,
                                          const bool &restart)
{
    ui->m_simulation_play_button->setEnabled(play);
    ui->m_simulation_pause_button->setEnabled(pause);
    ui->m_simulation_restart_button->setEnabled(restart);
    ui->m_simulation_stop_button->setEnabled(stop);
}

void UIMainWindow::updateStatus()
{
    m_time_frame++;

}


void UIMainWindow::on_m_about_back_button_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
    m_Demo->startSimulation();
}

void UIMainWindow::on_m_help_back_button_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
    ui->help_widget->stopDemo();
    m_Demo->startSimulation();
}

void UIMainWindow::on_m_simulation_back_icon_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
    m_Simulation->pauseSimulation();
    m_Demo->startSimulation();
}

void UIMainWindow::on_m_setting_back_icon_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
}

void UIMainWindow::on_m_simulation_play_button_clicked()
{    
    m_Simulation->startSimulation();
    ui->m_simulation_play_button->setEnabled(false);
    ui->m_simulation_pause_button->setEnabled(true);
}

void UIMainWindow::on_m_simulation_pause_button_clicked()
{
    m_Simulation->pauseSimulation();
    ui->m_simulation_play_button->setEnabled(true);
    ui->m_simulation_pause_button->setEnabled(false);
}

void UIMainWindow::on_m_simulation_restart_button_clicked()
{
    m_Simulation->stopSimulation();
    m_setup->show();
}

void UIMainWindow::on_m_simulation_stop_button_clicked()
{

    m_Simulation->stopSimulation();
}

void UIMainWindow::on_show_road_check_box_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        m_Simulation->showRoad();
    }else if(arg1 == Qt::Unchecked){
        m_Simulation->hideRoad();
    }
}

void UIMainWindow::on_show_detectors_check_box_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        m_Simulation->showDetectors();
    }else if(arg1 == Qt::Unchecked){
        m_Simulation->hideDetectors();
    }
}

void UIMainWindow::on_show_vehicles_vision_check_box_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        m_Simulation->showVehiclesVision();
    }else if(arg1 == Qt::Unchecked){
        m_Simulation->hideVehiclesVision();
    }
}

void UIMainWindow::on_show_traffic_light_check_box_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        m_Simulation->showTraffic();
    }else if(arg1 == Qt::Unchecked){
        m_Simulation->hideTraffic();
    }
}

void UIMainWindow::on_m_3_lanes_button_clicked()
{
    m_Simulation->setGenerationMethod(GENMETHOD::GEN_3);
}

void UIMainWindow::on_m_5_lanes_button_clicked()
{
    m_Simulation->setGenerationMethod(GENMETHOD::GEN_5);
}

void UIMainWindow::on_m_no_turn_button_clicked()
{
    m_Simulation->setGenerationMethod(GENMETHOD::NO_TURN);
}

void UIMainWindow::on_m_turn_only_button_clicked()
{
    m_Simulation->setGenerationMethod(GENMETHOD::ONLY_TURN);
}

void UIMainWindow::on_m_go_through_check_box_stateChanged(int arg1)
{
    if(arg1 == Qt::Checked){
        m_Simulation->turnOnGoThrough();
    }else if(arg1 == Qt::Unchecked){
        m_Simulation->turnOffGoThrough();
    }
}

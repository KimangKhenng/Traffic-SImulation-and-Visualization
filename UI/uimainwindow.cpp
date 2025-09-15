#include "uimainwindow.h"
#include "ui_uimainwindow.h"
#include <QDebug>
#include <QSplitter>
#include <QGraphicsView>

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

    // m_intro_page->AutoUpdate(true);

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
            this,&UIMainWindow::onSimulationInitialized);
    connect(m_setup,&SimulationSetup::onRandomClicked,
            this,&UIMainWindow::onSimulationInitialized);
    connect(m_setup,&SimulationSetup::onHelpClicked,
            this,&UIMainWindow::onHelpButtonClicked);

    // Create and setup metrics widget
    // m_metricsWidget = new MetricsWidget(ui->m_visualize_panel);
    // m_metricsWidget->setMetricsSource(m_Simulation->getMetrics());
    // m_metricsWidget->setMetricsVisible(false); // Hidden by default
    
    // Position the metrics widget (you might want to adjust this based on your UI layout)
    // m_metricsWidget->move(10, 10);
    // m_metricsWidget->setParent(ui->m_simulation_page);

   ui->m_visualize_panel->setController(m_Simulation->Scene()->getController());
   connect(m_Simulation,&RoadIntersectionSimulation::updatedOneFrame,
           ui->m_visualize_panel,&VisualizePanel::update_all);

   // Make visualize panel resizable using a better approach
   setupResizableVisualizePanelSplitter();


}

UIMainWindow::~UIMainWindow()
{
    delete ui;
    delete m_Simulation;
    delete m_Demo;
    delete m_intro_page;
    // m_metricsWidget will be deleted automatically by Qt parent-child relationship
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
    // Note: UI elements m_time_display and m_vehicles_number were removed from the UI
    // The metrics are now displayed in the separate MetricsWidget
    // If these displays are needed, they should be added back to the UI file
}

void UIMainWindow::updateButtonStates()
{
    if (!m_Simulation) return;
    
    SimulationState state = m_Simulation->State();
    
    // Update button states based on current simulation state
    ui->m_simulation_play_button->setEnabled(m_Simulation->canStart());
    ui->m_simulation_pause_button->setEnabled(m_Simulation->canPause());
    ui->m_simulation_stop_button->setEnabled(m_Simulation->canStop());
    ui->m_simulation_restart_button->setEnabled(state != SimulationState::UNINITIALIZED);
    
    qDebug() << "Button states updated for simulation state:" << state;
}

void UIMainWindow::onSimulationInitialized(SimulationInput input)
{
    qDebug() << "Simulation initialized, starting simulation";
    
    // Initialize and start the simulation with the provided input
    m_Simulation->initializeFrominput(input);
    
    // Update button states appropriately
    updateButtonStates();
    
    qDebug() << "Simulation state after initialization:" << m_Simulation->State();
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
    qDebug() << "Play button clicked. Simulation state:" << m_Simulation->State();
    
    if (m_Simulation->canStart()) {
        m_Simulation->startSimulation();
        updateButtonStates();
        qDebug() << "Simulation started successfully";
    } else {
        qDebug() << "Cannot start simulation from current state";
    }
}

void UIMainWindow::on_m_simulation_pause_button_clicked()
{
    qDebug() << "Pause button clicked. Simulation state:" << m_Simulation->State();
    
    if (m_Simulation->canPause()) {
        m_Simulation->pauseSimulation();
        updateButtonStates();
        qDebug() << "Simulation paused successfully";
    } else {
        qDebug() << "Cannot pause simulation from current state";
    }
}

void UIMainWindow::on_m_simulation_restart_button_clicked()
{
    qDebug() << "Restart button clicked. Simulation state:" << m_Simulation->State();
    
    // Restart the simulation (this will stop it and set state to UNINITIALIZED)
    m_Simulation->restartSimulation();
    
    updateButtonStates();
    
    // Show setup dialog to reinitialize
    if (m_setup) {
        m_setup->show();
    }
}

void UIMainWindow::on_m_simulation_stop_button_clicked()
{
    qDebug() << "Stop button clicked. Simulation state:" << m_Simulation->State();
    
    if (m_Simulation->canStop()) {
        m_Simulation->stopSimulation();
        updateButtonStates();
        
        // Return to main menu
        ui->m_stacked_widget->setCurrentIndex(0);
        if (m_Demo) {
            m_Demo->startSimulation();
        }
        qDebug() << "Simulation stopped successfully";
    } else {
        qDebug() << "Cannot stop simulation from current state";
    }
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

void UIMainWindow::on_show_metrics_check_box_stateChanged(int arg1)
{
    if (m_metricsWidget) {
        bool visible = (arg1 == Qt::Checked);
        m_metricsWidget->setMetricsVisible(visible);
        
        if (visible) {
            // Bring to front and ensure it's visible
            m_metricsWidget->raise();
            m_metricsWidget->show();
        }
    }
}

void UIMainWindow::setupResizableVisualizePanelSplitter()
{
    // Find the frame that contains the visualize panel
    QFrame* frame3 = findChild<QFrame*>("frame_3");
    if (!frame3) {
        qDebug() << "Could not find frame_3 to make visualize panel resizable";
        return;
    }
    
    // Remove size constraints to allow resizing
    frame3->setMaximumWidth(QWIDGETSIZE_MAX);
    frame3->setMinimumWidth(200);
    frame3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    
    // Find the parent layout that contains both GraphicsView and frame_3
    QWidget* parent = frame3->parentWidget();
    if (!parent) return;
    
    QLayout* parentLayout = parent->layout();
    if (!parentLayout) return;
    
    // Try to find the graphics view to set up proper splitter behavior
    QGraphicsView* graphicsView = findChild<QGraphicsView*>("graphicsView");
    if (graphicsView) {
        // Ensure graphics view can shrink when visualize panel expands
        graphicsView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        graphicsView->setMinimumWidth(300); // Minimum width for graphics view
    }
    
    qDebug() << "Visualize panel made resizable - you can now resize the panel by dragging the window";
}

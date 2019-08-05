#include "uimainwindow.h"
#include "ui_uimainwindow.h"
#include <QDesktopServices>
#include <QUrl>

UIMainWindow::UIMainWindow(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::UIMainWindow)
{
    ui->setupUi(this);
    m_Simulation = new RoadIntersectionSimulation(ui->graphicsView);


}

UIMainWindow::~UIMainWindow()
{
    delete ui;
}

void UIMainWindow::on_m_SettingButton_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(3);
}

void UIMainWindow::on_m_ExitButton_clicked()
{
    QApplication::exit();
}

void UIMainWindow::on_m_AboutButton_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(1);
}

void UIMainWindow::on_m_PlayButton_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(4);
}

void UIMainWindow::on_m_HelpButton_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(2);
}

void UIMainWindow::on_m_about_back_button_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
}

void UIMainWindow::on_m_help_back_button_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
}

void UIMainWindow::on_m_simulation_back_icon_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
}

void UIMainWindow::on_m_setting_back_icon_clicked()
{
    ui->m_stacked_widget->setCurrentIndex(0);
}

void UIMainWindow::on_m_simulation_play_button_clicked()
{    
    m_Simulation->startSimulation();
    ui->m_simulation_play_button->setEnabled(false);
}

void UIMainWindow::on_m_simulation_pause_button_clicked()
{

}

void UIMainWindow::on_m_simulation_restart_button_clicked()
{

}

void UIMainWindow::on_m_simulation_stop_button_clicked()
{

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

}

void UIMainWindow::on_m_5_lanes_button_clicked()
{

}

void UIMainWindow::on_m_no_turn_button_clicked()
{

}

void UIMainWindow::on_m_turn_only_button_clicked()
{

}

void UIMainWindow::on_m_go_through_check_box_stateChanged(int arg1)
{

}

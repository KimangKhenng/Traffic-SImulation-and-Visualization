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

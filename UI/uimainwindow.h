#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QWidget>
#include "Utilities/roadintersectionsimulation.h"

namespace Ui {
class UIMainWindow;
}

class UIMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UIMainWindow(QWidget *parent = 0);
    ~UIMainWindow();

private slots:
    void on_m_SettingButton_clicked();

    void on_m_ExitButton_clicked();

    void on_m_AboutButton_clicked();

    void on_m_PlayButton_clicked();

    void on_m_HelpButton_clicked();

    void on_m_about_back_button_clicked();

    void on_m_help_back_button_clicked();

    void on_m_simulation_back_icon_clicked();

    void on_m_setting_back_icon_clicked();

    void on_m_simulation_play_button_clicked();

    void on_m_simulation_pause_button_clicked();

    void on_m_simulation_restart_button_clicked();

    void on_m_simulation_stop_button_clicked();


    void on_show_road_check_box_stateChanged(int arg1);

    void on_show_detectors_check_box_stateChanged(int arg1);

    void on_show_vehicles_vision_check_box_stateChanged(int arg1);

    void on_show_traffic_light_check_box_stateChanged(int arg1);

    void on_m_3_lanes_button_clicked();

    void on_m_5_lanes_button_clicked();

    void on_m_no_turn_button_clicked();

    void on_m_turn_only_button_clicked();

    void on_m_go_through_check_box_stateChanged(int arg1);

private:
    Ui::UIMainWindow *ui;
    RoadIntersectionSimulation *m_Simulation;
};

#endif // UIMAINWINDOW_H

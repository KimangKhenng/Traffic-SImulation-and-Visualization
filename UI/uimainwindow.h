#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include "Utilities/roadintersectionsimulation.h"
#include "UI/intropage.h"
#include "UI/simulationsetup.h"

namespace Ui {
class UIMainWindow;
}

class UIMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UIMainWindow(QWidget *parent = 0);


    ~UIMainWindow();
public slots:
    void onExitButtonClicked();

    void onAboutButtonClicked();

    void onPlayButtonClicked();

    void onHelpButtonClicked();

    void EnableSimulationButton(const bool& play = true,
                                const bool& pause = true,
                                const bool& stop = true,
                                const bool& restart = true);
    void updateStatus();

private slots:


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
    RoadIntersectionSimulation *m_Demo;
    IntroPage *m_intro_page;
    SimulationSetup *m_setup;
    int m_time_frame;

};

#endif // UIMAINWINDOW_H

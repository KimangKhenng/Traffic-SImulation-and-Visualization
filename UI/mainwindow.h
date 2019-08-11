#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <omp.h>
#include <QMainWindow>
#include <QGraphicsSvgItem>
#include <QGLWidget>
#include "commonenum.h"
#include "Entities/Vehicle/vehicle.h"
#include "Utilities/road.h"
#include "simulationscene.h"
#include "Utilities/vehiclesgenerator.h"
#include "Entities/trafficcontroller.h"

namespace Ui {
class MainWindow;
}
class SimulationControl;
//class DataWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
//    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);
    void set_up_random();
    void set_up();
    void turnOnSimulationState();
    void turnOffSimulationState();
    GENMETHOD getCurrentMethod() const;
    VEHICLEMETHOD getCurrentVehicleMethod() const;
    SimulationScene *scene() const;
    TrafficController *getController() const;
    bool getSimulate_state() const;
    void showTraffic(bool checked);
    void set3LaneCheck(const bool& b);
    void setGenMethod(const GENMETHOD& gen);
    void setGoThroguht(const bool& b);
    void setSimMode(const VEHICLEMETHOD& m);
    void setTrafficState(const bool& b);
    ~MainWindow();
public slots:
    void check_state();
private slots:

    void on_actionExit_triggered();
    void on_play_clicked();
    void on_back_clicked();
    void on_open_simulation_button_clicked();
    void on_exit_clicked();
    void on_reset_clicked();
    void on_pause_clicked();
    void on_stop_clicked();
    void set_up_demo(); 
    void on_m_road_check_button_toggled(bool checked);
    void on_m_detector_button_clicked(bool checked);
    void on_m_sightseeing_button_clicked(bool checked);
    void on_m_aboutus_button_clicked();
    void on_m_manul_control_button_clicked(bool checked);
    void on_m_5_lanes_clicked();
    void on_m_3_lanes_clicked();
    void on_m_no_traffic_clicked(bool checked);
    void on_m_no_turn_clicked();
    void on_m_go_though_clicked(bool checked);
    void on_m_drop_in_clicked();
    void on_actionPNG_triggered();   
    void on_m_tool_panel_check_box_clicked(bool checked);
    void on_m_visualize_panel_check_box_clicked(bool checked);
    void on_m_back_button_clicked();
    void on_m_only_turn_clicked();

private:
    void changeVehicleMode(const VEHICLEMETHOD &mode);
    Ui::MainWindow *ui;
    SimulationScene *m_scene;

    bool m_simulate_state;
    bool m_traffic_state;
    bool m_sightseeing;
    bool m_visualize_state;
    QTimer *m_machine_state;
    //QSplashScreen *m_loading_screen;
    //DataWidget *m_data_widget;
    TrafficController *m_controller;
    //QList<TrafficLight *> *m_traffic_light;
};

#endif // MAINWINDOW_H

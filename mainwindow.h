#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QGraphicsSvgItem>
#include "commonenum.h"
#include "vehicle.h"
#include "road.h"
#include "simulationscene.h"
#include "datawidget.h"
#include "simulationcontrol.h"
#include "vehiclesgenerator.h"
#include "trafficcontroller.h"
namespace Ui {
class MainWindow;
}
class SimulationControl;
class DataWidget;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
//    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);
    void set_duration_for_1_traffic(int red,int yellow,int green);
    void set_duration_for_2_traffic(int red,int yellow,int green);
    void set_duration_for_3_traffic(int red,int yellow,int green);
    void set_duration_for_4_traffic(int red,int yellow,int green);
    void set_up_random();
    void turnOnSimulationState();
    void turnOffSimulationState();
    void trunSimControlCheckOff();
    GENMETHOD getCurrentMethod();
    VEHICLEMETHOD getCurrentVehicleMethod();
    ~MainWindow();
    SimulationScene *scene() const;
    TrafficController *getController() const;
    bool getSimulate_state() const;

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
    void set_up();
    void set_up_demo(); 
    void on_m_road_check_button_toggled(bool checked);
    void on_m_detector_button_clicked(bool checked);
    void on_m_sightseeing_button_clicked(bool checked);
    void on_m_data_widget_clicked(bool checked);
    void on_m_control_button_clicked(bool checked);
    void on_m_aboutus_button_clicked();
    void on_m_manul_control_button_clicked(bool checked);
    void on_m_5_lanes_clicked();
    void on_m_3_lanes_clicked();
    void on_m_no_traffic_clicked(bool checked);
    void on_m_no_turn_clicked();

    void on_m_go_though_clicked(bool checked);

private:
    Ui::MainWindow *ui;
    SimulationScene *m_scene;
    QGraphicsSvgItem *m_path;
    road *m_road;
    bool m_simulate_state;
    bool m_traffic_state;
    bool m_sightseeing;
    QTimer *m_machine_state;
    QSplashScreen *m_loading_screen;
    SimulationControl *m_simulation_control_widget;
    DataWidget *m_data_widget;
    TrafficController *m_controller;
    QList<TrafficLight *> *m_traffic_light;
};

#endif // MAINWINDOW_H

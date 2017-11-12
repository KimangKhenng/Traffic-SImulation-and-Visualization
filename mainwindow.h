#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QGraphicsSvgItem>
#include <QSplashScreen>
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
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);
    void set_duration_for_1_traffic(int red,int yellow,int green);
    void set_duration_for_2_traffic(int red,int yellow,int green);
    void set_duration_for_3_traffic(int red,int yellow,int green);
    void set_duration_for_4_traffic(int red,int yellow,int green);
    void set_up_random();
    ~MainWindow();
public slots:
    void check_state();
    void random_of_1();
    void random_of_2();
    void random_of_3();
    void random_of_4();
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
private:
    Ui::MainWindow *ui;
    DataWidget *m_data_widget;
    SimulationScene *m_scene;
    QGraphicsSvgItem *m_path;
    road *m_road;
    bool m_simulate_state;
    bool m_traffic_state;
    bool m_sightseeing;
    QTimer *m_machine_state;
    QSplashScreen *m_loading_screen;
    SimulationControl *m_simulation_control_widget;
    QGraphicsProxyWidget *m_control_sim;
    QGraphicsProxyWidget *m_data_control;
    TrafficController *m_controller;
};

#endif // MAINWINDOW_H

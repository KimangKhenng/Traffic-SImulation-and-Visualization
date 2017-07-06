#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include <QSplashScreen>
#include "vehicle.h"
#include "road.h"
#include "simulationscene.h"
#include "datawidget.h"
#include "traffic_light_widget.h"
#include "simulationcontrol.h"
#include "datapath.h"
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
    QList<Traffic_Light_widget *> *get_traffic_list();
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
    void on_vehicles_clicked();
    void on_road_clicked();
    void on_trafficLight_clicked();
    void on_matherials_clicked();
    void on_terrains_clicked();
    void on_back_clicked();
    void on_open_simulation_button_clicked();
    void on_exit_clicked();
    void on_reset_clicked();
    void on_pause_clicked();
    void on_stop_clicked();
    void set_up();
    void set_up_demo();

private:
    Ui::MainWindow *ui;
    DataWidget *m_data_widget;
    SimulationScene *m_scene;
    //QGraphicsScene *m_scene;
    QList<Vehicle *> *m_car_list_1;
    QList<Vehicle *> *m_car_list_2;
    QList<Vehicle *> *m_car_list_3;
    QList<Vehicle *> *m_car_list_4;
    QList<Vehicle *> *m_car_list_5;
    QList<Vehicle *> *m_car_list_6;
    QList<Vehicle *> *m_car_list_7;
    QList<Vehicle *> *m_car_list_8;
    QList<Vehicle *> *m_car_list_9;
    QList<Vehicle *> *m_car_list_10;
    QList<Vehicle *> *m_car_list_11;
    QList<Vehicle *> *m_car_list_12;
    road *m_road;
    bool m_simulate_state;
    bool m_traffic_state;
    QTimer *m_machine_state;
    QList<Traffic_Light_widget *> *m_traffic_widget_list;
    QSplashScreen *m_loading_screen;
    SimulationControl *m_simulation_control_widget;
    QGraphicsProxyWidget *m_control_sim;
    QGraphicsProxyWidget *m_data_control;
    Traffic_Light_widget *m_traffic_widget_1;
    Traffic_Light_widget *m_traffic_widget_2;
    Traffic_Light_widget *m_traffic_widget_3;
    Traffic_Light_widget *m_traffic_widget_4;
};

#endif // MAINWINDOW_H

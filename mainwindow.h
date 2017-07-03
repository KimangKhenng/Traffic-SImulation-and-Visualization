#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "vehicle.h"
#include "road.h"
#include "simulationscene.h"
#include "datawidget.h"
#include "traffic_light_widget.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void resizeEvent(QResizeEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);
    ~MainWindow();
public slots:
    void check_state();
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
    void on_data_clicked();
    void on_stop_clicked();
    void on_m_control_clicked();

private:
    Ui::MainWindow *ui;
    DataWidget *m_data_widget;
    SimulationScene *m_scene;
    //QGraphicsScene *m_scene;
    QList<Vehicle *> *m_car_list;
    road *m_road;
    bool m_simulate_state;
    bool m_traffic_state;
    QTimer *m_machine_state;
    QList<Traffic_Light_widget *> *m_traffic_widget_list;

};

#endif // MAINWINDOW_H

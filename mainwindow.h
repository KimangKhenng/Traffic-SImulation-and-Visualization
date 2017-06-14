#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore>
#include <QtWidgets>
#include "vehicle.h"
#include "road.h"
#include "simulationscene.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual void resizeEvent(QResizeEvent *event);
    ~MainWindow();

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
private:
    Ui::MainWindow *ui;
    QTimer *m_timer;
    SimulationScene *m_scene;
    Vehicle *m_car;
    road *m_road;
    bool simulate_state;

};

#endif // MAINWINDOW_H

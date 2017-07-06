#ifndef SIMULATIONCONTROL_H
#define SIMULATIONCONTROL_H

#include <QWidget>
#include "mainwindow.h"
namespace Ui {
class SimulationControl;
}
class MainWindow;
class SimulationControl : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControl(QWidget *parent = 0);
    void get_main_windows(MainWindow *window);
    void get_traffic_list(QList<Traffic_Light_widget *> *m_traffic);
    ~SimulationControl();

private slots:
    void on_m_setup_button_clicked();
    void on_m_setup_birth_rate_button_clicked();
    void on_m_stop_clicked();

    void on_m_auto_traffic_clicked();

private:
    Ui::SimulationControl *ui;
    MainWindow *m_main_window;
    QList<Traffic_Light_widget *> *m_traffic_widget_list;

};

#endif // SIMULATIONCONTROL_H

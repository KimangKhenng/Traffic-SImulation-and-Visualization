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
    ~SimulationControl();

private slots:
    void on_m_setup_button_clicked();
    void on_m_setup_birth_rate_button_clicked();

    void on_m_stop_clicked();

private:
    Ui::SimulationControl *ui;
    MainWindow *m_main_window;

};

#endif // SIMULATIONCONTROL_H

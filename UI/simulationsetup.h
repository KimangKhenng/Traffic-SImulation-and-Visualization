#ifndef SIMULATIONSETUP_H
#define SIMULATIONSETUP_H

#include <QWidget>
#include <QRadioButton>
#include "commonenum.h"
namespace Ui {
class SimulationSetup;
}

class SimulationSetup : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationSetup(QWidget *parent = nullptr);
    ~SimulationSetup();

private slots:
    void on_start_simulation_button_clicked();
    void on_random_setup_clicked();
    void on_help_setup_button_clicked();
    void on_traffic_level_easy_input_clicked();
    void on_traffic_mode_moderate_input_clicked();
    void on_traffic_mode_busy_input_clicked();
    void on_light_quick_input_clicked();
    void on_light_moderate_input_clicked();
    void on_light_long_input_clicked();
    void on_experimental_mode_crazy_clicked();
    void on_experimental_free_clicked();
signals:
    void inputReady(SimulationInput input);
    void onHelpClicked();
    void onRandomClicked(SimulationInput input);

private:
    Ui::SimulationSetup *ui;
    SimulationInput input;
    QList<QRadioButton*> trafficButton;
    QList<QRadioButton*> lightButton;
};

#endif // SIMULATIONSETUP_H

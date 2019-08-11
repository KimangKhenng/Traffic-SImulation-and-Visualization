#include "simulationsetup.h"
#include "ui_simulationsetup.h"

SimulationSetup::SimulationSetup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulationSetup)
{
    ui->setupUi(this);
    trafficButton.append(ui->traffic_level_easy_input);
    trafficButton.append(ui->traffic_mode_moderate_input);
    trafficButton.append(ui->traffic_mode_busy_input);
    lightButton.append(ui->light_quick_input);
    lightButton.append(ui->light_moderate_input);
    lightButton.append(ui->light_long_input);
}

SimulationSetup::~SimulationSetup()
{
    delete ui;
}

void SimulationSetup::on_start_simulation_button_clicked()
{
    for(int i = 0 ; i < 3 ; ++i){
        if(trafficButton.at(i)->isChecked()){
            for(int j = 0 ; j < 3 ; ++j){
                if(lightButton.at(j)->isChecked()){
                    emit inputReady(input);
                    close();
                }
            }
        }
    }
    return;

}

void SimulationSetup::on_random_setup_clicked()
{
    input.random();
    emit inputReady(input);
    close();
}

void SimulationSetup::on_help_setup_button_clicked()
{
    onHelpClicked();
    close();
}

void SimulationSetup::on_traffic_level_easy_input_clicked()
{
    input.trafficEasy();
}

void SimulationSetup::on_traffic_mode_moderate_input_clicked()
{
    input.trafficModerate();
}

void SimulationSetup::on_traffic_mode_busy_input_clicked()
{
    input.trafficBusy();
}

void SimulationSetup::on_light_quick_input_clicked()
{
    input.LightingQuick();
}

void SimulationSetup::on_light_moderate_input_clicked()
{
    input.LightingModerate();
}

void SimulationSetup::on_light_long_input_clicked()
{
    input.LightingLong();
}

void SimulationSetup::on_experimental_mode_crazy_clicked()
{
    input.ExperimentalCrazy();
    emit inputReady(input);
    close();
}

void SimulationSetup::on_experimental_free_clicked()
{
    input.ExperimentalFreeForAll();
    emit inputReady(input);
    close();
}

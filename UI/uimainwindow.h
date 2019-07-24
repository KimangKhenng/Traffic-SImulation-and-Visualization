#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QWidget>
#include "Utilities/roadintersectionsimulation.h"

namespace Ui {
class UIMainWindow;
}

class UIMainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit UIMainWindow(QWidget *parent = 0);
    ~UIMainWindow();

private slots:
    void on_m_SettingButton_clicked();

    void on_m_ExitButton_clicked();

    void on_m_AboutButton_clicked();

    void on_m_PlayButton_clicked();

    void on_m_HelpButton_clicked();

    void on_m_about_back_button_clicked();

    void on_m_help_back_button_clicked();

    void on_m_simulation_back_icon_clicked();

    void on_m_setting_back_icon_clicked();

    void on_m_simulation_play_button_clicked();

    void on_m_simulation_pause_button_clicked();

    void on_m_simulation_restart_button_clicked();

    void on_m_simulation_stop_button_clicked();

private:
    Ui::UIMainWindow *ui;
    RoadIntersectionSimulation *m_Simulation;
};

#endif // UIMAINWINDOW_H

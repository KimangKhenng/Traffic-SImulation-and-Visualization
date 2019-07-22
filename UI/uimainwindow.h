#ifndef UIMAINWINDOW_H
#define UIMAINWINDOW_H

#include <QWidget>

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

private:
    Ui::UIMainWindow *ui;
};

#endif // UIMAINWINDOW_H

#ifndef TOOLPANEL_H
#define TOOLPANEL_H

#include <QWidget>

namespace Ui {
class toolpanel;
}

class toolpanel : public QWidget
{
    Q_OBJECT

public:
    explicit toolpanel(QWidget *parent = 0);
    ~toolpanel();

private slots:
    void on_m_road_check_button_toggled(bool checked);
    void on_m_sightseeing_button_toggled(bool checked);
    void on_m_detector_button_toggled(bool checked);
    void on_m_manul_control_button_toggled(bool checked);
    void on_m_no_traffic_toggled(bool checked);
    void on_m_3_lanes_toggled(bool checked);
    void on_m_5_lanes_toggled(bool checked);
    void on_m_no_turn_toggled(bool checked);
    void on_m_go_though_toggled(bool checked);
private:
    Ui::toolpanel *ui;
};

#endif // TOOLPANEL_H

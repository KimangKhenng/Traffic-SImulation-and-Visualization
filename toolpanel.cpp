#include "toolpanel.h"
#include "ui_toolpanel.h"

toolpanel::toolpanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::toolpanel)
{
    ui->setupUi(this);
}

toolpanel::~toolpanel()
{
    delete ui;
}

void toolpanel::on_m_road_check_button_toggled(bool checked)
{

}

void toolpanel::on_m_sightseeing_button_toggled(bool checked)
{

}

void toolpanel::on_m_detector_button_toggled(bool checked)
{

}

void toolpanel::on_m_manul_control_button_toggled(bool checked)
{

}

void toolpanel::on_m_no_traffic_toggled(bool checked)
{

}

void toolpanel::on_m_3_lanes_toggled(bool checked)
{

}

void toolpanel::on_m_5_lanes_toggled(bool checked)
{

}

void toolpanel::on_m_no_turn_toggled(bool checked)
{

}

void toolpanel::on_m_go_though_toggled(bool checked)
{

}

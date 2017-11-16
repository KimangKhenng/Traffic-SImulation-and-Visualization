#ifndef DATAWIDGET_H
#define DATAWIDGET_H

#include <QWidget>
#include <QtCore>
#include "mainwindow.h"
#include "qcustomplot.h"
#include "trafficcontroller.h"

#define X_NUM_RANG 20;
#define Y_NUM_RANG 20;
#define X_FLOW_MAX 20;
#define Y_FLOW_MAX 20;
#define X_DEN_MAX 10;
#define Y_DEN_MAX 20;
#define X_HEAD_MAX 20;
#define Y_HEAD_MAX 20;

namespace Ui {
class DataWidget;
}
class MainWindow;
class DataWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DataWidget(QWidget *parent = 0);
    ~DataWidget();
    void setUpNumberWidget();
    void setUpFlowWidget();
    void setUpDensityWidget();
    void setUpHeadwayWidget();
//protected:
//    virtual void dragMoveEvent(QDragMoveEvent *event) Q_DECL_OVERRIDE;
//    virtual void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual void mouseReleaseEvent(QMouseEvent *event) Q_DECL_OVERRIDE;
//    virtual bool event(QEvent *event) Q_DECL_OVERRIDE;
//    void setDetector(QList<TrafficDetector *> *detector);
    void setEtimer(QList<QElapsedTimer *> *etimer);
    void setController(TrafficController *controller);

private slots:
    void on_m_show_hide_clicked(bool checked);
    void update_1();
    void update_2();
    void update_3();
    void update_4();
private:
    void update_FLOW();
    void update_NUM();
    void update_DEN();
    void update_HEAD();
    int getNumber(int x);
    int getNumberNS();
    int getNumberSN();
    int getNumberWE();
    int getNumberEW();
    double getFlow(int x);
    double getFlowNS();
    double getFlowSN();
    double getFlowWE();
    double getFlowEW();
    double getDensity(int x);
    double getDensityNS();
    double getDensitySN();
    double getDensityWE();
    double getDensityEW();
    double getHeadWay(int x);
    double getHeadWayNS();
    double getHeadWaySN();
    double getHeadWayWE();
    double getHeadWayEW();
    MainWindow *m_w;
    Ui::DataWidget *ui;
    QList<QCustomPlot *> m_number_widget;
    QList<QCustomPlot *> m_flow_widget;
    QList<QCustomPlot *> m_density_widget;
    QList<QCustomPlot *> m_headway_widget;
    TrafficController *m_controller;
//    QList<TrafficDetector *> *m_detector;
    QList<QVector<int>> m_number;
    QList<QVector<double>> m_flow;
    QList<QVector<double>> m_density;
    QList<QVector<double>> m_headway;
    QList<QTimer *> *m_timer;
    QList<QElapsedTimer *> *m_etimer;

};

#endif // DATAWIDGET_H

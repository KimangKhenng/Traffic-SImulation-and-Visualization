#ifndef VISUALIZEPANEL_H
#define VISUALIZEPANEL_H

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
class VisualizePanel;
}
class MainWindow;
class VisualizePanel : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizePanel(QWidget *parent = 0);
    //void initialize();
    void setEtimer(QList<QElapsedTimer *> *etimer);
    void setController(TrafficController *controller);
    void setMainWindows(MainWindow *w);
    void update_1();
    void update_2();
    void update_3();
    void update_4();
    void update_all();
    ~VisualizePanel();
//private slots:
//    void update_1();
//    void update_2();
//    void update_3();
//    void update_4();
private:
    void setUpNumberWidget();
    void setUpFlowWidget();
    void setUpDensityWidget();
    void setUpHeadwayWidget();
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
    Ui::VisualizePanel *ui;
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

#endif // VISUALIZEPANEL_H

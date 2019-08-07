#ifndef VISUALIZEPANEL_H
#define VISUALIZEPANEL_H

#include <QFile>
#include <QDir>
#include <QString>
#include "Utilities/qcustomplot.h"
#include "Entities/trafficcontroller.h"

#define X_NUM_RANG 20;
#define Y_NUM_RANG 20;
#define X_FLOW_MAX 20;
#define Y_FLOW_MAX 20;
#define X_DEN_MAX 10;
#define Y_DEN_MAX 20;
#define X_HEAD_MAX 20;
#define Y_HEAD_MAX 20;
#define RESET_RANGED 20

namespace Ui {
class VisualizePanel;
}
class MainWindow;

class VisualizePanel : public QWidget
{
    Q_OBJECT

public:
    explicit VisualizePanel(QWidget *parent = nullptr);
    //void initialize();
    //void setEtimer(QList<QElapsedTimer *> *etimer);
    void setController(TrafficController *controller);


    ~VisualizePanel() override;
//private slots:
//    void update_1();
//    void update_2();
//    void update_3();
//    void update_4();
public slots:
    void update_all();
private:
    void update_1();
    void update_2();
    void update_3();
    void update_4();
    void setUpNumberWidget();
    void setUpFlowWidget();
    void setUpDensityWidget();
    void setUpHeadwayWidget();
    void update_FLOW();
    void update_NUM();
    void update_DEN();
    void update_HEAD();
    int getNumber(const int &x) const;
    int getNumberNS() const;
    int getNumberSN() const;
    int getNumberWE() const;
    int getNumberEW() const;
    double getFlow(const int &x) const;
    double getFlowNS() const;
    double getFlowSN() const;
    double getFlowWE() const;
    double getFlowEW() const;
    double getDensity(const int &x) const;
    double getDensityNS() const;
    double getDensitySN() const;
    double getDensityWE() const;
    double getDensityEW() const;
    double getHeadWay(const int &x) const;
    double getHeadWayNS() const;
    double getHeadWaySN() const;
    double getHeadWayWE() const;
    double getHeadWayEW() const;

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
//    QList<QTimer *> *m_timer;
//    QList<QElapsedTimer *> *m_etimer;

    QList<QFile*> m_queue_size;
//    QTextStream numStream;
//    QTextStream flowStream;
//    QTextStream headwayStream;

};

#endif // VISUALIZEPANEL_H

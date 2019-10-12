#include "visualizepanel.h"
#include "ui_visualizepanel.h"



VisualizePanel::VisualizePanel(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::VisualizePanel)
{
    ui->setupUi(this);
    // Set up file for writing
    // Number in queue vs time
    for(int i = 0 ; i < 4 ; i++){
        m_queue_size.append(new QFile("queue_" + QString::number(i) + ".txt"));
    }
    for(int i = 0 ; i < m_queue_size.size() ; i++){
        if(!m_queue_size.at(i)->exists()){
            qDebug()<<m_queue_size.at(i)->fileName() + " Error";
        }
        if(m_queue_size.at(i)->open(QIODevice::ReadOnly|QIODevice::Text|QIODevice::WriteOnly)){
            QTextStream txtStream(m_queue_size.at(i));
            txtStream<<"This file contain data for queue size vs simulation time.\n";
            txtStream<<"This is queue size for approach " + QString::number(i) +"\n";
            txtStream.flush();
        }
    }


    // setUp Timer
//    m_timer = new QList<QTimer *>();
//    for(int i = 0 ; i < 4 ; ++i){
//        m_timer->append(new QTimer());
//    }
//    this->connect(m_timer->at(0),SIGNAL(timeout()),this,SLOT(update_1()));
//    this->connect(m_timer->at(1),SIGNAL(timeout()),this,SLOT(update_2()));
//    this->connect(m_timer->at(2),SIGNAL(timeout()),this,SLOT(update_3()));
//    this->connect(m_timer->at(3),SIGNAL(timeout()),this,SLOT(update_4()));
//    for(int i = 0 ; i < 4 ; ++i){
//        m_timer->at(i)->start(10);
//    }
    // Number Widget
    m_number_widget.append(ui->m_number_widget_1);
    m_number_widget.append(ui->m_number_widget_2);
    m_number_widget.append(ui->m_number_widget_3);
    m_number_widget.append(ui->m_number_widget_4);
    // Flow Widget
    m_flow_widget.append(ui->m_flow_widget_1);
    m_flow_widget.append(ui->m_flow_widget_2);
    m_flow_widget.append(ui->m_flow_widget_3);
    m_flow_widget.append(ui->m_flow_widget_4);
    // Density Widget
    m_density_widget.append(ui->m_density_widget_1);
    m_density_widget.append(ui->m_density_widget_2);
    m_density_widget.append(ui->m_density_widget_3);
    m_density_widget.append(ui->m_density_widget_4);
    // HeadWay Widget
    m_headway_widget.append(ui->m_headway_widget_1);
    m_headway_widget.append(ui->m_headway_widget_2);
    m_headway_widget.append(ui->m_headway_widget_3);
    m_headway_widget.append(ui->m_headway_widget_4);
    //Parent
//    if(dynamic_cast<MainWindow *>(this->parentWidget())){
//        m_w = dynamic_cast<MainWindow *>(this->parentWidget());
//        //qDebug()<<"Hello";
//    }
    // SetUp
    //setWindowTitle(QApplication::translate("toplevel", "Real-Time Data Visualization"));
    //setWindowFlags(Qt::Widget);

    setUpNumberWidget();
    setUpFlowWidget();
    setUpHeadwayWidget();
    setUpDensityWidget();
    //qDebug()<<"Hello";
}

//void VisualizePanel::initialize()
//{
//    m_timer = new QList<QTimer *>();
//    for(int i = 0 ; i < 4 ; ++i){
//        m_timer->append(new QTimer());
//    }
//    this->connect(m_timer->at(0),SIGNAL(timeout()),this,SLOT(update_1()));
//    this->connect(m_timer->at(1),SIGNAL(timeout()),this,SLOT(update_2()));
//    this->connect(m_timer->at(2),SIGNAL(timeout()),this,SLOT(update_3()));
//    this->connect(m_timer->at(3),SIGNAL(timeout()),this,SLOT(update_4()));
//    for(int i = 0 ; i < 4 ; ++i){
//        m_timer->at(i)->start(10);
//    }
//}



//bool VisualizePanel::event(QEvent *event)
//{

//    if(event->type() == QEvent::MouseButtonPress){
//        qDebug()<<"Hello";
//        setWindowOpacity(1.0);
//    }
//    return QWidget::event(event);
//}

//void VisualizePanel::dragMoveEvent(QDragMoveEvent *event)
//{
//    qDebug()<<"Hello";
//    setWindowOpacity(1.0);
//}

//void VisualizePanel::mousePressEvent(QMouseEvent *event)
//{
//    //qDebug()<<"Hello";
//    setWindowOpacity(1.0);
//    //QWidget::mousePressEvent(event);
//}

//void VisualizePanel::mouseReleaseEvent(QMouseEvent *event)
//{
//    //qDebug()<<"Hello";
//    setWindowOpacity(0.5);
//    //QWidget::mousePressEvent(event);
//}

VisualizePanel::~VisualizePanel()
{
    delete ui;
}

void VisualizePanel::setUpNumberWidget()
{
    for(int i = 0 ; i < m_number_widget.size() ; ++i){
        m_number_widget.at(i)->addGraph();
    //    graph1->setData(x1, y1);
        m_number_widget.at(i)->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black, 1.5), QBrush(Qt::white), 9));
        m_number_widget.at(i)->graph(0)->setPen(QPen(QColor(120, 120, 120), 2));
        // move bars above graphs and grid below bars:
        m_number_widget.at(i)->addLayer("abovemain", m_number_widget.at(i)->layer("main"), QCustomPlot::limAbove);
        m_number_widget.at(i)->addLayer("belowmain", m_number_widget.at(i)->layer("main"), QCustomPlot::limBelow);
        m_number_widget.at(i)->graph(0)->setLayer("abovemain");
        m_number_widget.at(i)->xAxis->grid()->setLayer("belowmain");
        m_number_widget.at(i)->yAxis->grid()->setLayer("belowmain");
        // set some pens, brushes and backgrounds:
        m_number_widget.at(i)->xAxis->setBasePen(QPen(Qt::white, 1));
        m_number_widget.at(i)->yAxis->setBasePen(QPen(Qt::white, 1));
        m_number_widget.at(i)->xAxis->setTickPen(QPen(Qt::white, 1));
        m_number_widget.at(i)->yAxis->setTickPen(QPen(Qt::white, 1));
        m_number_widget.at(i)->xAxis->setSubTickPen(QPen(Qt::white, 1));
        m_number_widget.at(i)->yAxis->setSubTickPen(QPen(Qt::white, 1));
        m_number_widget.at(i)->xAxis->setTickLabelColor(Qt::white);
        m_number_widget.at(i)->yAxis->setTickLabelColor(Qt::white);
        m_number_widget.at(i)->xAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        m_number_widget.at(i)->yAxis->grid()->setPen(QPen(QColor(140, 140, 140), 1, Qt::DotLine));
        m_number_widget.at(i)->xAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        m_number_widget.at(i)->yAxis->grid()->setSubGridPen(QPen(QColor(80, 80, 80), 1, Qt::DotLine));
        m_number_widget.at(i)->xAxis->grid()->setSubGridVisible(true);
        m_number_widget.at(i)->yAxis->grid()->setSubGridVisible(true);
        m_number_widget.at(i)->xAxis->grid()->setZeroLinePen(Qt::NoPen);
        m_number_widget.at(i)->yAxis->grid()->setZeroLinePen(Qt::NoPen);
        m_number_widget.at(i)->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        m_number_widget.at(i)->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
        QLinearGradient plotGradient;
        plotGradient.setStart(0, 0);
        plotGradient.setFinalStop(0, 350);
        plotGradient.setColorAt(0, QColor(80, 80, 80));
        plotGradient.setColorAt(1, QColor(50, 50, 50));
        m_number_widget.at(i)->setBackground(plotGradient);
        QLinearGradient axisRectGradient;
        axisRectGradient.setStart(0, 0);
        axisRectGradient.setFinalStop(0, 350);
        axisRectGradient.setColorAt(0, QColor(80, 80, 80));
        axisRectGradient.setColorAt(1, QColor(30, 30, 30));
        m_number_widget.at(i)->axisRect()->setBackground(axisRectGradient);
        m_number_widget.at(i)->rescaleAxes();
        m_number_widget.at(i)->yAxis->setRange(0,20);
        m_number_widget.at(i)->xAxis->setRange(0,20);
        m_number_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
        connect(m_number_widget.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), m_number_widget.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_number_widget.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), m_number_widget.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }
    m_number_widget.at(0)->yAxis->setRange(0,MAX_E_W);
    m_number_widget.at(1)->yAxis->setRange(0,MAX_N_S);
    m_number_widget.at(2)->yAxis->setRange(0,MAX_W_E);
    m_number_widget.at(3)->yAxis->setRange(0,MAX_S_N);

    for(int i = 0 ; i < m_number_widget.size() ; ++i){
        m_number_widget.at(i)->addGraph(); // blue line
        m_number_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));

        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%s");
        m_number_widget.at(i)->xAxis->setTicker(timeTicker);
        m_number_widget.at(i)->axisRect()->setupFullAxesBox();
        m_number_widget.at(i)->yAxis->setRange(0, 5);
        m_number_widget.at(i)->xAxis->setRange(0, 20);
        //m_number_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(m_number_widget.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), m_number_widget.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_number_widget.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), m_number_widget.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }
    m_number_widget.at(0)->yAxis->setRange(0,MAX_E_W);
    m_number_widget.at(1)->yAxis->setRange(0,MAX_N_S);
    m_number_widget.at(2)->yAxis->setRange(0,MAX_W_E);
    m_number_widget.at(3)->yAxis->setRange(0,MAX_S_N);

}

void VisualizePanel::setUpFlowWidget()
{
    for(int i = 0 ; i < m_flow_widget.size() ; ++i){
        m_flow_widget.at(i)->addGraph(); // blue line
        m_flow_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));

        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%s");
        m_flow_widget.at(i)->xAxis->setTicker(timeTicker);
        m_flow_widget.at(i)->axisRect()->setupFullAxesBox();
        m_flow_widget.at(i)->yAxis->setRange(0, 5);
        m_flow_widget.at(i)->xAxis->setRange(0, 20);
        //m_flow_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(m_flow_widget.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), m_flow_widget.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_flow_widget.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), m_flow_widget.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }
    m_flow_widget.at(0)->yAxis->setRange(0,MAX_E_W);
    m_flow_widget.at(1)->yAxis->setRange(0,MAX_N_S);
    m_flow_widget.at(2)->yAxis->setRange(0,MAX_W_E);
    m_flow_widget.at(3)->yAxis->setRange(0,MAX_S_N);
}

void VisualizePanel::setUpDensityWidget()
{
    for(int i = 0 ; i < m_density_widget.size() ; ++i){
        m_density_widget.at(i)->addGraph(); // blue line
        m_density_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));

        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%s");
        m_density_widget.at(i)->xAxis->setTicker(timeTicker);
        m_density_widget.at(i)->axisRect()->setupFullAxesBox();
        m_density_widget.at(i)->yAxis->setRange(0, 5);
        m_density_widget.at(i)->xAxis->setRange(0, 20);
        //m_density_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(m_density_widget.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), m_density_widget.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_density_widget.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), m_density_widget.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }
    m_density_widget.at(0)->yAxis->setRange(0,MAX_E_W);
    m_density_widget.at(1)->yAxis->setRange(0,MAX_N_S);
    m_density_widget.at(2)->yAxis->setRange(0,MAX_W_E);
    m_density_widget.at(3)->yAxis->setRange(0,MAX_S_N);
}

void VisualizePanel::setUpHeadwayWidget()
{
    for(int i = 0 ; i < m_headway_widget.size() ; ++i){
        m_headway_widget.at(i)->addGraph(); // blue line
        m_headway_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));

        QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
        timeTicker->setTimeFormat("%s");
        m_headway_widget.at(i)->xAxis->setTicker(timeTicker);
        m_headway_widget.at(i)->axisRect()->setupFullAxesBox();
        m_headway_widget.at(i)->yAxis->setRange(0, 5);
        m_headway_widget.at(i)->xAxis->setRange(0, 20);
        //m_headway_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
        // make left and bottom axes transfer their ranges to right and top axes:
        connect(m_headway_widget.at(i)->xAxis, SIGNAL(rangeChanged(QCPRange)), m_headway_widget.at(i)->xAxis2, SLOT(setRange(QCPRange)));
        connect(m_headway_widget.at(i)->yAxis, SIGNAL(rangeChanged(QCPRange)), m_headway_widget.at(i)->yAxis2, SLOT(setRange(QCPRange)));
    }
    m_headway_widget.at(0)->yAxis->setRange(0,MAX_E_W);
    m_headway_widget.at(1)->yAxis->setRange(0,MAX_N_S);
    m_headway_widget.at(2)->yAxis->setRange(0,MAX_W_E);
    m_headway_widget.at(3)->yAxis->setRange(0,MAX_S_N);
}

int VisualizePanel::getNumber(const int &x) const
{
    switch (x) {
        case 0 :
            return getNumberEW();
        case 1 :
            return getNumberNS();
        case 2:
            return getNumberWE();
        case 3:
            return getNumberSN();
    }
    return 0;
}

int VisualizePanel::getNumberNS() const
{
    int num = 0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_N_S).size() ; ++i){
        num += m_controller->getDetectorByRegion(REGION_N_S).at(i)->getNumbersOfVehicles();
    }
    return num;
}

int VisualizePanel::getNumberSN() const
{
    int num = 0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_S_N).size() ; ++i){
        num += m_controller->getDetectorByRegion(REGION_S_N).at(i)->getNumbersOfVehicles();
    }
    return num;
}

int VisualizePanel::getNumberWE() const
{
    int num = 0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_W_E).size() ; ++i){
        num += m_controller->getDetectorByRegion(REGION_W_E).at(i)->getNumbersOfVehicles();
    }
    return num;
}

int VisualizePanel::getNumberEW() const
{
    int num = 0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_E_W).size() ; ++i){
        num += m_controller->getDetectorByRegion(REGION_E_W).at(i)->getNumbersOfVehicles();
    }
    return num;
}

double VisualizePanel::getFlow(const int &x) const
{
    switch (x) {
        case 0 :
            return getFlowEW();//EW
        case 1 :
            return getFlowNS();//NS
        case 2:
            return getFlowWE();//WE
        case 3:
            return getFlowSN();//SN
    }
    return 0;
}

double VisualizePanel::getFlowNS() const
{
    double flow = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_N_S).size() ; ++i){
        flow += static_cast<double>(m_controller->getDetectorByRegion(REGION_N_S).at(i)->getFlow());
    }
    return flow;
}

double VisualizePanel::getFlowSN() const
{
    double flow = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_S_N).size() ; ++i){
        flow += static_cast<double>(m_controller->getDetectorByRegion(REGION_S_N).at(i)->getFlow());
    }
    return flow;
}

double VisualizePanel::getFlowWE() const
{
    double flow = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_W_E).size() ; ++i){
        flow += static_cast<double>(m_controller->getDetectorByRegion(REGION_W_E).at(i)->getFlow());
    }
    return flow;
}

double VisualizePanel::getFlowEW() const
{
    double flow = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_E_W).size() ; ++i){
        flow += static_cast<double>(m_controller->getDetectorByRegion(REGION_E_W).at(i)->getFlow());
    }
    return flow;
}

double VisualizePanel::getDensity(const int &x) const
{
    switch (x) {
        case 0 :
            return getDensityEW();//EW
        case 1 :
            return getDensityNS();//NS
        case 2:
            return getDensityWE();//WE
        case 3:
            return getDensitySN();//SN
    }
    return 0;
}

double VisualizePanel::getDensityNS() const
{
    double den = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_N_S).size() ; ++i){
        den += static_cast<double>(m_controller->getDetectorByRegion(REGION_N_S).at(i)->getDensity());
    }
    return den;
}

double VisualizePanel::getDensitySN() const
{
    double den = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_S_N).size() ; ++i){
        den += static_cast<double>(m_controller->getDetectorByRegion(REGION_S_N).at(i)->getDensity());
    }
    return den;
}

double VisualizePanel::getDensityWE() const
{
    double den = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_W_E).size() ; ++i){
        den += static_cast<double>(m_controller->getDetectorByRegion(REGION_W_E).at(i)->getDensity());
    }
    return den;
}

double VisualizePanel::getDensityEW() const
{
    double den = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_E_W).size() ; ++i){
        den += static_cast<double>(m_controller->getDetectorByRegion(REGION_E_W).at(i)->getDensity());
    }
    return den;
}

double VisualizePanel::getHeadWay(const int &x) const
{
    switch (x) {
        case 0 :
            return getHeadWayEW();//EW
        case 1 :
            return getHeadWayNS();//NS
        case 2:
            return getHeadWayWE();//WE
        case 3:
            return getHeadWaySN();//SN
    }
    return 0;
}

double VisualizePanel::getHeadWayNS() const
{
    double head = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_N_S).size() ; ++i){
        head += static_cast<double>(m_controller->getDetectorByRegion(REGION_N_S).at(i)->getHeadWay());
    }
    return head;
}

double VisualizePanel::getHeadWaySN() const
{
    double head = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_S_N).size() ; ++i){
        head += static_cast<double>(m_controller->getDetectorByRegion(REGION_S_N).at(i)->getHeadWay());
    }
    return head;
}

double VisualizePanel::getHeadWayWE() const
{
    double head = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_W_E).size() ; ++i){
        head += static_cast<double>(m_controller->getDetectorByRegion(REGION_W_E).at(i)->getHeadWay());
    }
    return head;
}

double VisualizePanel::getHeadWayEW() const
{
    double head = 0.0;
    for(int i = 0 ; i < m_controller->getDetectorByRegion(REGION_E_W).size() ; ++i){
        head += static_cast<double>(m_controller->getDetectorByRegion(REGION_E_W).at(i)->getHeadWay());
    }
    return head;
}



void VisualizePanel::update_1()
{
    update_NUM();
}

void VisualizePanel::update_2()
{

    update_FLOW();
}

void VisualizePanel::update_3()
{

    update_DEN();
}

void VisualizePanel::update_4()
{

    update_HEAD();
}

void VisualizePanel::update_all()
{
    update_1();
    update_2();
    update_3();
    update_4();
}
void VisualizePanel::update_FLOW()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
//    if(key >= RESET_RANGED){
//        for(int i = 0 ; i < 4 ; ++i){
////            m_flow_widget.at(i)->graph(0)->data().clear();
////            m_flow_widget.at(i)->graph(0)->data().data()->clear();
//            m_flow_widget.at(i)->clearGraphs();
////            m_flow_widget.at(i)->clearItems();
////            m_flow_widget.at(i)->clearPlottables();
//            m_flow_widget.at(i)->addGraph();
//            m_flow_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//            //m_flow_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
//        }
//        time.restart();
//        key = 0;
//        lastPointKey = 0;
//    }
    if(key - lastPointKey > 0.1){
        for(int i = 0 ; i < m_flow_widget.size() ; ++i){
            //m_flow_widget.at(i)->graph(0)->data().data()->clear();
            //m_flow_widget.at(i)->graph(0)->data().data()->removeBefore(key-20.0);
            m_flow_widget.at(i)->graph(0)->addData(key,getFlow(i));
        }
        lastPointKey = key;
    }
    for(int i = 0 ; i < m_flow_widget.size() ; ++i){
        m_flow_widget.at(i)->xAxis->setRange(key,20, Qt::AlignRight);
        m_flow_widget.at(i)->replot();
    }
}

void VisualizePanel::update_NUM()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
//    if(key >= RESET_RANGED){
//        for(int i = 0 ; i < 4 ; ++i){
////            m_number_widget.at(i)->graph(0)->data().clear();
////            m_number_widget.at(i)->graph(0)->data().data()->clear();
//            m_number_widget.at(i)->clearGraphs();
//            m_number_widget.at(i)->addGraph();
//            m_number_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//            //m_number_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
//        }
//        time.restart();
//        key = 0;
//        lastPointKey = 0;
//    }
    if(key - lastPointKey > 1){
        for(int i = 0 ; i < m_number_widget.size() ; ++i){
            //m_number_widget.at(i)->graph(0)->data().data()->clear();
            //m_number_widget.at(i)->graph(0)->data().data()->removeBefore(key-20.0);
            m_number_widget.at(i)->graph(0)->addData(key,getNumber(i));
            //QTextStream txtStream(m_queue_size.at(i));
            //txtStream<<QString::number(key)<<"\t"<<QString::number(getNumber(i))<<"\n";
            //txtStream.flush();

        }
        lastPointKey = key;
    }
    for(int i = 0 ; i < m_number_widget.size() ; ++i){
        m_number_widget.at(i)->xAxis->setRange(key,20, Qt::AlignRight);
        m_number_widget.at(i)->replot();
    }
}

void VisualizePanel::update_DEN()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
//    if(key >= RESET_RANGED){
//        for(int i = 0 ; i < 4 ; ++i){
////            m_density_widget.at(i)->graph(0)->data().clear();
////            m_density_widget.at(i)->graph(0)->data().data()->clear();
//           m_density_widget.at(i)->clearGraphs();
//           m_density_widget.at(i)->addGraph();
//           m_density_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//           //m_density_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
//        }
//        time.restart();
//        key = 0;
//        lastPointKey = 0;
//    }
    if(key - lastPointKey > 0.1){
        for(int i = 0 ; i < m_density_widget.size() ; ++i){
            //m_density_widget.at(i)->graph(0)->data().data()->clear();
            //m_density_widget.at(i)->graph(0)->data().data()->removeBefore(key-20.0);
            m_density_widget.at(i)->graph(0)->addData(key,getDensity(i));
        }
        lastPointKey = key;
    }
    for(int i = 0 ; i < m_density_widget.size() ; ++i){
        m_density_widget.at(i)->xAxis->setRange(key,20, Qt::AlignRight);
        m_density_widget.at(i)->replot();
    }
}

void VisualizePanel::update_HEAD()
{
    static QTime time(QTime::currentTime());
    double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
    static double lastPointKey = 0;
//    if(key >= RESET_RANGED){
//        for(int i = 0 ; i < 4 ; ++i){
////            m_headway_widget.at(i)->graph(0)->data().clear();
////            m_headway_widget.at(i)->graph(0)->data().data()->clear();
//            m_headway_widget.at(i)->clearGraphs();
//            m_headway_widget.at(i)->addGraph();
//            m_headway_widget.at(i)->graph(0)->setPen(QPen(QColor(40, 110, 255)));
//            //m_headway_widget.at(i)->graph(0)->layer()->setMode(QCPLayer::lmBuffered);
//        }
//        time.restart();
//        key = 0;
//        lastPointKey = 0;
//    }
    if(key - lastPointKey > 0.1){
        for(int i = 0 ; i < m_headway_widget.size() ; ++i){
            //m_headway_widget.at(i)->graph(0)->data().data()->clear();
            //m_headway_widget.at(i)->graph(0)->data().data()->removeBefore(key-20.0);
            m_headway_widget.at(i)->graph(0)->addData(key,getHeadWay(i));
        }
        lastPointKey = key;
    }
    for(int i = 0 ; i < m_headway_widget.size() ; ++i){
        m_headway_widget.at(i)->xAxis->setRange(key,20, Qt::AlignRight);
        m_headway_widget.at(i)->replot();
    }
}

void VisualizePanel::setController(TrafficController *controller)
{
    m_controller = controller;
}


//void VisualizePanel::setEtimer(QList<QElapsedTimer *> *etimer)
//{
//    m_etimer = etimer;
//}

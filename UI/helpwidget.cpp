#include "helpwidget.h"
#include "ui_helpwidget.h"

HelpWidget::HelpWidget(QWidget *parent)
    :QWidget(parent)
    ,ui(new Ui::HelpWidget)
{
    ui->setupUi(this);
    //ui->demo_widget->setTransformationAnchor(QGraphicsView::AnchorViewCenter);


    m_demo = new RoadIntersectionSimulation(ui->demo_widget);
    m_demo->initialize();
    //ui->demo_widget->centerOn(ui->demo_widget->width()/2,ui->demo_widget->height()/2);
    ui->demo_widget->scale(0.55,0.55);

    //qDebug()<<ui->demo_widget->rect();




}

void HelpWidget::startDemo()
{

    m_demo->startDemo();
}

void HelpWidget::stopDemo()
{
    m_demo->pauseSimulation();
}

HelpWidget::~HelpWidget()
{
    delete ui;
}

void HelpWidget::on_next_button_clicked()
{
    int totalPage = ui->stackedWidget->count();
    int current = ui->stackedWidget->currentIndex();
    if(current == totalPage - 1){
        startDemo();
        ui->stackedWidget->setCurrentIndex(0);
    }else{
        stopDemo();
        ui->stackedWidget->setCurrentIndex(current + 1);
    }
}

void HelpWidget::on_back_button_clicked()
{
    int totalPage = ui->stackedWidget->count();
    int current = ui->stackedWidget->currentIndex();
    if(current - 1 == 0){
        startDemo();
    }else{
        stopDemo();
    }

    if(current == 0){
        ui->stackedWidget->setCurrentIndex(totalPage - 1);
    }else{
        ui->stackedWidget->setCurrentIndex(current - 1);
    }
}

RoadIntersectionSimulation *HelpWidget::demo() const
{
    return m_demo;
}

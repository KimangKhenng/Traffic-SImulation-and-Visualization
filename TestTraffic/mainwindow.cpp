#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lightwidget.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QGraphicsScene *scene = new QGraphicsScene();
    ui->graphicsView->setScene(scene);
    QGraphicsItem *detector = new TrafficDetector(60);
    scene->addItem(detector);
    detector->moveBy(600,600);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

}

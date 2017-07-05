#include "datawidget.h"
#include "ui_datawidget.h"

DataWidget::DataWidget(QWidget *parent) :QWidget(parent),ui(new Ui::DataWidget)
{
    ui->setupUi(this);
    setWindowTitle ("Generated Data");
    setFixedSize (300,200);
}

DataWidget::~DataWidget()
{
    delete ui;
}

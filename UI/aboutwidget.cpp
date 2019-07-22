#include "aboutwidget.h"
#include "ui_aboutwidget.h"
#include <QDesktopServices>
#include <QUrl>
AboutWidget::AboutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutWidget)
{
    ui->setupUi(this);
}

AboutWidget::~AboutWidget()
{
    delete ui;
}

void AboutWidget::on_label_16_linkActivated(const QString &link)
{
    QDesktopServices::openUrl(QUrl(link));
}

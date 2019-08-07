#include "intropage.h"
#include "ui_intropage.h"
#include <QtDebug>
IntroPage::IntroPage(QWidget *parent) :
    QLightBoxWidget(parent),
    ui(new Ui::IntroPage)
{
    ui->setupUi(this);
//    connect(this,&IntroPage::PlayClicked,main,&UIMainWindow::onPlayButtonClicked);
//    connect(this,&IntroPage::HelpClicked,main,&UIMainWindow::onHelpButtonClicked);
//    connect(this,&IntroPage::ExitClicked,main,&UIMainWindow::onExitButtonClicked);
//    connect(this,&IntroPage::AboutClicked,main,&UIMainWindow::onAboutButtonClicked);
    //m_timer = new QTimer;

    //connect(m_timer,&QTimer::timeout,this,&IntroPage::repaintWidget);


}

//void IntroPage::AutoUpdate(const bool &x)
//{
//    if(x){
//        m_timer->start(10);
//    }else{
//        m_timer->stop();
//    }
//}


IntroPage::~IntroPage()
{
    delete ui;
}



void IntroPage::on_m_PlayButton_clicked()
{

    emit PlayClicked();
}

void IntroPage::on_m_ExitButton_clicked()
{
    emit ExitClicked();
}

void IntroPage::on_m_AboutButton_clicked()
{
    //qDebug()<<"Hello";
    emit AboutClicked();
}

void IntroPage::on_m_HelpButton_clicked()
{
    emit HelpClicked();
}

void IntroPage::repaintWidget()
{
    resize(parentWidget()->size());
    repaint();

    //QApplication::processEvents();
    //update();
}

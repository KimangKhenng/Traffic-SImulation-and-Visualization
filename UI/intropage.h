#ifndef INTROPAGE_H
#define INTROPAGE_H

#include "Utilities/qlightboxwidget.h"
#include <QTimer>


namespace Ui {
class IntroPage;
}

class IntroPage : public QLightBoxWidget
{
    Q_OBJECT

public:
    explicit IntroPage( QWidget *parent = 0);
//    void AutoUpdate(const bool& x);
    ~IntroPage();

signals:
    void PlayClicked();
    void ExitClicked();
    void AboutClicked();
    void HelpClicked();

public slots:
    void on_m_PlayButton_clicked();

    void on_m_ExitButton_clicked();

    void on_m_AboutButton_clicked();

    void on_m_HelpButton_clicked();

    void repaintWidget();

private:
    Ui::IntroPage *ui;
    //QTimer *m_timer;
};

#endif // INTROPAGE_H

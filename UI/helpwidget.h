#ifndef HELPWIDGET_H
#define HELPWIDGET_H

#include <QWidget>
#include "Utilities/roadintersectionsimulation.h"
namespace Ui {
class HelpWidget;
}

class HelpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HelpWidget(QWidget *parent = 0);
    void startDemo();
    void stopDemo();
    ~HelpWidget();

    RoadIntersectionSimulation *demo() const;

private slots:
    void on_next_button_clicked();

    void on_back_button_clicked();

private:
    Ui::HelpWidget *ui;
    RoadIntersectionSimulation *m_demo;
};

#endif // HELPWIDGET_H

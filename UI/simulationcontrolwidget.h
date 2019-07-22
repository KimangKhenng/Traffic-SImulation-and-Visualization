#ifndef SIMULATIONCONTROLWIDGET_H
#define SIMULATIONCONTROLWIDGET_H

#include <QWidget>

namespace Ui {
class SimulationControlWidget;
}

class SimulationControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControlWidget(QWidget *parent = 0);
    ~SimulationControlWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SimulationControlWidget *ui;
};

#endif // SIMULATIONCONTROLWIDGET_H

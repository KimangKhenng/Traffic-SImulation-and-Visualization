#ifndef SIMULATIONCONTROL_H
#define SIMULATIONCONTROL_H

#include <QWidget>

namespace Ui {
class SimulationControl;
}

class SimulationControl : public QWidget
{
    Q_OBJECT

public:
    explicit SimulationControl(QWidget *parent = 0);
    ~SimulationControl();

private:
    Ui::SimulationControl *ui;
};

#endif // SIMULATIONCONTROL_H

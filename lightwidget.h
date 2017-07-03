#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QtWidgets>

class LightWidget :public QWidget
{
    Q_OBJECT
    Q_PROPERTY(bool on READ isOn WRITE setOn)
public:
    LightWidget(const QColor &color, QWidget *parent = 0);
    bool isOn() const;
    void setOn(bool on);
public slots:
public slots:
    void turnOff();
    void turnOn();
protected:
    virtual void paintEvent(QPaintEvent *) Q_DECL_OVERRIDE;
private:
    QColor m_color;
    bool m_on;
};

#endif // LIGHTWIDGET_H

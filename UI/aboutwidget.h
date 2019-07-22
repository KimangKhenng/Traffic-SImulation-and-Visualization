#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

namespace Ui {
class AboutWidget;
}

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = 0);
    ~AboutWidget();

private slots:
    void on_label_16_linkActivated(const QString &link);

private:
    Ui::AboutWidget *ui;
};

#endif // ABOUTWIDGET_H

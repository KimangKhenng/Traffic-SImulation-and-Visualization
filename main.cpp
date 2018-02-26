#include "mainwindow.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

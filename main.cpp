#include "UI/mainwindow.h"
#include <QTime>
#include <QApplication>
#include "UI/uimainwindow.h"

int main(int argc, char *argv[])
{
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));

    QApplication a(argc, argv);
    //MainWindow w;
    UIMainWindow ww;
    ww.show();
    //w.show();
    return a.exec();
}

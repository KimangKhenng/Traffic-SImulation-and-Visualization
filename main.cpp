#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Intersection Road Simulation and Visualization");
    w.show();
    return a.exec();
}

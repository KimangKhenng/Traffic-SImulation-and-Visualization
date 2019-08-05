#include "UI/mainwindow.h"
#include <QTime>
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "UI/uimainwindow.h"

int main(int argc, char *argv[])
{
    qsrand(static_cast<uint>(QTime(0,0,0).secsTo(QTime::currentTime())));

    QApplication a(argc, argv);

    UIMainWindow ww;
    ww.show();

    return a.exec();
}

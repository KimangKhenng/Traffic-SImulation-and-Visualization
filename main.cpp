#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "UI/uimainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    UIMainWindow windows;
    windows.show();
    return app.exec();
}

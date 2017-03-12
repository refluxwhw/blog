#include "mainwindow.h"
#include <QApplication>
#include "dumphelper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DumpHelper::getInst().init();

    MainWindow w;
    w.show();


    return a.exec();
}

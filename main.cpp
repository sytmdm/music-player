#include "mainwindow.h"
#include"onlineplayer.h"
#include <QApplication>
#include"musicmenu.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
//    musicMenu m;
//    m.show();
//    onLinePlayer w;
    return a.exec();
}

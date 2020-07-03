#include "orderform.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>
/*
The implementation is terrible, I want to seperate STD and QT
However, have to do lots of mess to get it work.
Since need this to roll over contract, get it work first.
Need to revise later
*/
int main(int argc, char *argv[])
{
    QString path = QDir::currentPath();
    QApplication::addLibraryPath(path+QString("/plugins"));
    QPluginLoader loader(path+QString("/plugins/sqldrivers/qsqlite4.dll"));
    QApplication a(argc, argv);
    OrderForm w;
    w.show();
    return a.exec();
}

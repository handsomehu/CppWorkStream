#include "orderform.h"

#include <QApplication>
#include <QDir>
#include <QPluginLoader>
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

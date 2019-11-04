#include "orderform.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    OrderForm w;
    w.show();
    return a.exec();
}

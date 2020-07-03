#ifndef TDTHREAD_H
#define TDTHREAD_H
#include <QThread>
#include "qtd.h"
class TdThread: public QThread
{
    Q_OBJECT
public:
    QTd* td;
    TdThread(QObject *parent);
    void run();
    void dowork();
    //void readcfg();
private:

    //QString cfgdata;
};

#endif // TDTHREAD_H

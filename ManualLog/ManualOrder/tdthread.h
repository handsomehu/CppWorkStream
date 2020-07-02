#ifndef TDTHREAD_H
#define TDTHREAD_H
#include <QThread>
#include "qtd.h"
class TdThread: public QThread
{
    Q_OBJECT
public:
    TdThread(QObject *parent);
    void run();
    void readcfg();

private:
    QTd trade;
    QString cfgdata;
};

#endif // TDTHREAD_H

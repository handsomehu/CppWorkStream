#ifndef TDTHREAD_H
#define TDTHREAD_H
#include <QThread>
#include "qtd.h"
class TdThread: public QObject,public QThread
{
    Q_OBJECT
public:
    TdThread(TdThread(QObject *parent));
};

#endif // TDTHREAD_H

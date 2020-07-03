#ifndef QTD_H
#define QTD_H
#include <QObject>
#include <QDebug>
#include <QString>
#include "tradewrapper.h"

class QTd: public QObject , public TradeWrapper
{
    Q_OBJECT
public:
    QTd(QObject *parent, const std::string &path);
    CThostFtdcOrderField* FwdOrdResp();
    bool HasWork();

signals:
    void sendWT(QString);
};

#endif // QTD_H

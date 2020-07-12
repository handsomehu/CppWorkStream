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
    std::shared_ptr<CThostFtdcOrderField> FwdOrdResp();
    std::shared_ptr<CThostFtdcTradeField> FwdTraResp();
    bool HasOrder();
    bool HasTrade();
    void testsig();
    void ReqCancelOrder(QString wth, QString exchg);

signals:
    void sendWT(QString);
    void sendCJ(QString);

};

#endif // QTD_H

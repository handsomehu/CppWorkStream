#include "qtd.h"

QTd::QTd(QObject *parent,const std::string &path) : QObject(parent), TradeWrapper(path)
{

}

void QTd::testsig()
{
    qDebug() << "aBefore get order return!" ;
    emit sendWT(QString("test sig,a,b,c,d,e,f,g,h,i"));
    qDebug() << "bBefore get order return!" ;
}
std::shared_ptr<CThostFtdcOrderField> QTd::FwdOrdResp()
{
    qDebug() << "Before get order return!" ;
    std::shared_ptr<CThostFtdcOrderField> pOrder =  GetOrderRet();
    return pOrder;
}


std::shared_ptr<CThostFtdcTradeField> QTd::FwdTraResp()
{
    qDebug() << "Before get trade return!" ;
    std::shared_ptr<CThostFtdcTradeField> pTrade =  GetTradeRet();
    return pTrade;
}


bool QTd::HasOrder()
{
    bool haswork = 0;

    if (HasOrderRet())
        haswork = 1;
    return haswork;

}

bool QTd::HasTrade()
{
    bool haswork = 0;

    if (HasTradeRet())
        haswork = 1;
    return haswork;

}

void QTd::ReqCancelOrder(QString wth, QString exchg)
{
    std::string stdwt = wth.toStdString();
    std::string stdexch = exchg.toStdString();
    int iResult = CancelOrder(stdwt, stdexch);
    qDebug() << "Cancel Order Return val:" << iResult;

}

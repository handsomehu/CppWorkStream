#include "qtd.h"

QTd::QTd(QObject *parent,const std::string &path) : QObject(parent), TradeWrapper(path)
{

}

CThostFtdcOrderField* QTd::FwdOrdResp()
{
    qDebug() << "Before get order return!" ;
    CThostFtdcOrderField* pOrder =  GetOrderRet();
    //报单状态处理
    QString zt;
    if (pOrder->OrderStatus=THOST_FTDC_OST_AllTraded)
    {
        zt=QString::fromLocal8Bit("全部成交");
    }else if(THOST_FTDC_OST_PartTradedQueueing)
    {
        zt=QString::fromLocal8Bit("部分成交");
    }
    else if (pOrder->OrderStatus=THOST_FTDC_OST_PartTradedNotQueueing)
    {
        zt=QString::fromLocal8Bit("部分成交");
    }
    else if (pOrder->OrderStatus=THOST_FTDC_OST_NoTradeQueueing)
    {
        zt=QString::fromLocal8Bit("未成交");
    }
    else if (pOrder->OrderStatus=THOST_FTDC_OST_Canceled)
    {
        zt=QString::fromLocal8Bit("已撤单");
    }


      QString wttime = pOrder->InsertTime; //委托时间
      QString dm = pOrder->InstrumentID; //委托代码
      QString bs = QChar::fromLatin1(pOrder->Direction); //买卖方向
      QString kp=pOrder->CombOffsetFlag; //开平标志
      QString lots = QString::number(pOrder->VolumeTotalOriginal); //数量
      QString price = QString::number(pOrder->LimitPrice); //价格
      //QString zt=pOrder->OrderStatus; //报单状态
      QString wth = pOrder->OrderSysID; //委托号
      QString jsy=pOrder->ExchangeID; //交易所

      QString WTData=wttime+","+dm+","+bs+","+kp+","+lots+","+lots+","+price+","+zt+","+wth+","+jsy;
      qDebug() << WTData;

      emit sendWT(WTData);
      qDebug() << "emit signals";
}

bool QTd::HasWork()
{
    bool haswork = 0;

    if (HasOrderRet() == 1)
        haswork = 1;
    return haswork;

}

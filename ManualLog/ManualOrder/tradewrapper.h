#ifndef TRADEWRAPPER_H
#define TRADEWRAPPER_H
#include "./libhead/ThostFtdcTraderApi.h"
//#include "traderApi.h"
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <memory>
#include <queue>
#include <chrono>
#include <thread>
#include <iostream>
#include "./libhead/json.hpp"
#include <fstream>

void NewTradeEvent();
class TradeWrapper: public CThostFtdcTraderSpi
{
public:

    TradeWrapper(const std::string &path);
    virtual ~TradeWrapper(){ release();}
    void ReadUserData();
    //activat method
    void connectCtp();
    int ReqAuthenticate();
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    int ReqUserLogin();
    void release();
    void login();
    void settlementinfoConfirm();
    void orderinsert( std::string symbol, std::string dir, std::string kp, std::string exchange,double price, int vol,int reqid);
    void qryInstrument();
    bool is_connected();
    bool is_goodorder();
    void reset_goodorder();
    CThostFtdcOrderField* GetOrderRet();
    bool HasOrderRet();
    //responsive method
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnOrder(CThostFtdcOrderField *pOrder);
    void OnRtnTrade(CThostFtdcTradeField *pTrade);
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo) ;


private:

    // could use smart point replace
    // How the api instance the class? via stack or new?
    CThostFtdcTraderApi *m_ptraderapi;
    std::string cfgpath;
    std::string brokerid,mdaddress,tdaddress,
    userid, password, appid,authcode;
    std::ifstream jfile;
    bool isconnected;
    bool goodorder;
    std::queue<CThostFtdcOrderField*> orderresp;


};


#endif // TRADEWRAPPER_H

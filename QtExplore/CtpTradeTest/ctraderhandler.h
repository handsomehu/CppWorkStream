#ifndef CTRADERHANDLER_H
#define CTRADERHANDLER_H
#include "./libhead/ThostFtdcTraderApi.h"
//#include "traderApi.h"
#include <string.h>
#include <cstring>
#include <stdio.h>
#include <memory>
#include <chrono>
#include <thread>
#include <iostream>
//#include <Windows.h>

class CTraderHandler: public CThostFtdcTraderSpi
{
public:

    CTraderHandler();
    //activat method
    void connect();
    int ReqAuthenticate();
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    int ReqUserLogin();
    void release();
    void login();
    void settlementinfoConfirm();
    void orderinsert();
    void qryInstrument();
    //responsive method
    void OnFrontConnected();
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRtnOrder(CThostFtdcOrderField *pOrder);
    void OnRtnTrade(CThostFtdcTradeField *pTrade);
    void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);


private:

    // could use smart point replace
    // How the api instance the class? via stack or new?
    CThostFtdcTraderApi *m_ptraderapi;


};

#endif // CTRADERHANDLER_H

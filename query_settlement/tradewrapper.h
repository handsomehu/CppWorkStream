#ifndef TRADEWRAPPER_H
#define TRADEWRAPPER_H
#include "./libhead/ThostFtdcTraderApi.h"
//#include "traderApi.h"
#include <string.h>
#include <cstring>
#include <stdlib.h>
#include <stdio.h>
#include <iconv.h>
#include <memory>
#include <chrono>
#include <array>
#include <thread>
#include <iostream>
#include <wchar.h>
#include "./libhead/json.hpp"
#include <fstream>

void NewTradeEvent();


int GbkToUtf8(char *str_str, size_t src_len, char *dst_str, size_t dst_len);
int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len);


//TThostFtdcContentType
class TradeWrapper: public CThostFtdcTraderSpi
{
public:

    TradeWrapper(const std::string &path);
    virtual ~TradeWrapper(){ release();}
    void ReadUserData();
    //activat method
    void connect();
    int ReqAuthenticate();
    void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    int ReqUserLogin();
    void release();
    void login();
    void settlementinfoConfirm();
    void orderinsert( std::string symbol, std::string dir, std::string kp, std::string exchange,double price, int vol,int reqid);
    void qryInstrument();
    void qrySettlement(std::string tradedate);
    bool is_connected();
    bool is_goodorder();
    void reset_goodorder();
    wchar_t* MBCS2Unicode(wchar_t* buff, const char* str);
    std::vector<std::vector<char*>> getsettlements() ;
    //responsive method
    void OnFrontConnected();
    void OnFrontDisconnected(int nReason);
    void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    void OnRspQrySettlementInfo(CThostFtdcSettlementInfoField *pSettlementInfo, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
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
    std::vector<std::string> oneday;
    std::vector<std::vector<std::string>> alldays;
    std::vector<char*> pconeday;
    std::vector<std::vector<char*>> pcalldays;
};


#endif // TRADEWRAPPER_H

/*
 * mdWrapper.h
 *
 *  Created on: Aug 10, 2019
 *      Author: leon
 */
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <unordered_map>
#include <future>
#include "./libhead/ThostFtdcMdApi.h"
#include "./libhead/json.hpp"
//#include "./libhead/nlohmann/json.hpp"

#ifndef SRC_MDWRAPPER_H_
#define SRC_MDWRAPPER_H_

struct thevwap
{
    double avgprice;
    int vol;
};
class CmdWrapper : public CThostFtdcMdSpi{
private:
    CThostFtdcMdApi *m_mdApi = nullptr;
    double curPrice = 0;
    int curVolumn = 0;
    int totalvol = 0;
    double avgprice = 0;
    thevwap lastvwap;
    thevwap newvwap;
    std::unordered_map<std::string,thevwap> vwaps;
    bool loginstatus = false;
    std::mutex              g_lockprint;
    std::mutex              g_lockqueue;
    std::condition_variable g_queuecheck;
    std::queue<CThostFtdcDepthMarketDataField> g_tasks;
    bool                    g_done = false;
    bool                    g_notified;
    bool                    g_setcomplete = false;
public:
	CmdWrapper();
	virtual ~CmdWrapper();
	void getavg();
	void persistvwap();
	void connect();
	bool getloginstatus();
	int apijoin();
	void apirelease();
	///客户端认证请求
	//virtual int ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID) = 0;
	///客户端认证响应
	//virtual void OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;
	int ReqUserLogin();
	void subscribe(std::vector<char*>symbols);
	///当客户端与交易后台建立起通信连接时（还未登录前），该方法被调用。
	virtual void OnFrontConnected();

	///当客户端与交易后台通信连接断开时，该方法被调用。当发生这个情况后，API会自动重新连接，客户端可不做处理。
	///@param nReason 错误原因
	///        0x1001 网络读失败
	///        0x1002 网络写失败
	///        0x2001 接收心跳超时
	///        0x2002 发送心跳失败
	///        0x2003 收到错误报文
	virtual void OnFrontDisconnected(int nReason){};

	///心跳超时警告。当长时间未收到报文时，该方法被调用。
	///@param nTimeLapse 距离上次接收报文的时间
	virtual void OnHeartBeatWarning(int nTimeLapse){};


	///登录请求响应
	virtual void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) ;

	///登出请求响应
	virtual void OnRspUserLogout(CThostFtdcUserLogoutField *pUserLogout, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///错误应答
	virtual void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅行情应答
	virtual void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///取消订阅行情应答
	virtual void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///订阅询价应答
	virtual void OnRspSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///取消订阅询价应答
	virtual void OnRspUnSubForQuoteRsp(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) {};

	///深度行情通知
	virtual void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

	///询价通知
	virtual void OnRtnForQuoteRsp(CThostFtdcForQuoteRspField *pForQuoteRsp) {};
	void SaveTaskToQueue(CThostFtdcDepthMarketDataField pDepthMarketData);
	void ProcessTaskFromQueue(std::future<void> futureObj);
	void SetComplete();
	void UpdateVwap(std::string inID,double price, int vol);
};

#endif /* SRC_MDWRAPPER_H_ */

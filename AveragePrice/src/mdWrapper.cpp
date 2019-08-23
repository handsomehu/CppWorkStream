/*
 * mdWrapper.cpp
 *
 *  Created on: Aug 10, 2019
 *      Author: leon
 */

#include "mdWrapper.h"

CmdWrapper::CmdWrapper() {
	// TODO Auto-generated constructor stub

}

CmdWrapper::~CmdWrapper() {
	// TODO Auto-generated destructor stub
}


void CmdWrapper::connect(){
	m_mdApi = CThostFtdcMdApi::CreateFtdcMdApi(".//temp_md/", true, true);
	m_mdApi->RegisterSpi(this);
	char* pstr = (char*)"tcp://180.168.146.187:10131";
	m_mdApi->RegisterFront(pstr);
	m_mdApi->Init();

}
bool CmdWrapper::getloginstatus()
{
	return loginstatus;
}
int CmdWrapper::apijoin()
{
	if (m_mdApi != nullptr)
		return m_mdApi->Join();
	else
		return 0;
}

void CmdWrapper::apirelease()
{
	if (m_mdApi != nullptr)
		m_mdApi->Release();

}
/*
int CmdWrapper::ReqAuthenticate(CThostFtdcReqAuthenticateField *pReqAuthenticateField, int nRequestID)
{
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    strcpy(field.BrokerID, "9999");
    strcpy(field.UserID, "118907");
    strcpy(field.AppID, "simnow_client_test");
    strcpy(field.AuthCode, "0000000000000000");
    if (m_mdApi != nullptr)
    	return m_mdApi->ReqAuthenticate(&field, 5);
    else
		return 1;
}
*/
void CmdWrapper::OnFrontConnected()
{

	std::cout << "=====Server Connected=====" << std::endl;
	// Start to Auth

    std::cout << "OnFrontConnected." << std::endl;
    if (m_mdApi != nullptr)
    {
    	static const char *version = m_mdApi->GetApiVersion();
    	std::cout << "------Current Version：" << version << " ------" << std::endl;
    	static int cnt = 0;
    	while(cnt < 5)
    	{
    		if (ReqUserLogin() != 0)
    		{
    			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    			cnt++;
    		}
    		else
    		{
    			loginstatus = true;
    			cnt = 5; //exit the loop
    		}



    	}

    }

}

/*

void CmdWrapper::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    std::cout <<"OnRspAuthenticate\n" << endl;
    if (pRspInfo != NULL && pRspInfo->ErrorID == 0)
    {
    	std::cout <<"认证成功,ErrMsg=" << pRspInfo->ErrorMsg << std::endl;
        ReqUserLogin();
    }
    else
    cout << "认证失败，" << "ErrorID=" << pRspInfo->ErrorID << "  ,ErrMsg=" << pRspInfo->ErrorMsg << endl;
}
*/
int CmdWrapper::ReqUserLogin()
{
    std::cout <<"====ReqUserLogin====,用户登录中...\n\n"<< std::endl;
    CThostFtdcReqUserLoginField reqUserLogin;
    memset(&reqUserLogin, 0, sizeof(reqUserLogin));
    strcpy(reqUserLogin.BrokerID, "9999");
    strcpy(reqUserLogin.UserID, "118907");
    strcpy(reqUserLogin.Password, "");
    //strcpy(reqUserLogin.TradingDay, "20190813");
    static int requestID = 0; // 请求编号
    static int rt;
	if (m_mdApi != nullptr)
		rt = m_mdApi->ReqUserLogin(&reqUserLogin, ++requestID);
	if (!rt)
		std::cout << ">>>>>>发送登录请求成功" << std::endl;
	else
		std::cerr << "--->>>发送登录请求失败" << std::endl;
    return rt;
	//return m_pUserApi->ReqUserLogin(&reqUserLogin, ++RequestID);
}

void CmdWrapper::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
//订阅行情

void CmdWrapper::subscribe(std::vector<char*>symbols)
{
	static int symbolcnt = symbols.size();
	if (m_mdApi != nullptr)
	{
		while (m_mdApi->SubscribeMarketData(symbols.data(), symbolcnt)!=0)
			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}
void CmdWrapper::SaveTaskToQueue(CThostFtdcDepthMarketDataField pDepthMarketData)
{
    std::unique_lock<std::mutex> locker(g_lockqueue);
    g_tasks.push(pDepthMarketData);
    g_notified = true;
    // may be a little beteer to unlock the object before notify
    //since it is still lock when notify.
    locker.unlock();
    g_queuecheck.notify_one();
}
void CmdWrapper::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	SaveTaskToQueue(*pDepthMarketData);
	//std::cout <<  pDepthMarketData->InstrumentID <<"\t" << std::setprecision(8) << pDepthMarketData->ClosePrice <<"\t" << pDepthMarketData->UpdateTime <<"\t" <<pDepthMarketData->Volume  << std::endl;
}

///订阅行情应答
void CmdWrapper::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo->ErrorID  == 0)
    {
    	//SaveTaskToqueue(*pDepthMarketData);
    	std::cout <<  "Subscribe Instrument:" << pSpecificInstrument->InstrumentID << "succeed!" <<std::endl;
    }
}


void CmdWrapper::ProcessTaskFromQueue()
{
	CThostFtdcDepthMarketDataField content;
    while(!g_done)
    {
        std::unique_lock<std::mutex> locker(g_lockqueue);

        g_queuecheck.wait(locker, [&](){return !g_tasks.empty();});

        // if there are error codes in the queue process them
        while(!g_tasks.empty())
        {
            content = g_tasks.front();
            g_tasks.pop();
            //the cout is expensive, so I unlock first
            locker.unlock();
            std::cout <<  "Pop queue:\t"  <<content.InstrumentID << "\t"  << std::setprecision(8) << content.ClosePrice <<"\t" << content.UpdateTime <<"\t" <<content.Volume  << std::endl;
        }
    }
}

void CmdWrapper::SetComplete()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000*60));
	g_done = true;
}

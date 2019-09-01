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

	m_mdApi = CThostFtdcMdApi::CreateFtdcMdApi("./temp_md", true, true);
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
		newvwap.avgprice = 0;
		newvwap.vol =0 ;
		for (char* v:symbols)
			vwaps[v] = newvwap;
	}
}
void CmdWrapper::SaveTaskToQueue(CThostFtdcDepthMarketDataField pDepthMarketData)
{
    std::unique_lock<std::mutex> locker(g_lockqueue);
    //locker.lock();
    g_tasks.push(pDepthMarketData);

    // may be a little beteer to unlock the object before notify
    //since it is still lock when notify.
    locker.unlock();
    g_queuecheck.notify_one();
    g_notified = true;
    //std::cout << pDepthMarketData.InstrumentID << std::endl;
}
void CmdWrapper::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
	SaveTaskToQueue(*pDepthMarketData);

	//std::cout <<  pDepthMarketData->InstrumentID << std::endl;
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
        //while(!g_tasks.empty())
        //std::cout << g_tasks.size();
        	//locker.lock();
            content = g_tasks.front();
            g_tasks.pop();
            //the cout is expensive, so I unlock first
            totalvol = content.Volume;
            curPrice = content.LastPrice;
            UpdateVwap(content.InstrumentID ,curPrice,totalvol);
            locker.unlock();
            //std::cout << g_tasks.size();
            //std::cout << "ttt" << std::endl;
            //std::cout <<  "Pop queue:\t"  << content.InstrumentID << std::endl;
            //std::cout <<  "Pop queue:\t"  <<content.InstrumentID << "\t"  << std::setprecision(8) << content.ClosePrice <<"\t" << content.UpdateTime <<"\t" <<content.Volume  << std::endl;
        //}
    }

}
void CmdWrapper::persistvwap()
{

	//nlohmann::json myj;
	std::unordered_map<std::string,thevwap>::iterator iter;
	int repeattime = 10;
	while (repeattime > 0)
	{
		--repeattime;
		std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	    for (iter = vwaps.begin(); iter != vwaps.end(); ++iter)
	    	{
	    		newvwap = iter->second;
	    		std::cout << "(" << iter->first << ", " << newvwap.avgprice << ")" << " "<<std::endl;
	    	}

	}
}

void CmdWrapper::getavg()
{
	std::cout << avgprice << std::endl;
}
void CmdWrapper::UpdateVwap(std::string inID, double curprice, int curvol)
{

		//totalvol = vwap.at(inID)
		//std::cout << "test " << std::endl;
		lastvwap = vwaps[inID];
		std::cout << "before update" <<lastvwap.avgprice << std::endl;
		if (lastvwap.avgprice != 0)
		{

			avgprice = lastvwap.avgprice + curprice *curvol;
			totalvol = totalvol + lastvwap.vol;
			avgprice = avgprice / totalvol;
			lastvwap.avgprice = avgprice;
			lastvwap.vol = totalvol;
		}
		else
		{
			lastvwap.avgprice = curprice;
			lastvwap.vol = curvol;
		}
		//vwaps.at(inID) = avgprice;
		//std::cout << "test1 " << std::endl;
		vwaps[inID] = lastvwap;
		std::cout << "after update" << lastvwap.avgprice  << std::endl;
		//std::cout << "test2 " << std::endl;
		//std::cout << inID << "\t" << avgprice << std::endl;

}
void CmdWrapper::SetComplete()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000*60*20));
	g_done = true;
}

#include "tradewrapper.h"

void NewTradeEvent()
{

}

TradeWrapper::TradeWrapper(const std::string &path):
  m_ptraderapi(nullptr),
  cfgpath(path), brokerid(""),mdaddress(""),tdaddress(""),
  userid(""), password(""), appid(""),authcode(""),
  jfile(path),isconnected(false),goodorder(false),orderresp{},
  iRequestTdID{0}

{
    nlohmann::json j;
    std::cout << "before json";
    if (jfile)
    {
        jfile >> j;
        if (j.find("brokerID") != j.end())
          brokerid = j["brokerID"];
        if (j.find("mdAddress") != j.end())
          mdaddress = j["mdAddress"];
        if (j.find("tdAddress") != j.end())
          tdaddress = j["tdAddress"];
        if (j.find("userID") != j.end())
          userid = j["userID"];
        if (j.find("password") != j.end())
          password = j["password"];
        if (j.find("appID") != j.end())
          appid = j["appID"];
        if (j.find("authCode") != j.end())
          authcode = j["authCode"];
        std::cout << "test constructor";

    }
}
void TradeWrapper::ReadUserData()
{

}
int TradeWrapper::CancelOrder(std::string orderid, std::string exchangeid)
{
    CThostFtdcInputOrderActionField req;
    memset(&req, 0, sizeof(req));

    char bufstr[100];

    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(req.BrokerID, bufstr);

    std::copy(orderid.begin(),orderid.end(),bufstr);
    bufstr[orderid.size()] = '\0';
    std::strcpy(req.OrderSysID, bufstr);

    std::copy(exchangeid.begin(),exchangeid.end(),bufstr);
    bufstr[exchangeid.size()] = '\0';
    std::strcpy(req.ExchangeID, bufstr);

    ///操作标志
    req.ActionFlag = THOST_FTDC_AF_Delete;
    int iResult = m_ptraderapi->ReqOrderAction(&req, ++iRequestTdID);
    return iResult;

}
void TradeWrapper::connectCtp()
{
    //创建API实例
    std::cout << "start connect!";
    m_ptraderapi = CThostFtdcTraderApi::CreateFtdcTraderApi(".//flow/");
    //必须提前创建好flow目录，流文件*.con就会在该文件夹下面创建，如果想要区别不同session创建的流水文件名称可见如下示例“.//flow/a_”

    m_ptraderapi->RegisterSpi(this);

    m_ptraderapi->SubscribePublicTopic(THOST_TERT_QUICK);

    m_ptraderapi->SubscribePrivateTopic(THOST_TERT_QUICK); //设置私有流订阅模式
    char tdads[tdaddress.size()+1];
    std::copy(tdaddress.begin(),tdaddress.end(),tdads);
    tdads[tdaddress.size()] = '\0';
    std::cout << "\ntestit" << tdaddress <<  tdads << std::endl;
    m_ptraderapi->RegisterFront(tdads);

    m_ptraderapi->Init();

    //输出API版本信息

    printf("%s\n", m_ptraderapi->GetApiVersion());


}

bool TradeWrapper::HasOrderRet()
{
    if (orderresp.empty())
        return false;
    else
        return true;
}

bool TradeWrapper::HasTradeRet()
{
    if (traderesp.empty())
        return false;
    else
        return true;
}

bool TradeWrapper::is_goodorder()
{
    return goodorder;
}
void TradeWrapper::reset_goodorder()
{
    //std::this_thread::sleep_for(std::chrono::seconds(120));
    goodorder = false;
}
//前置连接响应

void TradeWrapper::OnFrontConnected()

{

    printf("OnFrontConnected\n");
    ReqAuthenticate();

}

int TradeWrapper::ReqAuthenticate()
{
    //try something danngerous, cause I do not want to create
    // so many variable
    char bufstr[100];
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(field.BrokerID, bufstr);
    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(field.UserID, bufstr);
    std::copy(appid.begin(),appid.end(),bufstr);
    bufstr[appid.size()] = '\0';
    std::strcpy(field.AppID, bufstr);
    std::copy(authcode.begin(),authcode.end(),bufstr);
    bufstr[authcode.size()] = '\0';
    std::strcpy(field.AuthCode, bufstr);
    return m_ptraderapi->ReqAuthenticate(&field, 5);

}
void TradeWrapper::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    printf("OnRspAuthenticate\n");
    if (pRspInfo != NULL && pRspInfo->ErrorID == 0)
    {
        printf("认证成功,ErrorID=0x%04x, ErrMsg=%s\n\n", pRspInfo->ErrorID, pRspInfo->ErrorMsg);
        ReqUserLogin();
    }
    else
    std::cout << "认证失败，" << "ErrorID=" << pRspInfo->ErrorID << "  ,ErrMsg=" << pRspInfo->ErrorMsg << std::endl;

}

int TradeWrapper::ReqUserLogin()
{
    //try something danngerous, cause I do not want to create
    // so many variable
    char bufstr[100];
    char *tradingday = "20191111";

    printf("====ReqUserLogin====,用户登录中...\n\n");
    CThostFtdcReqUserLoginField reqUserLogin;
    memset(&reqUserLogin, 0, sizeof(reqUserLogin));

    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(reqUserLogin.BrokerID, bufstr);
    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(reqUserLogin.UserID, bufstr);
    std::copy(password.begin(),password.end(),bufstr);
    bufstr[password.size()] = '\0';
    std::strcpy(reqUserLogin.Password, bufstr);
    //std::copy(tradingday.begin(),tradingday.end(),bufstr);
    //bufstr[tradingday.size()] = '\0';
    std::strcpy(reqUserLogin.TradingDay, tradingday);

    static int RequestID = 0;
    return m_ptraderapi->ReqUserLogin(&reqUserLogin, ++RequestID);
}
void TradeWrapper::release()
{
    m_ptraderapi->Release();
}

void TradeWrapper::login()
{
    char bufstr[100];
    char *tradingday = "20191111";

    CThostFtdcReqUserLoginField t = {0};


    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(t.BrokerID, bufstr);

    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(t.UserID, bufstr);

    std::copy(password.begin(),password.end(),bufstr);
    bufstr[password.size()] = '\0';
    std::strcpy(t.Password, bufstr);
    //std::copy(tradingday.begin(),tradingday.end(),bufstr);
    //bufstr[tradingday.size()] = '\0';
    std::strcpy(t.TradingDay, tradingday);

    while (m_ptraderapi->ReqUserLogin(&t, 1)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);
}

//结算单确认

void TradeWrapper::settlementinfoConfirm()

{

    CThostFtdcSettlementInfoConfirmField t = {0};

    char bufstr[100];
    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(t.BrokerID, bufstr);

    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(t.InvestorID, bufstr);

    while (m_ptraderapi->ReqSettlementInfoConfirm(&t, 2)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}



//报单

void TradeWrapper::orderinsert( std::string symbol,std::string dir, std::string kp, std::string exchange,double price, int vol,int reqid)

{

    CThostFtdcInputOrderField t = { 0 };

    char bufstr[100];
    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    std::strcpy(t.BrokerID, bufstr);

    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(t.InvestorID, bufstr);
    std::strcpy(t.UserID, bufstr);

    if (dir=="多")
        t.Direction = THOST_FTDC_D_Buy;
    else
        t.Direction = THOST_FTDC_D_Sell;

    if (kp == "开仓")
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Open;
    else if (kp == "平仓")
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Close;
    else if (kp == "平昨")

        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseYesterday;
    else if (kp == "平今")
        t.CombOffsetFlag[0] = THOST_FTDC_OF_CloseToday;
    else
        t.CombOffsetFlag[0] = THOST_FTDC_OF_Close;

    //t.CombOffsetFlag[0] = THOST_FTDC_OF_Open;

    t.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

    t.ContingentCondition = THOST_FTDC_CC_Immediately;
    std::copy(symbol.begin(),symbol.end(),bufstr);
    bufstr[symbol.size()] = '\0';

    std::strcpy(t.InstrumentID, bufstr);

    t.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

    t.LimitPrice =  price;

    t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;

    t.VolumeCondition = THOST_FTDC_VC_AV;

    t.TimeCondition = THOST_FTDC_TC_GFD;

    t.VolumeTotalOriginal = vol;

    //std::strcpy(t.OrderRef, "0000001");


    if (exchange ==  "SHFE")
        std::strcpy(t.ExchangeID, "SHFE");
    if (exchange == "CZCE")
        std::strcpy(t.ExchangeID, "CZCE");
    if  (exchange == "DCE")
        std::strcpy(t.ExchangeID, "DCE");
    if  (exchange == "CFFEX")
        std::strcpy(t.ExchangeID, "CFFEX");
    if  (exchange == "INE")
        std::strcpy(t.ExchangeID, "INE");
    //static int reqid = 200;
    m_ptraderapi->ReqOrderInsert(&t, reqid);
    std::this_thread::sleep_for(std::chrono::seconds(1));
    return; //submit order and return, deal order status later
    while (m_ptraderapi->ReqOrderInsert(&t, reqid) != 0)
    {std::this_thread::sleep_for(std::chrono::seconds(1));
    std::cout << "wait to commit" << std::endl;
    }//Sleep(1000);
    std::cout << "commited" << std::endl;

}

//查询合约

void TradeWrapper::qryInstrument()

{

    CThostFtdcQryInstrumentField t = { 0 };

    std::strcpy(t.ExchangeID, "CFFEX");

    std::strcpy(t.InstrumentID, "T1912");

    while (m_ptraderapi->ReqQryInstrument(&t, 4) != 0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}







//登陆请求响应

void TradeWrapper::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspUserLogin\n");
    isconnected = true;
    std::cout << pRspInfo->ErrorMsg << std::endl;
    std::cout << pRspInfo->ErrorID << std::endl;

}
bool TradeWrapper::is_connected()
{
    return isconnected;
}
void TradeWrapper::OnFrontDisconnected(int nReason)
{
    //isconnected = false;
    std::cout << "disconnected!";
}

//结算单确认响应

void TradeWrapper::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspSettlementInfoConfirm\n");
    //if (pRspInfo->
    std::cout << std::string(pRspInfo->ErrorMsg) << std::endl;
    //std::cout << pRspInfo-> << std::endl;

}



//查询合约响应

void TradeWrapper::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspQryInstrument\n");
    std::cout << pInstrument->InstrumentID << std::endl;
}


//报单通知

void TradeWrapper::OnRtnOrder(CThostFtdcOrderField *pOrder)

{

    printf("OnRtnOrder\n");
    std::cout << pOrder->InstrumentID << "\t" << pOrder->OrderStatus << std::endl;
    std::shared_ptr<CThostFtdcOrderField> p = std::make_shared<CThostFtdcOrderField>(*pOrder);
    orderresp.push(p);

}


std::shared_ptr<CThostFtdcOrderField> TradeWrapper::GetOrderRet()
{

    if (!orderresp.empty())
    {
        std::shared_ptr<CThostFtdcOrderField> rsp = orderresp.front();
        orderresp.pop();
        return rsp;
    }
    else
        return nullptr;
}

//成交通知

void TradeWrapper::OnRtnTrade(CThostFtdcTradeField *pTrade)

{

    printf("OnRtnTrade\n");
    if (pTrade)
    {printf("not null\n");printf("%s, %d\n",pTrade->InstrumentID,pTrade->Volume);}
    else
        printf("nullptr\n");
    std::cout << pTrade->InstrumentID << "\t"  << std::endl;
    std::cout << "trade no:" << pTrade->Volume << "\t"  << std::endl;
    std::shared_ptr<CThostFtdcTradeField> p = std::make_shared<CThostFtdcTradeField>(*pTrade);
    traderesp.push(p);

}

std::shared_ptr<CThostFtdcTradeField> TradeWrapper::GetTradeRet()
{

    if (!traderesp.empty())
    {
        std::shared_ptr<CThostFtdcTradeField> rsp = traderesp.front();
        traderesp.pop();
        return rsp;
    }
    else
        return nullptr;
}

//报单录入请求响应

void TradeWrapper::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspOrderInsert\n");

}



//错误应答

void TradeWrapper::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspError\n");
    std::vector<int> errcode = {15,22,23,24,27,28,29,30,31,32,33,50,51,78,79,80};
    for(auto err:errcode)
    {
        if(err == pRspInfo->ErrorID)
        {

            reset_goodorder();
            break;
        }
    }

}

void TradeWrapper::OnRtnTradingNotice(CThostFtdcTradingNoticeInfoField *pTradingNoticeInfo)
{
    //std::cout << pTradingNoticeInfo->FieldContent  << std::endl;
}

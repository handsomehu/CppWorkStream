#include "tradewrapper.h"
TradeWrapper::TradeWrapper(const std::string &path):
  m_ptraderapi(nullptr),
  cfgpath(path), brokerid(""),mdaddress(""),tdaddress(""),
  userid(""), password(""), appid(""),authcode(""),
  jfile(path)
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
void TradeWrapper::connect()
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
    CThostFtdcReqUserLoginField t = {0};

    std::strcpy(t.BrokerID, "9999");

    std::strcpy(t.UserID, "118907");

    std::strcpy(t.Password, "CTPp4ss");

    while (m_ptraderapi->ReqUserLogin(&t, 1)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);
}

//结算单确认

void TradeWrapper::settlementinfoConfirm()

{

    CThostFtdcSettlementInfoConfirmField t = {0};

    std::strcpy(t.BrokerID, "9999");

    std::strcpy(t.InvestorID, "118907");

    while (m_ptraderapi->ReqSettlementInfoConfirm(&t, 2)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}



//报单

void TradeWrapper::orderinsert()

{

    CThostFtdcInputOrderField t = { 0 };

    std::strcpy(t.BrokerID, "9999");

    std::strcpy(t.InvestorID, "118907");

    std::strcpy(t.UserID, "118907");

    t.Direction = THOST_FTDC_D_Buy;

    t.CombOffsetFlag[0] = THOST_FTDC_OF_Open;

    t.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;

    t.ContingentCondition = THOST_FTDC_CC_Immediately;

    std::strcpy(t.InstrumentID, "sc1912");

    t.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;

    t.LimitPrice = 490;

    t.OrderPriceType = THOST_FTDC_OPT_LimitPrice;

    t.VolumeCondition = THOST_FTDC_VC_AV;

    t.TimeCondition = THOST_FTDC_TC_GFD;

    t.VolumeTotalOriginal = 1;

    std::strcpy(t.OrderRef, "0000001");

    std::strcpy(t.ExchangeID, "INE");

    while (m_ptraderapi->ReqOrderInsert(&t, 3) != 0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}

//查询合约

void TradeWrapper::qryInstrument()

{

    CThostFtdcQryInstrumentField t = { 0 };

    std::strcpy(t.ExchangeID, "SHFE");

    std::strcpy(t.InstrumentID, "zn2001");

    while (m_ptraderapi->ReqQryInstrument(&t, 4) != 0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}



//前置连接响应

void TradeWrapper::OnFrontConnected()

{

    printf("OnFrontConnected\n");
    ReqAuthenticate();

}



//登陆请求响应

void TradeWrapper::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspUserLogin\n");

}



//结算单确认响应

void TradeWrapper::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspSettlementInfoConfirm\n");
    std::cout << std::string(pRspInfo->ErrorMsg) << std::endl;
    //std::cout << pRspInfo-> << std::endl;

}



//查询合约响应

void TradeWrapper::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspQryInstrument\n");

}


//报单通知

void TradeWrapper::OnRtnOrder(CThostFtdcOrderField *pOrder)

{

    printf("OnRtnOrder\n");

}



//成交通知

void TradeWrapper::OnRtnTrade(CThostFtdcTradeField *pTrade)

{

    printf("OnRtnTrade\n");

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

}

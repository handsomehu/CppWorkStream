#include "ctraderhandler.h"

CTraderHandler::CTraderHandler()
{

}
void CTraderHandler::connect()
{
    //创建API实例

    m_ptraderapi = CThostFtdcTraderApi::CreateFtdcTraderApi(".//flow/");
    //必须提前创建好flow目录，流文件*.con就会在该文件夹下面创建，如果想要区别不同session创建的流水文件名称可见如下示例“.//flow/a_”

    m_ptraderapi->RegisterSpi(this);

    m_ptraderapi->SubscribePublicTopic(THOST_TERT_QUICK);

    m_ptraderapi->SubscribePrivateTopic(THOST_TERT_QUICK); //设置私有流订阅模式

    m_ptraderapi->RegisterFront("tcp://180.168.146.187:10100");

    m_ptraderapi->Init();

    //输出API版本信息

    printf("%s\n", m_ptraderapi->GetApiVersion());
    ReqAuthenticate();

}
int CTraderHandler::ReqAuthenticate()
{
    CThostFtdcReqAuthenticateField field;
    memset(&field, 0, sizeof(field));
    std::strcpy(field.BrokerID, "9999");
    std::strcpy(field.UserID, "118907");
    std::strcpy(field.AppID, "simnow_client_test");
    std::strcpy(field.AuthCode, "0000000000000000");
    return m_ptraderapi->ReqAuthenticate(&field, 5);

}
void CTraderHandler::OnRspAuthenticate(CThostFtdcRspAuthenticateField *pRspAuthenticateField, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
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

int CTraderHandler::ReqUserLogin()
{
    printf("====ReqUserLogin====,用户登录中...\n\n");
    CThostFtdcReqUserLoginField reqUserLogin;
    memset(&reqUserLogin, 0, sizeof(reqUserLogin));
    std::strcpy(reqUserLogin.BrokerID, "9999");
    strcpy(reqUserLogin.UserID, "118907");
    strcpy(reqUserLogin.Password, "Newpass");
    strcpy(reqUserLogin.TradingDay, "1108");
    static int RequestID = 0;
    return m_ptraderapi->ReqUserLogin(&reqUserLogin, ++RequestID);
}
void CTraderHandler::release()
{
    m_ptraderapi->Release();
}

void CTraderHandler::login()
{
    CThostFtdcReqUserLoginField t = {0};

    std::strcpy(t.BrokerID, "9999");

    std::strcpy(t.UserID, "118907");

    std::strcpy(t.Password, "Newpass");

    while (m_ptraderapi->ReqUserLogin(&t, 1)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);
}

//结算单确认

void CTraderHandler::settlementinfoConfirm()

{

    CThostFtdcSettlementInfoConfirmField t = {0};

    std::strcpy(t.BrokerID, "9999");

    std::strcpy(t.InvestorID, "118907");

    while (m_ptraderapi->ReqSettlementInfoConfirm(&t, 2)!=0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}



//报单

void CTraderHandler::orderinsert()

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

void CTraderHandler::qryInstrument()

{

    CThostFtdcQryInstrumentField t = { 0 };

    std::strcpy(t.ExchangeID, "SHFE");

    std::strcpy(t.InstrumentID, "zn2001");

    while (m_ptraderapi->ReqQryInstrument(&t, 4) != 0)
        std::this_thread::sleep_for(std::chrono::seconds(1));//Sleep(1000);

}



//前置连接响应

void CTraderHandler::OnFrontConnected()

{

    printf("OnFrontConnected\n");

}



//登陆请求响应

void CTraderHandler::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspUserLogin\n");

}



//结算单确认响应

void CTraderHandler::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspSettlementInfoConfirm\n");
    std::cout << std::string(pRspInfo->ErrorMsg) << std::endl;
    //std::cout << pRspInfo-> << std::endl;

}



//查询合约响应

void CTraderHandler::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspQryInstrument\n");

}


//报单通知

void CTraderHandler::OnRtnOrder(CThostFtdcOrderField *pOrder)

{

    printf("OnRtnOrder\n");

}



//成交通知

void CTraderHandler::OnRtnTrade(CThostFtdcTradeField *pTrade)

{

    printf("OnRtnTrade\n");

}



//报单录入请求响应

void CTraderHandler::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspOrderInsert\n");

}



//错误应答

void CTraderHandler::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)

{

    printf("OnRspError\n");

}

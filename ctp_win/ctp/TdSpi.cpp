#include "TdSpi.h"
#include <iostream>
#include "ThostFtdcTraderApi.h"
using namespace std;


TdSpi::TdSpi(QObject *parent)
	: QObject(parent)
{

}

TdSpi::~TdSpi()
{

}

#pragma warning(disable : 4996)

char INSTRUMENT_ID[100];	// 合约代码
TThostFtdcPriceType	LIMIT_PRICE;	// 价格
TThostFtdcDirectionType	DIRECTION;	// 买卖方向

// 请求编号
int iRequestTdID;

// 会话参数
TThostFtdcFrontIDType	FRONT_ID;	//前置编号
TThostFtdcSessionIDType	SESSION_ID;	//会话编号
TThostFtdcOrderRefType	ORDER_REF;	//报单引用

QString hyarray[500][4];   //定义一个合约的二纬数组
int k=0;


void TdSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	///用户登录请求
	ReqUserLogin();
}

void TdSpi::ReqUserLogin()
{
	CThostFtdcReqUserLoginField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, jy.BROKER_ID);
	strcpy(req.UserID, jy.INVESTOR_ID);
	strcpy(req.Password, jy.PASSWORD);
	int iResult = pUserApi->ReqUserLogin(&req, ++iRequestTdID);
	cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
								CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspUserLogin" << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// 保存会话参数
		FRONT_ID = pRspUserLogin->FrontID;
		SESSION_ID = pRspUserLogin->SessionID;
		int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		///获取当前交易日

		cerr << "--->>> 获取当前交易日 = " << pUserApi->GetTradingDay() << endl;
		///投资者结算结果确认
        this_thread::sleep_for(std::chrono::seconds(1));
		ReqSettlementInfoConfirm();
	}
}

void TdSpi::ReqSettlementInfoConfirm()
{
	CThostFtdcSettlementInfoConfirmField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, jy.BROKER_ID);
	strcpy(req.InvestorID, jy.INVESTOR_ID);
	int iResult = pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestTdID);
	cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询合约
		ReqQryInstrument();
	}
}

void TdSpi::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	int iResult = pUserApi->ReqQryInstrument(&req, ++iRequestTdID);
	cerr << "--->>> 请求查询合约: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	QString dm=pInstrument->InstrumentID; //合约代码
	QString mc=QString::fromLocal8Bit(pInstrument->InstrumentName); //名称
	QString cs=QString::number(pInstrument->VolumeMultiple);//合约乘数
	QString ds=QString::number(pInstrument->PriceTick); //合约点数

	hyarray[k][0]=dm;
	hyarray[k][1]=mc;
	hyarray[k][2]=cs;
	hyarray[k][3]=ds;
	k++;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//请求查询合约
        this_thread::sleep_for(std::chrono::seconds(2));
		ReqQryTradingAccount();
	}

	QString hyData=dm+","+mc+","+cs+","+ds;
	emit sendHY(hyData);


}

void TdSpi::ReqQryTradingAccount()
{
	CThostFtdcQryTradingAccountField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, jy.BROKER_ID);
	strcpy(req.InvestorID, jy.INVESTOR_ID);
	int iResult = pUserApi->ReqQryTradingAccount(&req, ++iRequestTdID);
	cerr << "--->>> 请求查询资金账户: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	QString account=pTradingAccount->AccountID;					//帐户
	double zqy=pTradingAccount->Balance;	//总权益
	double bzj=pTradingAccount->CurrMargin; //占用保证金
	double kyzj=pTradingAccount->Available;	//可用资金
	double sxf=pTradingAccount->Commission;
	double psyk=pTradingAccount->CloseProfit;

	double starqy = pTradingAccount->PreBalance;
	double yk=zqy-starqy-sxf; 
	double ykbfb=(zqy-starqy)*100/starqy;


	double fxd=bzj*100/zqy;

	//QString ZJData = account+","+QString("%1").arg(zqy,0,'f',2)+","+QString::number(bzj)+","+QString::number(kyzj)+","+QString::number(fxd);
	

	QString ZJData = account+","+QString("%1").arg(starqy,0,'f',2)+","+QString::number(bzj)+","+QString::number(kyzj)+","+QString::number(yk)+","+QString("%1").arg(ykbfb,0,'f',2);
	emit sendZJ(ZJData);

	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///请求查询投资者持仓
		//因为持仓查询具有延迟,无法正常显示,需要使用Sleep()
		//Sleep(2000); //windows.h
		ReqQryInvestorPosition();
	}
}

void TdSpi::ReqQryInvestorPosition()
{
	CThostFtdcQryInvestorPositionField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.BrokerID, jy.BROKER_ID);
	strcpy(req.InvestorID, jy.INVESTOR_ID);
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	int iResult = pUserApi->ReqQryInvestorPosition(&req, ++iRequestTdID);
	cerr << "--->>> 请求查询投资者持仓: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
   if(pInvestorPosition==NULL)return;
   if (pInvestorPosition->Position==0)return;
   QString dm=pInvestorPosition->InstrumentID; //持仓代码
   QString lx=QChar::fromLatin1(pInvestorPosition->PosiDirection); //持仓多空方向
   int lots=pInvestorPosition->Position; //持仓,一般用今仓
   double cb=pInvestorPosition->PositionCost/lots/hy(dm).hycs;	   //持仓成本 ,ag1612以吨计价

   QString CCData=dm+","+lx+","+QString::number(lots)+","+QString::number(cb);
   emit sendCC(CCData);
}


void TdSpi::ReqOrderInsert(QString dm,QString lx,int lots,double price)
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, jy.BROKER_ID);
	///投资者代码
	strcpy(req.InvestorID, jy.INVESTOR_ID);
	///合约代码
	strcpy(req.InstrumentID, dm.toStdString().data());
	///报单引用
    sprintf(ORDER_REF,"%d",iRequestTdID);	  //-------------
	strcpy(req.OrderRef, ORDER_REF);  
	///用户代码
	//	TThostFtdcUserIDType	UserID;
	///报单价格条件: 限价
	req.OrderPriceType = THOST_FTDC_OPT_LimitPrice;

	if (lx=="kd")
	{
		req.Direction=THOST_FTDC_D_Buy;
		req.CombOffsetFlag[0]= THOST_FTDC_OF_Open;
	}
	if (lx=="pd")
	{
		req.Direction=THOST_FTDC_D_Sell;
		req.CombOffsetFlag[0]=THOST_FTDC_OF_CloseToday;
	}
	if (lx=="kk")
	{
		  req.Direction=THOST_FTDC_D_Sell;
		  req.CombOffsetFlag[0]=THOST_FTDC_OF_Open;
	}
	if (lx=="pk")
	{
		req.Direction=THOST_FTDC_D_Buy;
		req.CombOffsetFlag[0] =THOST_FTDC_OF_CloseToday;
	}

	///组合投机套保标志
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///价格
	req.LimitPrice = price;
	///数量: 1
	req.VolumeTotalOriginal = lots;
	///有效期类型: 当日有效
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD日期
	//	TThostFtdcDateType	GTDDate;
	///成交量类型: 任何数量
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///最小成交量: 1
	req.MinVolume = 1;
	///触发条件: 立即
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///止损价
	//	TThostFtdcPriceType	StopPrice;
	///强平原因: 非强平
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///自动挂起标志: 否
	req.IsAutoSuspend = 0;
	///业务单元
	//	TThostFtdcBusinessUnitType	BusinessUnit;
	///请求编号
	//	TThostFtdcRequestIDType	RequestID;
	///用户强评标志: 否
	req.UserForceClose = 0;

	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestTdID);
	cerr << "--->>> 报单录入请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void TdSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderInsert" << endl;
	IsErrorRspInfo(pRspInfo);
}
//报单录入请求,撤单
void TdSpi::ReqOrderAction(QString brokerid,QString wth,QString jys)
{
	QByteArray ba=brokerid.toLatin1();
	char *pbid=ba.data();
	QByteArray bw=wth.toLatin1();
	char* pwth=bw.data();
	QByteArray bj=jys.toLatin1();
	char *pjys=	bj.data();

	CThostFtdcInputOrderActionField req;
	memset(&req, 0, sizeof(req));
	///经纪公司代码
	strcpy(req.BrokerID, pbid);
	strcpy(req.OrderSysID,pwth); //委托号
	strcpy(req.ExchangeID,pjys); //交易所

	///操作标志
	req.ActionFlag = THOST_FTDC_AF_Delete;
	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestTdID);
}

void TdSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderAction" << endl;
	IsErrorRspInfo(pRspInfo);
}

//问题模块
///报单通知	   ----委托回报
void TdSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	
	//报单状态处理
		
	QString zt;
	if(pOrder->OrderStatus==THOST_FTDC_OST_AllTraded){zt=QString::fromLocal8Bit("全部成交");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_PartTradedQueueing){zt=QString::fromLocal8Bit("部份成交");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_PartTradedNotQueueing){zt=QString::fromLocal8Bit("部份成交");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_NoTradeQueueing){zt=QString::fromLocal8Bit("未成交");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_Canceled){zt=QString::fromLocal8Bit("已撤单");}
	else {return;}

	
		QString wttime = pOrder->InsertTime; //委托时间
		QString dm = pOrder->InstrumentID; //委托代码
        QString bs = QChar::fromLatin1(pOrder->Direction); //买卖方向
		QString kp=pOrder->CombOffsetFlag; //开平标志
		QString lots = QString::number(pOrder->VolumeTotalOriginal); //数量
		QString price = QString::number(pOrder->LimitPrice); //价格
		QString wth = pOrder->OrderSysID; //委托号
		QString jsy=pOrder->ExchangeID; //交易所

		QString WTData=wttime+","+dm+","+bs+","+kp+","+lots+","+lots+","+price+","+zt+","+wth+","+jsy;

		emit sendWT(WTData);
	
}

///成交通知
void TdSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

	QString cjtime=pTrade->TradeTime;  //成交时间
	QString dm = pTrade->InstrumentID; //合约代码
    QString bs = QChar::fromLatin1(pTrade->Direction); //买卖方向
    QString kp = QChar::fromLatin1(pTrade->OffsetFlag); //开平标志
	QString lots = QString::number(pTrade->Volume); //合约数量
	QString price = QString::number(pTrade->Price);	//价格
	QString wth=pTrade->OrderSysID; //委托编号
	QString jys = pTrade->ExchangeID; //交易所

	QString CJData=cjtime+","+dm+","+bs+","+kp+","+lots+","+price+","+wth+","+jys;

	emit sendCJ(CJData);

}

void TdSpi:: OnFrontDisconnected(int nReason)
{
	cerr << "--->>> " << "OnFrontDisconnected" << endl;
	cerr << "--->>> Reason = " << nReason << endl;
}

void TdSpi::OnHeartBeatWarning(int nTimeLapse)
{
	cerr << "--->>> " << "OnHeartBeatWarning" << endl;
	cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void TdSpi::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspError" << endl;
	IsErrorRspInfo(pRspInfo);
}

bool TdSpi::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
	// 如果ErrorID != 0, 说明收到了错误的响应
	bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
	if (bResult)
		cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
	return bResult;
}

bool TdSpi::IsMyOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->FrontID == FRONT_ID) &&
		(pOrder->SessionID == SESSION_ID) &&
		(strcmp(pOrder->OrderRef, ORDER_REF) == 0));
}

bool TdSpi::IsTradingOrder(CThostFtdcOrderField *pOrder)
{
	return ((pOrder->OrderStatus != THOST_FTDC_OST_PartTradedNotQueueing) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_Canceled) &&
		(pOrder->OrderStatus != THOST_FTDC_OST_AllTraded));
}

void TdSpi::Init()
{
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// 创建UserApi
	pUserApi->RegisterSpi(this);			// 注册事件类
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// 注册公有流
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);					// 注册私有流
	pUserApi->RegisterFront(jy.FRONT_ADDR);							// connect
	pUserApi->Init();


}

 TdSpi::HYStruct TdSpi::hy(QString dm)
 {
 	HYStruct myhy;
	for (int i=0;i<500;i++)
	{
		if (dm==hyarray[i][0])
		{
			myhy.hycs=hyarray[i][2].toInt();
			myhy.hyds=hyarray[i][3].toDouble();
			break;
		}
	}
 	return myhy;
 }

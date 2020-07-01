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

char INSTRUMENT_ID[100];	// ��Լ����
TThostFtdcPriceType	LIMIT_PRICE;	// �۸�
TThostFtdcDirectionType	DIRECTION;	// ��������

// ������
int iRequestTdID;

// �Ự����
TThostFtdcFrontIDType	FRONT_ID;	//ǰ�ñ��
TThostFtdcSessionIDType	SESSION_ID;	//�Ự���
TThostFtdcOrderRefType	ORDER_REF;	//��������

QString hyarray[500][4];   //����һ����Լ�Ķ�γ����
int k=0;


void TdSpi::OnFrontConnected()
{
	cerr << "--->>> " << "OnFrontConnected" << endl;
	///�û���¼����
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
	cerr << "--->>> �����û���¼����: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
								CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspUserLogin" << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		// ����Ự����
		FRONT_ID = pRspUserLogin->FrontID;
		SESSION_ID = pRspUserLogin->SessionID;
		int iNextOrderRef = atoi(pRspUserLogin->MaxOrderRef);
		iNextOrderRef++;
		sprintf(ORDER_REF, "%d", iNextOrderRef);
		///��ȡ��ǰ������

		cerr << "--->>> ��ȡ��ǰ������ = " << pUserApi->GetTradingDay() << endl;
		///Ͷ���߽�����ȷ��
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
	cerr << "--->>> Ͷ���߽�����ȷ��: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspSettlementInfoConfirm" << endl;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		///�����ѯ��Լ
		ReqQryInstrument();
	}
}

void TdSpi::ReqQryInstrument()
{
	CThostFtdcQryInstrumentField req;
	memset(&req, 0, sizeof(req));
	strcpy(req.InstrumentID, INSTRUMENT_ID);
	int iResult = pUserApi->ReqQryInstrument(&req, ++iRequestTdID);
	cerr << "--->>> �����ѯ��Լ: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	
	QString dm=pInstrument->InstrumentID; //��Լ����
	QString mc=QString::fromLocal8Bit(pInstrument->InstrumentName); //����
	QString cs=QString::number(pInstrument->VolumeMultiple);//��Լ����
	QString ds=QString::number(pInstrument->PriceTick); //��Լ����

	hyarray[k][0]=dm;
	hyarray[k][1]=mc;
	hyarray[k][2]=cs;
	hyarray[k][3]=ds;
	k++;
	if (bIsLast && !IsErrorRspInfo(pRspInfo))
	{
		//�����ѯ��Լ
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
	cerr << "--->>> �����ѯ�ʽ��˻�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	QString account=pTradingAccount->AccountID;					//�ʻ�
	double zqy=pTradingAccount->Balance;	//��Ȩ��
	double bzj=pTradingAccount->CurrMargin; //ռ�ñ�֤��
	double kyzj=pTradingAccount->Available;	//�����ʽ�
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
		///�����ѯͶ���ֲ߳�
		//��Ϊ�ֲֲ�ѯ�����ӳ�,�޷�������ʾ,��Ҫʹ��Sleep()
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
	cerr << "--->>> �����ѯͶ���ֲ߳�: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
   if(pInvestorPosition==NULL)return;
   if (pInvestorPosition->Position==0)return;
   QString dm=pInvestorPosition->InstrumentID; //�ֲִ���
   QString lx=QChar::fromLatin1(pInvestorPosition->PosiDirection); //�ֲֶ�շ���
   int lots=pInvestorPosition->Position; //�ֲ�,һ���ý��
   double cb=pInvestorPosition->PositionCost/lots/hy(dm).hycs;	   //�ֲֳɱ� ,ag1612�ԶּƼ�

   QString CCData=dm+","+lx+","+QString::number(lots)+","+QString::number(cb);
   emit sendCC(CCData);
}


void TdSpi::ReqOrderInsert(QString dm,QString lx,int lots,double price)
{
	CThostFtdcInputOrderField req;
	memset(&req, 0, sizeof(req));
	///���͹�˾����
	strcpy(req.BrokerID, jy.BROKER_ID);
	///Ͷ���ߴ���
	strcpy(req.InvestorID, jy.INVESTOR_ID);
	///��Լ����
	strcpy(req.InstrumentID, dm.toStdString().data());
	///��������
    sprintf(ORDER_REF,"%d",iRequestTdID);	  //-------------
	strcpy(req.OrderRef, ORDER_REF);  
	///�û�����
	//	TThostFtdcUserIDType	UserID;
	///�����۸�����: �޼�
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

	///���Ͷ���ױ���־
	req.CombHedgeFlag[0] = THOST_FTDC_HF_Speculation;
	///�۸�
	req.LimitPrice = price;
	///����: 1
	req.VolumeTotalOriginal = lots;
	///��Ч������: ������Ч
	req.TimeCondition = THOST_FTDC_TC_GFD;
	///GTD����
	//	TThostFtdcDateType	GTDDate;
	///�ɽ�������: �κ�����
	req.VolumeCondition = THOST_FTDC_VC_AV;
	///��С�ɽ���: 1
	req.MinVolume = 1;
	///��������: ����
	req.ContingentCondition = THOST_FTDC_CC_Immediately;
	///ֹ���
	//	TThostFtdcPriceType	StopPrice;
	///ǿƽԭ��: ��ǿƽ
	req.ForceCloseReason = THOST_FTDC_FCC_NotForceClose;
	///�Զ������־: ��
	req.IsAutoSuspend = 0;
	///ҵ��Ԫ
	//	TThostFtdcBusinessUnitType	BusinessUnit;
	///������
	//	TThostFtdcRequestIDType	RequestID;
	///�û�ǿ����־: ��
	req.UserForceClose = 0;

	int iResult = pUserApi->ReqOrderInsert(&req, ++iRequestTdID);
	cerr << "--->>> ����¼������: " << ((iResult == 0) ? "�ɹ�" : "ʧ��") << endl;
}

void TdSpi::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderInsert" << endl;
	IsErrorRspInfo(pRspInfo);
}
//����¼������,����
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
	///���͹�˾����
	strcpy(req.BrokerID, pbid);
	strcpy(req.OrderSysID,pwth); //ί�к�
	strcpy(req.ExchangeID,pjys); //������

	///������־
	req.ActionFlag = THOST_FTDC_AF_Delete;
	int iResult = pUserApi->ReqOrderAction(&req, ++iRequestTdID);
}

void TdSpi::OnRspOrderAction(CThostFtdcInputOrderActionField *pInputOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
	cerr << "--->>> " << "OnRspOrderAction" << endl;
	IsErrorRspInfo(pRspInfo);
}

//����ģ��
///����֪ͨ	   ----ί�лر�
void TdSpi::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
	
	//����״̬����
		
	QString zt;
	if(pOrder->OrderStatus==THOST_FTDC_OST_AllTraded){zt=QString::fromLocal8Bit("ȫ���ɽ�");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_PartTradedQueueing){zt=QString::fromLocal8Bit("���ݳɽ�");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_PartTradedNotQueueing){zt=QString::fromLocal8Bit("���ݳɽ�");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_NoTradeQueueing){zt=QString::fromLocal8Bit("δ�ɽ�");}
	else if(pOrder->OrderStatus==THOST_FTDC_OST_Canceled){zt=QString::fromLocal8Bit("�ѳ���");}
	else {return;}

	
		QString wttime = pOrder->InsertTime; //ί��ʱ��
		QString dm = pOrder->InstrumentID; //ί�д���
        QString bs = QChar::fromLatin1(pOrder->Direction); //��������
		QString kp=pOrder->CombOffsetFlag; //��ƽ��־
		QString lots = QString::number(pOrder->VolumeTotalOriginal); //����
		QString price = QString::number(pOrder->LimitPrice); //�۸�
		QString wth = pOrder->OrderSysID; //ί�к�
		QString jsy=pOrder->ExchangeID; //������

		QString WTData=wttime+","+dm+","+bs+","+kp+","+lots+","+lots+","+price+","+zt+","+wth+","+jsy;

		emit sendWT(WTData);
	
}

///�ɽ�֪ͨ
void TdSpi::OnRtnTrade(CThostFtdcTradeField *pTrade)
{

	QString cjtime=pTrade->TradeTime;  //�ɽ�ʱ��
	QString dm = pTrade->InstrumentID; //��Լ����
    QString bs = QChar::fromLatin1(pTrade->Direction); //��������
    QString kp = QChar::fromLatin1(pTrade->OffsetFlag); //��ƽ��־
	QString lots = QString::number(pTrade->Volume); //��Լ����
	QString price = QString::number(pTrade->Price);	//�۸�
	QString wth=pTrade->OrderSysID; //ί�б��
	QString jys = pTrade->ExchangeID; //������

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
	// ���ErrorID != 0, ˵���յ��˴������Ӧ
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
	pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi();			// ����UserApi
	pUserApi->RegisterSpi(this);			// ע���¼���
	pUserApi->SubscribePublicTopic(THOST_TERT_RESTART);					// ע�ṫ����
	pUserApi->SubscribePrivateTopic(THOST_TERT_RESTART);					// ע��˽����
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

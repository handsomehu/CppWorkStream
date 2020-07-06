#include "qmd.h"
#include <iostream>
#include <QObject>
#include <QStringList>
using namespace std;

#pragma warning(disable: 4996)

char* ppInstrumentID []={"rb2010","TA009"};
int iInstrumentID=2;
// 请求编号
int iRequestID;

QMd::QMd(QObject *parent,std::string path)
    : QObject(parent),
      m_pmdapi(nullptr),
      cfgpath(path), brokerid(""),mdaddress(""),tdaddress(""),
      userid(""), password(""), appid(""),authcode(""),
      jfile(path),isconnected(false),goodorder(false),mktdata{},
      dm{"IF2008"}

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

QMd::~QMd()
{

}

void QMd::OnRspError(CThostFtdcRspInfoField *pRspInfo,
                        int nRequestID, bool bIsLast)
{
    cerr << "--->>> "<< __FUNCTION__ << endl;
    IsErrorRspInfo(pRspInfo);
}

void QMd::OnFrontDisconnected(int nReason)
{
    cerr << "--->>> " << __FUNCTION__ << endl;
    cerr << "--->>> Reason = " << nReason << endl;
}

void QMd::OnHeartBeatWarning(int nTimeLapse)
{
    cerr << "--->>> " << __FUNCTION__ << endl;
    cerr << "--->>> nTimerLapse = " << nTimeLapse << endl;
}

void QMd::OnFrontConnected()
{
    cerr << "--->>> " << __FUNCTION__ << endl;
    ///用户登录请求
    ReqUserLogin();
}


void QMd::ReqUserLogin()
{
    CThostFtdcReqUserLoginField req;
    memset(&req, 0, sizeof(req));
    char bufstr[100];
    std::copy(brokerid.begin(),brokerid.end(),bufstr);
    bufstr[brokerid.size()] = '\0';
    strcpy(req.BrokerID, bufstr);
    std::copy(userid.begin(),userid.end(),bufstr);
    bufstr[userid.size()] = '\0';
    std::strcpy(req.UserID, bufstr);
    std::copy(password.begin(),password.end(),bufstr);
    bufstr[password.size()] = '\0';
    std::strcpy(req.Password, bufstr);

    int iResult = m_pmdapi->ReqUserLogin(&req, ++iRequestID);
    cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

void QMd::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin,
                            CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << "--->>> " << __FUNCTION__ << endl;
    if (bIsLast && !IsErrorRspInfo(pRspInfo))
    {
        ///获取当前交易日
        cerr << "--->>> 获取当前交易日 = " << m_pmdapi->GetTradingDay() << endl;
        // 请求订阅行情
        SubscribeMarketData();
        SubscribeMarketData(dm);  //
    }
}
//
void QMd::SubscribeMarketData()
{
    int iResult = m_pmdapi->SubscribeMarketData(ppInstrumentID, iInstrumentID);
    cerr << "--->>> 发送行情订阅请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}
//自动交易模块化行情代码部分
void QMd::SubscribeMarketData(QString dm)
{
    QStringList strlist=dm.split(",");
    qDebug() << strlist[0];
    int iInstrumentID=strlist.length();
    for (int i=0;i<iInstrumentID;i++)
    {
        QString str=strlist.at(i);
        char *ch;
        QByteArray ba=str.toLatin1();
        ch=ba.data();
        char *myppInstrumentID[]={ch};
        int iRequestID=m_pmdapi->SubscribeMarketData(myppInstrumentID,1); //每次只发送一个
        std::this_thread::sleep_for(std::chrono::seconds(2));//Sleep(1000);

    }
    cerr<<"--->>>发送行情订阅请求:"<<((iRequestID==0)?"成功":"失败")<<endl;
}



void QMd::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << __FUNCTION__ << endl;
}

void QMd::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    cerr << __FUNCTION__ << endl;
}
//返回合约代码具体信息
void QMd::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    //cerr << __FUNCTION__ << endl;
    QString dm = pDepthMarketData->InstrumentID;   //
    QString updatetime = pDepthMarketData->UpdateTime;	  // 更新时间
    QString lastprice = QString::number(pDepthMarketData->LastPrice);	  //最新价
    QString buyprice = QString::number(pDepthMarketData->BidPrice1); //买一价
    QString buyvol=QString::number(pDepthMarketData->BidVolume1);//买一量
    QString sellprice =QString::number(pDepthMarketData->AskPrice1); //卖一价
    QString sellvol = QString::number(pDepthMarketData->AskVolume1); //卖一量
    QString preLastPrice = QString::number(pDepthMarketData->PreClosePrice); //昨收盘价
    QString zf = QString::number(((pDepthMarketData->LastPrice-pDepthMarketData->PreClosePrice)*100/pDepthMarketData->PreClosePrice),'f',2);  //涨幅的计算
    QString vol = QString::number(pDepthMarketData->Volume); //成交量
    QString zt = QString::number(pDepthMarketData->UpperLimitPrice); //涨停价
    QString dt = QString::number(pDepthMarketData->LowerLimitPrice); //跌停价
    QString openprice=QString::number(pDepthMarketData->OpenPrice);	 //开盘价

    QString HQTick = dm+","+updatetime+","+lastprice+","+buyprice+","+buyvol+","+sellprice+","+sellvol+","+zf+","+vol+","+zt+","+dt+","+openprice;	 //使用信号传递数据
    emit sendData(HQTick); //只是发送了数据，需要接收端接收数据 ，a,在ctp.h头文件定义接收方法 b, 通过SLOT连接
}

bool QMd::IsErrorRspInfo(CThostFtdcRspInfoField *pRspInfo)
{
    // 如果ErrorID != 0, 说明收到了错误的响应
    bool bResult = ((pRspInfo) && (pRspInfo->ErrorID != 0));
    if (bResult)
        cerr << "--->>> ErrorID=" << pRspInfo->ErrorID << ", ErrorMsg=" << pRspInfo->ErrorMsg << endl;
    return bResult;
}

void QMd::Init()
{
    char mdads[tdaddress.size()+1];
    std::copy(tdaddress.begin(),tdaddress.end(),mdads);
    mdads[mdaddress.size()] = '\0';
    m_pmdapi = CThostFtdcMdApi::CreateFtdcMdApi();
    m_pmdapi->RegisterSpi(this);
    m_pmdapi->RegisterFront(mdads);
    m_pmdapi->Init();
}

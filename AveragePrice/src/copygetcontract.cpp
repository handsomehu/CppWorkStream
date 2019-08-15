// 说明：通过调用ctp的trade接口，获取当前所有可交易的合约，如果账户登录不了的话，则不能成功查询
#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <memory>
#include <vector>
#include <chrono>
#include <thread>
#include "./libhead/ThostFtdcTraderApi.h"
using namespace std;
int iRequestID = 0;  //应答请求号
int Count(0);        //统计合约数
char *InstrumentName[5000];  //定义一个缓冲数组，用来保存合约名称的
TThostFtdcInstrumentIDType InstrumentName2[5000];  //总字节31*5000
bool OnRspQryInstrument_bIsLast(false);
char  FRONT_ADDR[] = "tcp://180.168.146.187:10030"; // 前置地址
TThostFtdcBrokerIDType BROKER_ID = "9999";   // 经纪公司代码
TThostFtdcInvestorIDType INVESTOR_ID = "118907";              // 注意输入你自己的simnow仿真投资者代码
TThostFtdcPasswordType  PASSWORD = "******";    // 注意输入你自己的simnow仿真用户密码


class CSimpleHandler : public CThostFtdcTraderSpi
{
public:
// 构造函数，需要一个有效的指向CThostFtdcMduserApi实例的指针
CSimpleHandler(CThostFtdcTraderApi *pUserApi):m_pUserApi(pUserApi) {}
~CSimpleHandler() {}
// 当客户端与交易托管系统建立起通信连接，客户端需要进行登录
virtual void OnFrontConnected()
{
CThostFtdcReqUserLoginField reqUserLogin;   //定义一个结构体
// 给结构体赋值

    strcpy(reqUserLogin.BrokerID, BROKER_ID);
    cout<<"reqUserLogin.BrokerID:"<<reqUserLogin.BrokerID<<endl;
strcpy(reqUserLogin.UserID, INVESTOR_ID);
strcpy(reqUserLogin.Password, PASSWORD);
//strcpy(reqUserLogin.AppID, "simnow_client_test");
//strcpy(reqUserLogin.AuthCode, "0000000000000000");
int iResult = m_pUserApi->ReqUserLogin(&reqUserLogin, ++iRequestID);
cerr << "--->>> 发送用户登录请求: " << ((iResult == 0) ? "成功" : "失败") << endl;
}

// 当客户端与交易托管系统通信连接断开时，该方法被调用
virtual void OnFrontDisconnected(int nReason)
{
// 当发生这个情况后，API会自动重新连接，客户端可不做处理
printf("客户端与交易托管系统通信连接断,API会自动重新连接.\n");
}



virtual void ReqSettlementInfoConfirm()
{

CThostFtdcSettlementInfoConfirmField req;
memset(&req, 0, sizeof(req));
strcpy(req.BrokerID, BROKER_ID);
strcpy(req.InvestorID, INVESTOR_ID);
int iResult = m_pUserApi->ReqSettlementInfoConfirm(&req, ++iRequestID);
cerr << "--->>> 投资者结算结果确认: " << ((iResult == 0) ? "成功" : "失败") << endl;
ReqQryInstrument();
}

// 当客户端发出登录请求之后，该方法会被调用，通知客户端登录是否成功
virtual void OnRspUserLogin(CThostFtdcRspUserLoginField*pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
printf("OnRspUserLogin:\n");
printf("ErrorCode=[%d], ErrorMsg=[%s]\n",
pRspInfo->ErrorID, pRspInfo->ErrorMsg);
printf("RequestID=[%d], Chain=[%d]\n", nRequestID, bIsLast);


if (pRspInfo->ErrorID != 0)
{
// 端登失败，客户端需进行错误处理
printf("Failed to login, errorcode=%d errormsg=%srequestid=%d chain=%d", pRspInfo->ErrorID, pRspInfo->ErrorMsg,nRequestID, bIsLast);

// 如果登录失败，这个时候没有查询出合约数，则总合约数返回值为-1
OnRspQryInstrument_bIsLast = true;  //当正确的查询来了合约，则返回总的合约数，否则返回-1，表示出错吗，更改这个值，则终止主线程的while
Count = -1; //表示没有查询结果，这个时候修改这两个全部变量的值
//exit(-1);  //退出线程，表示程序就不会再重新连接登录了，否则的话，会一直登录

}else
{
//确认结果
ReqSettlementInfoConfirm();
}
}


void ReqQryInstrument()
{
CThostFtdcQryInstrumentField req;
memset(&req, 0, sizeof(req));
//strcpy(req.InstrumentID, INSTRUMENT_ID);  //只要注释掉这一句，就可以实现全合约的查询了，这一句的作用是查询我们指定的合约信息
int iResult = m_pUserApi->ReqQryInstrument(&req, ++iRequestID);
cerr << "--->>> 请求查询合约: " << ((iResult == 0) ? "成功" : "失败") << endl;
}


void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID,bool bIsLast)
{
// TThostFtdcInstrumentIDType[31] 就是char[31];
char *temp = pInstrument->InstrumentID;
InstrumentName[Count] =temp;  //这样定义的InstrumentName在主函数里会出错，出现了野指针现象
memcpy(&InstrumentName2[Count], &(pInstrument->InstrumentID),sizeof(TThostFtdcInstrumentIDType));
//cout<<InstrumentName2[Count] <<endl;
Count++;
if (bIsLast==true)
{
  // cout<<"总合约数:"<<Count<<endl;
OnRspQryInstrument_bIsLast = true;
}



}







private:
// 指向CThostFtdcMduserApi实例的指针
CThostFtdcTraderApi *m_pUserApi;

};


int get_Instrument()
{
// 产生一个CThostFtdcTraderApi实例
CThostFtdcTraderApi *pUserApi =CThostFtdcTraderApi::CreateFtdcTraderApi();
// 产生一个事件处理的实例
CSimpleHandler sh(pUserApi);
// 注册一事件处理的实例
pUserApi->RegisterSpi(&sh);
// 订阅私有流
// TERT_RESTART:从本交易日开始重传
// TERT_RESUME:从上次收到的续传
// TERT_QUICK:只传送登录后私有流的内容
pUserApi->SubscribePrivateTopic(THOST_TERT_RESUME);
// 订阅公共流
// TERT_RESTART:从本交易日开始重传
// TERT_RESUME:从上次收到的续传
// TERT_QUICK:只传送登录后公共流的内容
pUserApi->SubscribePublicTopic(THOST_TERT_RESUME);
// 设置交易托管系统服务的地址，可以注册多个地址备用
pUserApi->RegisterFront( FRONT_ADDR);
// 使客户端开始与后台服务建立连接
pUserApi->Init();





while (OnRspQryInstrument_bIsLast==false && Count>=0)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
cout<<"在更新Count"<<endl;
}
// 释放API实例
pUserApi->Release();

if(OnRspQryInstrument_bIsLast)  //当正确的查询来了合约，则返回总的合约数，否则返回-1，表示出错
return Count;
else
return -1;





}


int main1()

{
int  Instrument_num = get_Instrument();
cout<<"合约数："<<Instrument_num<<endl;

// 由于缓存比较大，很多没有存满，存在冗余的，因此，重新定义变量，只取有存合约名字的
// 定义变量数量未知的字符数组：利用new和delete
TThostFtdcInstrumentIDType *adjusted_Instrument_name = new TThostFtdcInstrumentIDType[Instrument_num];
memcpy(adjusted_Instrument_name,&InstrumentName2,sizeof(TThostFtdcInstrumentIDType)*Count);


for (int i=0;i=0;i++)
{
//cout<<"sizeof(InstrumentName2)"<<sizeof(InstrumentName2)<<endl;
//cout<<"sizeof(TThostFtdcInstrumentIDType)"<<sizeof(TThostFtdcInstrumentIDType)<<endl;
cout<<"合约名字1："<<adjusted_Instrument_name[i]<<endl;   //这种方式会出错
//cout<<"合约名字2："<<InstrumentName2[i]<<endl;
cout<<"------------------------------------------------"<<endl;
}
delete adjusted_Instrument_name;
return 0;

}

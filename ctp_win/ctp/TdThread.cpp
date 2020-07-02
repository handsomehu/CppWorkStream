#include "TdThread.h"
#include "TdSpi.h"

TdThread::TdThread(QObject *parent)
{
	td=new TdSpi(this);
}

TdThread::~TdThread()
{

}

void TdThread::run()
{
	///////交易登陆
	strcpy(td->jy.FRONT_ADDR,jy.FRONT_ADDR);
	strcpy(td->jy.BROKER_ID,jy.BROKER_ID);
	strcpy(td->jy.INVESTOR_ID,jy.INVESTOR_ID);
	strcpy(td->jy.PASSWORD,jy.PASSWORD);
	td->Init();
}

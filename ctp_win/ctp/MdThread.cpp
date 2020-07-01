#include "MdThread.h"

MdThread::MdThread(QObject *parent)
{
	md=new MdSpi(this);

}

MdThread::~MdThread()
{

}

void MdThread::run()
{
	  strcpy(md->hq.FRONT_ADDR,hq.FRONT_ADDR);
	  strcpy(md->hq.BROKER_ID,hq.BROKER_ID);
	  md->Init();
}

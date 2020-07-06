#include "mdthread.h"

MdThread::MdThread(QObject *parent)
{
    md=new QMd(this,"./cfg/j123.json");

}

MdThread::~MdThread()
{

}

void MdThread::run()
{
	  md->Init();
}

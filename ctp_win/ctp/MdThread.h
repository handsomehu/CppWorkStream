#ifndef MDTHREAD_H
#define MDTHREAD_H

#include <QObject>
#include <QThread>
#include "MdSpi.h"

class MdThread : public QThread
{
	Q_OBJECT

public:
	MdThread(QObject *parent);
	~MdThread();
	MdSpi *md;
	void run();

public:
	typedef	struct MDStruct
	{
		char FRONT_ADDR[100];
		TThostFtdcBrokerIDType BROKER_ID;
		TThostFtdcInvestorIDType INVESTOR_ID;
		TThostFtdcPasswordType PASSWORD;
	};
	MDStruct hq;

private:
	
};

#endif // MDTHREAD_H

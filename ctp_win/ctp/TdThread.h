#ifndef TDTHREAD_H
#define TDTHREAD_H

#include <QObject>
#include <QThread>
#include "TdSpi.h"

class TdThread : public QThread
{
	Q_OBJECT

public:
	TdThread(QObject *parent);
	~TdThread();
	void run();
	TdSpi *td;
public:
	typedef struct TDStruct
	{
		char FRONT_ADDR[100];
		TThostFtdcBrokerIDType BROKER_ID;
		TThostFtdcInvestorIDType INVESTOR_ID;
		TThostFtdcPasswordKeyType PASSWORD;
	};
	TDStruct jy;
	//合约结构

private:
	
};

#endif // TDTHREAD_H

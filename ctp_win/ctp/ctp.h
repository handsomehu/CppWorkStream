#ifndef CTP_H
#define CTP_H

#include <QtWidgets/QMainWindow>
#include "ui_ctp.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TdSpi.h"


class ctp : public QMainWindow
{
	Q_OBJECT

public:
	ctp(QWidget *parent = 0);
	~ctp();
	MdSpi *md;
	TdSpi *td;
private slots:
	void MDLogin();
	void xd();
	void ReceiveHQ(QString);
	void ReceiveCJ(QString);
	void ReceiveWT(QString);
	void ReceiveCC(QString);
	void ReceiveZJ(QString);
	void ReceiveHY(QString);
private:
	Ui::ctpClass ui;

};

#endif // CTP_H

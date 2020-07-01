#ifndef CTP_H
#define CTP_H
#include <QtWidgets/QMainWindow>
#include "ui_ctp.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"

#include "tinystr.h"
#include "tinyxml.h"
#include <string>
#include <cstring>
#include <iostream>
#include "MdThread.h"
#include "TdThread.h"
using namespace std;

class ctp : public QMainWindow
{
	Q_OBJECT

public:
    ctp(QWidget *parent = nullptr);
	~ctp();
	MdThread *md;
	TdThread *td;
private slots:
	void MDLogin();
	void xd();
	void ReceiveHQ(QString);
	void ReceiveAutoHQ(QString);
	void ReceiveCJ(QString);
	void ReceiveWT(QString);
	void ReceiveCC(QString);
	void ReceiveAutoCC(QString);
	void ReceiveZJ(QString);
	void ReceiveHY(QString);
	void OnWTMenu(const QPoint& pt);
	void cd();
	void Onxml();
	void OnExit();

    string GetAppPath();
	bool writexml(string& szFileName); //xml写入
	bool readxml(string & szFileName);//xml读取

	void OnAddHeyue();  //自动交易合约添加
private:
	Ui::ctpClass ui;
	void WriteTxt(QString path,QString data);
	void WriteTxt(QString path,int flag);
	void ReadTxt(QString path);
	void ReadTxt(QString path,int flag);
	void AddHeyue();

	void kc(int);
	void pc(int);
};

#endif // CTP_H

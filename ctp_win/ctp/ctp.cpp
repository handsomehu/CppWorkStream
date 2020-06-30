#include "ctp.h"
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "MdSpi.h"
#include "TdSpi.h"


ctp::ctp(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	md=new MdSpi(this);
	td=new TdSpi(this);

	connect(md,SIGNAL(sendData(QString)),this,SLOT(ReceiveHQ(QString)));
	connect(td,SIGNAL(sendCJ(QString)),this,SLOT(ReceiveCJ(QString)));
	connect(td,SIGNAL(sendWT(QString)),this,SLOT(ReceiveWT(QString)));
	connect(td,SIGNAL(sendHY(QString)),this,SLOT(ReceiveHY(QString)));
	connect(td,SIGNAL(sendCC(QString)),this,SLOT(ReceiveCC(QString)));
	connect(td,SIGNAL(sendZJ(QString)),this,SLOT(ReceiveZJ(QString)));
	connect(ui.BtnXd,SIGNAL(clicked()),this,SLOT(xd()));

	//***************************行情表设置****************************************//
	//设置行情表格行列数量,行11行,10列
	ui.HQTable->setColumnCount(11);

	QStringList headerHQ;
	headerHQ.append(QString::fromLocal8Bit("合约代码"));
	headerHQ.append(QString::fromLocal8Bit("更新时间"));
	headerHQ.append(QString::fromLocal8Bit("最新价"));
	headerHQ.append(QString::fromLocal8Bit("买一价"));
	headerHQ.append(QString::fromLocal8Bit("买一量"));
	headerHQ.append(QString::fromLocal8Bit("卖一价"));
	headerHQ.append(QString::fromLocal8Bit("卖一量"));
	headerHQ.append(QString::fromLocal8Bit("涨幅"));
	headerHQ.append(QString::fromLocal8Bit("成交量"));
	headerHQ.append(QString::fromLocal8Bit("涨停价"));
	headerHQ.append(QString::fromLocal8Bit("跌停价"));

	//填充表格信息
	ui.HQTable->setHorizontalHeaderLabels(headerHQ);
	//自动排列列的内容
	ui.HQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.HQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.HQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


	//***************************委托表设置****************************************//
	//设置委托表格行列数量,行11行,10列
	ui.WTTable->setColumnCount(9);
	//ui.WTTable->setRowCount(10);

	QStringList headerWT;
	headerWT.append(QString::fromLocal8Bit("委托时间"));
	headerWT.append(QString::fromLocal8Bit("合约代码"));
	headerWT.append(QString::fromLocal8Bit("买卖"));
	headerWT.append(QString::fromLocal8Bit("开平"));
	headerWT.append(QString::fromLocal8Bit("数量"));
	headerWT.append(QString::fromLocal8Bit("价格"));
	headerWT.append(QString::fromLocal8Bit("状态"));
	headerWT.append(QString::fromLocal8Bit("委托号"));
	headerWT.append(QString::fromLocal8Bit("交易所"));
	

	//填充表格信息
	ui.WTTable->setHorizontalHeaderLabels(headerWT);
	//自动排列列的内容
	ui.WTTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.WTTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.WTTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************成交表设置****************************************//
	//设置成交表格行列数量,行11行,10列
	ui.CJTable->setColumnCount(8);
	//ui.CJTable->setRowCount(10);

	QStringList headerCJ;
	headerCJ.append(QString::fromLocal8Bit("成交时间"));
	headerCJ.append(QString::fromLocal8Bit("合约代码"));
	headerCJ.append(QString::fromLocal8Bit("买卖"));
	headerCJ.append(QString::fromLocal8Bit("开平"));
	headerCJ.append(QString::fromLocal8Bit("数量"));
	headerCJ.append(QString::fromLocal8Bit("价格"));
	headerCJ.append(QString::fromLocal8Bit("委托号"));
	headerCJ.append(QString::fromLocal8Bit("交易所"));


	//填充表格信息
	ui.CJTable->setHorizontalHeaderLabels(headerCJ);
	//自动排列列的内容
	ui.CJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.CJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.CJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************持仓表设置****************************************//
	//设置持仓表格行列数量,行11行,10列
	ui.CCTable->setColumnCount(4);
	//ui.CCTable->setRowCount(6);

	QStringList headerCC;
	headerCC.append(QString::fromLocal8Bit("合约代码"));
	headerCC.append(QString::fromLocal8Bit("持仓类型"));
	headerCC.append(QString::fromLocal8Bit("持仓数量"));
	headerCC.append(QString::fromLocal8Bit("持仓成本"));

	//填充表格信息
	ui.CCTable->setHorizontalHeaderLabels(headerCC);
	//自动排列列的内容
	ui.CCTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.CCTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.CCTable->setEditTriggers(QAbstractItemView::NoEditTriggers);



	//***************************资金表设置****************************************//
	//设置资金表格行列数量,行11行,10列
	ui.ZJTable->setColumnCount(5);

	QStringList headerZJ;
	headerZJ.append(QString::fromLocal8Bit("帐户"));
	headerZJ.append(QString::fromLocal8Bit("动态权益"));
	headerZJ.append(QString::fromLocal8Bit("占用保证金"));
	headerZJ.append(QString::fromLocal8Bit("可用资金"));
	headerZJ.append(QString::fromLocal8Bit("风险度"));


	//填充表格信息
	ui.ZJTable->setHorizontalHeaderLabels(headerZJ);
	//自动排列列的内容
	ui.ZJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.ZJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.ZJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************合约表设置****************************************//
	//设置合约表格行列数量,
	ui.HYTable->setColumnCount(4);
	//ui.HYTable->setRowCount(200);

	QStringList headerHY;
	headerHY.append(QString::fromLocal8Bit("代码"));
	headerHY.append(QString::fromLocal8Bit("合约名称"));
	headerHY.append(QString::fromLocal8Bit("合约乘数"));
	headerHY.append(QString::fromLocal8Bit("合约点数"));

	//填充表格信息
	ui.HYTable->setHorizontalHeaderLabels(headerHY);
	//自动排列列的内容
	ui.HYTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//整行选中
	ui.HYTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//禁止编辑
	ui.HYTable->setEditTriggers(QAbstractItemView::NoEditTriggers);



	/////////////////////********************************///////////////////////////
	//设置行情地址
	ui.MDEdit->setText("tcp://180.168.146.187:10010");
	ui.TDEdit->setText("tcp://180.168.146.187:10000");
	ui.BIDEdit->setText("9999");
	ui.USEREdit->setText("049252");
	ui.PWDEdit->setEchoMode(QLineEdit::Password);
	ui.PWDEdit->setText("5201314tang");


	ui.Editdm->setText("ni1609");
	ui.EditLots->setText("2");

	//设置平今仓/市价的radio为选中
	ui.radioSJ->setChecked(true);
	ui.radioPJ->setChecked(true);


}

ctp::~ctp()
{

}

void ctp::MDLogin()
{
	/////////////行情

	//从EditLine传过来的参数为QString数据类型，在CTP API中为char数据类型，需做如下转化
	char* ch1;
	char* ch2;
	char* ch3;
	char* ch4;
	char* ch5;

	QByteArray ba1=ui.MDEdit->text().toLatin1();
	QByteArray ba2=ui.BIDEdit->text().toLatin1();
	QByteArray ba3=ui.TDEdit->text().toLatin1();
	QByteArray ba4 = ui.USEREdit->text().toLatin1();
	QByteArray ba5 = ui.PWDEdit->text().toLatin1();

	ch1 =ba1.data();
	ch2=ba2.data();
	ch3=ba3.data();
	ch4=ba4.data();
	ch5=ba5.data();

	strcpy(md->hq.FRONT_ADDR,ch1);
	strcpy(md->hq.BROKER_ID,ch2);
	md->Init();

	///////交易登陆
	strcpy(td->jy.FRONT_ADDR,ch3);
	strcpy(td->jy.BROKER_ID,ch2);
	strcpy(td->jy.INVESTOR_ID,ch4);
	strcpy(td->jy.PASSWORD,ch5);
	td->Init();

}

void ctp::ReceiveHQ(QString TICK)
{
  QStringList  strlist =TICK.split(",");	   //接收StringList数据

  if (strlist.at(0)==ui.Editdm->text())
  {
	   ui.labelAsk->setText(strlist.at(5));
	   ui.labelLast->setText(strlist.at(2));
	   ui.labelBid->setText(strlist.at(3));
	   ui.labelUp->setText(strlist.at(9));
	   ui.labelDown->setText(strlist.at(10));
  }




  //循环传入的数据
  for (int i=0;i<ui.HQTable->rowCount();i++)   //以 HQTable数量为边界
  {
	  if (ui.HQTable->item(i,0)->text()==strlist.at(0))
	  {
		  
		  ui.HQTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
		  ui.HQTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //更新数据
		  ui.HQTable->setItem(i,2,new QTableWidgetItem(strlist.at(2)));	  //更新数据
		  ui.HQTable->setItem(i,3,new QTableWidgetItem(strlist.at(3)));	  //更新数据
		  ui.HQTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //更新数据
		  ui.HQTable->setItem(i,5,new QTableWidgetItem(strlist.at(5)));	  //更新数据
		  ui.HQTable->setItem(i,6,new QTableWidgetItem(strlist.at(6)));	  //更新数据
		  ui.HQTable->setItem(i,7,new QTableWidgetItem(strlist.at(7)));	  //更新数据
		  ui.HQTable->setItem(i,8,new QTableWidgetItem(strlist.at(8)));	  //更新数据
		  ui.HQTable->setItem(i,9,new QTableWidgetItem(strlist.at(9)));	  //更新数据
		  ui.HQTable->setItem(i,10,new QTableWidgetItem(strlist.at(10)));	  //更新数据
		  
		  return;
	  }
	  
  }
  int row = ui.HQTable->rowCount();
  ui.HQTable->insertRow(row);
  ui.HQTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
  ui.HQTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
  ui.HQTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
  ui.HQTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
  ui.HQTable->setItem(row,4,new QTableWidgetItem(strlist.at(4)));
  ui.HQTable->setItem(row,5,new QTableWidgetItem(strlist.at(5)));
  ui.HQTable->setItem(row,6,new QTableWidgetItem(strlist.at(6)));
  ui.HQTable->setItem(row,7,new QTableWidgetItem(strlist.at(7)));
  ui.HQTable->setItem(row,8,new QTableWidgetItem(strlist.at(8)));
  ui.HQTable->setItem(row,9,new QTableWidgetItem(strlist.at(9)));
  ui.HQTable->setItem(row,10,new QTableWidgetItem(strlist.at(10)));

}

void ctp::ReceiveCJ(QString CJData)
{

	QStringList strlist =CJData.split(",");

	QString buysell="";
	QString openclose="";
	if (strlist.at(2)=="0")
	{
		buysell=QString::fromLocal8Bit("买入");
	}else
	{
		buysell=QString::fromLocal8Bit("卖出");
	}
	if (strlist.at(3)=="0")
	{
		openclose = QString::fromLocal8Bit("开仓");
	}
	else if(strlist.at(3)=="4")
	{
		openclose=QString::fromLocal8Bit("平昨");
	}
	else
	{
		openclose=QString::fromLocal8Bit("平今");
	}
	//0是开仓,3是平今，4是平昨

	int row=ui.CJTable->rowCount();
	ui.CJTable->insertRow(row);
	ui.CJTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
	ui.CJTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
	ui.CJTable->setItem(row,2,new QTableWidgetItem(buysell));
	ui.CJTable->setItem(row,3,new QTableWidgetItem(openclose));
	ui.CJTable->setItem(row,4,new QTableWidgetItem(strlist.at(4)));
	ui.CJTable->setItem(row,5,new QTableWidgetItem(strlist.at(5)));
	ui.CJTable->setItem(row,6,new QTableWidgetItem(strlist.at(6)));
	ui.CJTable->setItem(row,7,new QTableWidgetItem(strlist.at(7)));
	

}

void ctp::ReceiveWT(QString WTData )
{
	 QStringList strlist = WTData.split(",");
	 if (strlist.at(8)=="")return;

	 QString buysell="";
	 QString openclose="";
	 if (strlist.at(2)=="0")
	 {
		 buysell=QString::fromLocal8Bit("买入");
	 }else
	 {
		 buysell=QString::fromLocal8Bit("卖出");
	 }
	 if (strlist.at(3)=="0")
	 {
		 openclose = QString::fromLocal8Bit("开仓");
	 }
	 else if(strlist.at(3)=="4")
	 {
		 openclose=QString::fromLocal8Bit("平昨");
	 }
	 else
	 {
		 openclose=QString::fromLocal8Bit("平今");
	 }
	 //0是开仓,3是平今，4是平昨


	 //循环传入的数据
	 for (int i=0;i<ui.WTTable->rowCount();i++)   //以 WTTable数量为边界
	 {
		 if (ui.WTTable->item(i,0)->text()==strlist.at(0))
		 {

			 ui.WTTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
			 ui.WTTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //更新数据
			 ui.WTTable->setItem(i,2,new QTableWidgetItem(buysell));	  //更新数据
			 ui.WTTable->setItem(i,3,new QTableWidgetItem(openclose));	  //更新数据
			 ui.WTTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //更新数据
			 ui.WTTable->setItem(i,5,new QTableWidgetItem(strlist.at(6)));	  //更新数据
			 ui.WTTable->setItem(i,6,new QTableWidgetItem(strlist.at(7)));	  //更新数据
			 ui.WTTable->setItem(i,7,new QTableWidgetItem(strlist.at(8)));	  //更新数据
			 ui.WTTable->setItem(i,8,new QTableWidgetItem(strlist.at(9)));	  //更新数据

			 return;
		 }

	 }


	 int row=ui.WTTable->rowCount();
	 ui.WTTable->insertRow(row);
	 ui.WTTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
	 ui.WTTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
	 ui.WTTable->setItem(row,2,new QTableWidgetItem(buysell));
	 ui.WTTable->setItem(row,3,new QTableWidgetItem(openclose));
	 ui.WTTable->setItem(row,4,new QTableWidgetItem(strlist.at(4)));
	 ui.WTTable->setItem(row,5,new QTableWidgetItem(strlist.at(6)));
	 ui.WTTable->setItem(row,6,new QTableWidgetItem(strlist.at(7)));
	 ui.WTTable->setItem(row,7,new QTableWidgetItem(strlist.at(8)));
	 ui.WTTable->setItem(row,8,new QTableWidgetItem(strlist.at(9)));

}

void ctp::ReceiveCC(QString CCData)
{
   QString lx;
   QStringList strlist = CCData.split(",");
   if (strlist.at(1)=="2"){lx=QString::fromLocal8Bit("买");}
   if (strlist.at(1)=="3"){lx=QString::fromLocal8Bit("卖");}

   int row=ui.CCTable->rowCount();
   ui.CCTable->insertRow(row);
   ui.CCTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
   ui.CCTable->setItem(row,1,new QTableWidgetItem(lx));
   ui.CCTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
   ui.CCTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
}

//资金数据接收方法,更新至资金表
void ctp::ReceiveZJ(QString ZJData)
{
	QStringList  strlist =ZJData.split(",");	   //接收StringList数据
	//循环传入的数据
	int row = ui.ZJTable->rowCount();
	ui.ZJTable->insertRow(row);
	ui.ZJTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
	ui.ZJTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
	ui.ZJTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
	ui.ZJTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
	ui.ZJTable->setItem(row,4,new QTableWidgetItem(strlist.at(4)));
}

void ctp::ReceiveHY(QString HYData)
{
 	QStringList  strlist =HYData.split(",");	   //接收StringList数据
 	//循环传入的数据
 	int row = ui.HYTable->rowCount();
 	ui.HYTable->insertRow(row);
 	ui.HYTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
 	ui.HYTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
	ui.HYTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
	ui.HYTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
}

void ctp::xd()
{
	   QString dm=ui.Editdm->text();
	   int lots=ui.EditLots->text().toInt();

	   QString lx;
	   double wtprice;
	   double sjprice;
	   double xjprice;
	   
	   int index=ui.comboXd->currentIndex();
	   if (ui.radioSJ->isChecked())
	   {
		   if (index == 0)
		   {
			   lx = "kd";
			   sjprice=ui.labelAsk->text().toDouble();
			   wtprice=sjprice;

		   }
		   if (index==1)
		   {
			   lx="pd";
			   sjprice=ui.labelBid->text().toDouble();
			   wtprice=sjprice;
		   }
		   if (index==2)
		   {
			   lx="kk";
			   sjprice=ui.labelBid->text().toDouble();
			   wtprice=sjprice;
		   }
		   if (index==3)
		   {
				lx="pk";
				sjprice	=ui.labelAsk->text().toDouble();
				wtprice=sjprice;
		   }
	   }
	   if (ui.radioXJ->isChecked())
	   {
		   if (index==0)
		   {
			   lx="kd";
			   xjprice=ui.EditXj->text().toDouble();
			   wtprice=xjprice;
		   }
		   if (index==1)
		   {
			   lx="pd";
			   xjprice=ui.EditXj->text().toDouble();
			   wtprice=xjprice;
		   }
		   if (index==2)
		   {
			   lx="kk";
			   xjprice=ui.EditXj->text().toDouble();
			   wtprice=xjprice;

		   }
		   if (index==3)
		   {
			   lx="pk";
			   xjprice=	ui.EditXj->text().toDouble();
			   wtprice=xjprice;
		   }
	   }

	  td->ReqOrderInsert(dm,lx,lots,wtprice);
	   

}

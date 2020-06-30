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

	//***************************���������****************************************//
	//������������������,��11��,10��
	ui.HQTable->setColumnCount(11);

	QStringList headerHQ;
	headerHQ.append(QString::fromLocal8Bit("��Լ����"));
	headerHQ.append(QString::fromLocal8Bit("����ʱ��"));
	headerHQ.append(QString::fromLocal8Bit("���¼�"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("��һ��"));
	headerHQ.append(QString::fromLocal8Bit("�Ƿ�"));
	headerHQ.append(QString::fromLocal8Bit("�ɽ���"));
	headerHQ.append(QString::fromLocal8Bit("��ͣ��"));
	headerHQ.append(QString::fromLocal8Bit("��ͣ��"));

	//�������Ϣ
	ui.HQTable->setHorizontalHeaderLabels(headerHQ);
	//�Զ������е�����
	ui.HQTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.HQTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.HQTable->setEditTriggers(QAbstractItemView::NoEditTriggers);


	//***************************ί�б�����****************************************//
	//����ί�б����������,��11��,10��
	ui.WTTable->setColumnCount(9);
	//ui.WTTable->setRowCount(10);

	QStringList headerWT;
	headerWT.append(QString::fromLocal8Bit("ί��ʱ��"));
	headerWT.append(QString::fromLocal8Bit("��Լ����"));
	headerWT.append(QString::fromLocal8Bit("����"));
	headerWT.append(QString::fromLocal8Bit("��ƽ"));
	headerWT.append(QString::fromLocal8Bit("����"));
	headerWT.append(QString::fromLocal8Bit("�۸�"));
	headerWT.append(QString::fromLocal8Bit("״̬"));
	headerWT.append(QString::fromLocal8Bit("ί�к�"));
	headerWT.append(QString::fromLocal8Bit("������"));
	

	//�������Ϣ
	ui.WTTable->setHorizontalHeaderLabels(headerWT);
	//�Զ������е�����
	ui.WTTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.WTTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.WTTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************�ɽ�������****************************************//
	//���óɽ������������,��11��,10��
	ui.CJTable->setColumnCount(8);
	//ui.CJTable->setRowCount(10);

	QStringList headerCJ;
	headerCJ.append(QString::fromLocal8Bit("�ɽ�ʱ��"));
	headerCJ.append(QString::fromLocal8Bit("��Լ����"));
	headerCJ.append(QString::fromLocal8Bit("����"));
	headerCJ.append(QString::fromLocal8Bit("��ƽ"));
	headerCJ.append(QString::fromLocal8Bit("����"));
	headerCJ.append(QString::fromLocal8Bit("�۸�"));
	headerCJ.append(QString::fromLocal8Bit("ί�к�"));
	headerCJ.append(QString::fromLocal8Bit("������"));


	//�������Ϣ
	ui.CJTable->setHorizontalHeaderLabels(headerCJ);
	//�Զ������е�����
	ui.CJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.CJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.CJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************�ֱֲ�����****************************************//
	//���óֱֲ����������,��11��,10��
	ui.CCTable->setColumnCount(4);
	//ui.CCTable->setRowCount(6);

	QStringList headerCC;
	headerCC.append(QString::fromLocal8Bit("��Լ����"));
	headerCC.append(QString::fromLocal8Bit("�ֲ�����"));
	headerCC.append(QString::fromLocal8Bit("�ֲ�����"));
	headerCC.append(QString::fromLocal8Bit("�ֲֳɱ�"));

	//�������Ϣ
	ui.CCTable->setHorizontalHeaderLabels(headerCC);
	//�Զ������е�����
	ui.CCTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.CCTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.CCTable->setEditTriggers(QAbstractItemView::NoEditTriggers);



	//***************************�ʽ������****************************************//
	//�����ʽ�����������,��11��,10��
	ui.ZJTable->setColumnCount(5);

	QStringList headerZJ;
	headerZJ.append(QString::fromLocal8Bit("�ʻ�"));
	headerZJ.append(QString::fromLocal8Bit("��̬Ȩ��"));
	headerZJ.append(QString::fromLocal8Bit("ռ�ñ�֤��"));
	headerZJ.append(QString::fromLocal8Bit("�����ʽ�"));
	headerZJ.append(QString::fromLocal8Bit("���ն�"));


	//�������Ϣ
	ui.ZJTable->setHorizontalHeaderLabels(headerZJ);
	//�Զ������е�����
	ui.ZJTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.ZJTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.ZJTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

	//***************************��Լ������****************************************//
	//���ú�Լ�����������,
	ui.HYTable->setColumnCount(4);
	//ui.HYTable->setRowCount(200);

	QStringList headerHY;
	headerHY.append(QString::fromLocal8Bit("����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));
	headerHY.append(QString::fromLocal8Bit("��Լ����"));

	//�������Ϣ
	ui.HYTable->setHorizontalHeaderLabels(headerHY);
	//�Զ������е�����
	ui.HYTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	//����ѡ��
	ui.HYTable->setSelectionBehavior(QAbstractItemView::SelectRows);
	//��ֹ�༭
	ui.HYTable->setEditTriggers(QAbstractItemView::NoEditTriggers);



	/////////////////////********************************///////////////////////////
	//���������ַ
	ui.MDEdit->setText("tcp://180.168.146.187:10010");
	ui.TDEdit->setText("tcp://180.168.146.187:10000");
	ui.BIDEdit->setText("9999");
	ui.USEREdit->setText("049252");
	ui.PWDEdit->setEchoMode(QLineEdit::Password);
	ui.PWDEdit->setText("5201314tang");


	ui.Editdm->setText("ni1609");
	ui.EditLots->setText("2");

	//����ƽ���/�м۵�radioΪѡ��
	ui.radioSJ->setChecked(true);
	ui.radioPJ->setChecked(true);


}

ctp::~ctp()
{

}

void ctp::MDLogin()
{
	/////////////����

	//��EditLine�������Ĳ���ΪQString�������ͣ���CTP API��Ϊchar�������ͣ���������ת��
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

	///////���׵�½
	strcpy(td->jy.FRONT_ADDR,ch3);
	strcpy(td->jy.BROKER_ID,ch2);
	strcpy(td->jy.INVESTOR_ID,ch4);
	strcpy(td->jy.PASSWORD,ch5);
	td->Init();

}

void ctp::ReceiveHQ(QString TICK)
{
  QStringList  strlist =TICK.split(",");	   //����StringList����

  if (strlist.at(0)==ui.Editdm->text())
  {
	   ui.labelAsk->setText(strlist.at(5));
	   ui.labelLast->setText(strlist.at(2));
	   ui.labelBid->setText(strlist.at(3));
	   ui.labelUp->setText(strlist.at(9));
	   ui.labelDown->setText(strlist.at(10));
  }




  //ѭ�����������
  for (int i=0;i<ui.HQTable->rowCount();i++)   //�� HQTable����Ϊ�߽�
  {
	  if (ui.HQTable->item(i,0)->text()==strlist.at(0))
	  {
		  
		  ui.HQTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //��������
		  ui.HQTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //��������
		  ui.HQTable->setItem(i,2,new QTableWidgetItem(strlist.at(2)));	  //��������
		  ui.HQTable->setItem(i,3,new QTableWidgetItem(strlist.at(3)));	  //��������
		  ui.HQTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //��������
		  ui.HQTable->setItem(i,5,new QTableWidgetItem(strlist.at(5)));	  //��������
		  ui.HQTable->setItem(i,6,new QTableWidgetItem(strlist.at(6)));	  //��������
		  ui.HQTable->setItem(i,7,new QTableWidgetItem(strlist.at(7)));	  //��������
		  ui.HQTable->setItem(i,8,new QTableWidgetItem(strlist.at(8)));	  //��������
		  ui.HQTable->setItem(i,9,new QTableWidgetItem(strlist.at(9)));	  //��������
		  ui.HQTable->setItem(i,10,new QTableWidgetItem(strlist.at(10)));	  //��������
		  
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
		buysell=QString::fromLocal8Bit("����");
	}else
	{
		buysell=QString::fromLocal8Bit("����");
	}
	if (strlist.at(3)=="0")
	{
		openclose = QString::fromLocal8Bit("����");
	}
	else if(strlist.at(3)=="4")
	{
		openclose=QString::fromLocal8Bit("ƽ��");
	}
	else
	{
		openclose=QString::fromLocal8Bit("ƽ��");
	}
	//0�ǿ���,3��ƽ��4��ƽ��

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
		 buysell=QString::fromLocal8Bit("����");
	 }else
	 {
		 buysell=QString::fromLocal8Bit("����");
	 }
	 if (strlist.at(3)=="0")
	 {
		 openclose = QString::fromLocal8Bit("����");
	 }
	 else if(strlist.at(3)=="4")
	 {
		 openclose=QString::fromLocal8Bit("ƽ��");
	 }
	 else
	 {
		 openclose=QString::fromLocal8Bit("ƽ��");
	 }
	 //0�ǿ���,3��ƽ��4��ƽ��


	 //ѭ�����������
	 for (int i=0;i<ui.WTTable->rowCount();i++)   //�� WTTable����Ϊ�߽�
	 {
		 if (ui.WTTable->item(i,0)->text()==strlist.at(0))
		 {

			 ui.WTTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //��������
			 ui.WTTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //��������
			 ui.WTTable->setItem(i,2,new QTableWidgetItem(buysell));	  //��������
			 ui.WTTable->setItem(i,3,new QTableWidgetItem(openclose));	  //��������
			 ui.WTTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //��������
			 ui.WTTable->setItem(i,5,new QTableWidgetItem(strlist.at(6)));	  //��������
			 ui.WTTable->setItem(i,6,new QTableWidgetItem(strlist.at(7)));	  //��������
			 ui.WTTable->setItem(i,7,new QTableWidgetItem(strlist.at(8)));	  //��������
			 ui.WTTable->setItem(i,8,new QTableWidgetItem(strlist.at(9)));	  //��������

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
   if (strlist.at(1)=="2"){lx=QString::fromLocal8Bit("��");}
   if (strlist.at(1)=="3"){lx=QString::fromLocal8Bit("��");}

   int row=ui.CCTable->rowCount();
   ui.CCTable->insertRow(row);
   ui.CCTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
   ui.CCTable->setItem(row,1,new QTableWidgetItem(lx));
   ui.CCTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
   ui.CCTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
}

//�ʽ����ݽ��շ���,�������ʽ��
void ctp::ReceiveZJ(QString ZJData)
{
	QStringList  strlist =ZJData.split(",");	   //����StringList����
	//ѭ�����������
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
 	QStringList  strlist =HYData.split(",");	   //����StringList����
 	//ѭ�����������
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

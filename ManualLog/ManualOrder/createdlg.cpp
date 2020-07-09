#include "createdlg.h"
#include "ui_createdlg.h"

CreateDlg::CreateDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDlg)
    , dbhelper("/home/leon/sqllitedb/tradelog_vnpy.db")
    //,mktdata("")
    , cnstatus(true)
{
    tdthread = new TdThread(this);
    mdthread = new MdThread(this);
    ui->setupUi(this);
    ui->cb_Dir->addItem("多");
    ui->cb_Dir->addItem("空");
    ui->cb_offset->addItems({"开仓","平仓","平昨","平今"});
    //qDebug() << dbhelper. getMaxId();
    ui->cb_strg->addItems({"DT_IntraDayCommonStrategy","TurtleUseCloseStrategy","JDualThrust_IntraDayStrategy"});
    ui->cb_exch->addItems({"SHFE","DCE","CZCE","CFFEX","INE"});
    connect(this, SIGNAL(LogOrder(QString)), this, SLOT(onTrade(QString) ));

    //if (tdthread->td)
    bool t1 = connect(this,&CreateDlg::uisendWT,this,&CreateDlg::ReceiveWT,Qt::QueuedConnection);
    qDebug() << t1;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(querywork()),Qt::QueuedConnection);
    connect(mdthread->md,&QMd::sendData,this,&CreateDlg::ReceiveHQ);
    connect(mdthread->md,&QMd::sendData,this,&CreateDlg::ReceiveAutoHQ);
    ui->HqTable->setColumnCount(11);
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
    ui->HqTable->setHorizontalHeaderLabels(headerHQ);
    //自动排列列的内容
    ui->HqTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //整行选中
    ui->HqTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //禁止编辑
    ui->HqTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //***************************委托表设置****************************************//
    //设置委托表格行列数量,行11行,10列
    ui->WtTable->setColumnCount(9);
    //ui->WtTable->setRowCount(10);

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
    ui->WtTable->setHorizontalHeaderLabels(headerWT);
    //自动排列列的内容
    ui->WtTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    //整行选中
    ui->WtTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    //禁止编辑
    ui->WtTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    //set up right click
    ui->WtTable->setContextMenuPolicy(Qt::CustomContextMenu);
    cancel_menu = new QMenu(ui->WtTable);
    QAction *action = new QAction("Cancel Order", this);
    connect(action, SIGNAL(triggered()), this, SLOT(cancelorder));
    cancel_menu->addAction(action);
    cancel_menu->addAction(action);



    //tdthread=new TdThread(this);
    tdthread->start();
    timer->start(1000);
    mdthread->start();

}
void CreateDlg::cancelorder()
{
    QMessageBox::information(this,"",QString::fromLocal8Bit("已提交撤单"));
    int i = ui->WtTable->currentIndex().row();
    QString wth=ui->WtTable->item(i,7)->text(); //委托号
    QString jsy=ui->WtTable->item(i,8)->text(); //交易所
    tdthread->td->ReqCancelOrder(wth,jsy);
    QMessageBox::information(this,"",QString::fromLocal8Bit("已提交撤单"));
}
void CreateDlg::ReceiveHQ(QString TICK)
{
    QStringList  strlist =TICK.split(",");	   //接收StringList数据
    //qDebug() << "Receive Hq!";
    //qDebug() << TICK;
  //循环传入的数据
  for (int i=0;i<ui->HqTable->rowCount();i++)   //以 HQTable数量为边界
  {
      if (ui->HqTable->item(i,0)->text()==strlist.at(0))
      {
          ui->HqTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
          ui->HqTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //更新数据
          ui->HqTable->setItem(i,2,new QTableWidgetItem(strlist.at(2)));	  //更新数据
          ui->HqTable->setItem(i,3,new QTableWidgetItem(strlist.at(3)));	  //更新数据
          ui->HqTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //更新数据
          ui->HqTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
          ui->HqTable->setItem(i,6,new QTableWidgetItem(strlist.at(6)));	  //更新数据
          ui->HqTable->setItem(i,7,new QTableWidgetItem(strlist.at(7)));	  //更新数据
          ui->HqTable->setItem(i,8,new QTableWidgetItem(strlist.at(8)));	  //更新数据
          ui->HqTable->setItem(i,9,new QTableWidgetItem(strlist.at(9)));	  //更新数据
          ui->HqTable->setItem(i,10,new QTableWidgetItem(strlist.at(10)));	  //更新数据

          return;
      }

  }
  int row = ui->HqTable->rowCount();
  ui->HqTable->insertRow(row);
  ui->HqTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
  ui->HqTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
  ui->HqTable->setItem(row,2,new QTableWidgetItem(strlist.at(2)));
  ui->HqTable->setItem(row,3,new QTableWidgetItem(strlist.at(3)));
  ui->HqTable->setItem(row,6,new QTableWidgetItem(strlist.at(4)));
  ui->HqTable->setItem(row,5,new QTableWidgetItem(strlist.at(5)));
  ui->HqTable->setItem(row,4,new QTableWidgetItem(strlist.at(6)));
  ui->HqTable->setItem(row,7,new QTableWidgetItem(strlist.at(7)));
  ui->HqTable->setItem(row,8,new QTableWidgetItem(strlist.at(8)));
  ui->HqTable->setItem(row,9,new QTableWidgetItem(strlist.at(9)));
  ui->HqTable->setItem(row,10,new QTableWidgetItem(strlist.at(10)));

}

void CreateDlg::ReceiveAutoHQ(QString TICK)
{
}

CreateDlg::~CreateDlg()
{
    delete ui;
}
void CreateDlg::querywork()
{
    static int pno =0;
    pno++;
    //qDebug() << "timer exec query work!";
    if (tdthread->td)
    {
        if (pno%1000==0)
            qDebug() << "td is inited!";
        //qDebug() << tdthread->td->HasWork();
        if(tdthread->td->HasWork())
        {
            qDebug() << "before do the work" ;
            CThostFtdcOrderField* tord = tdthread->td->FwdOrdResp();
            ParseWT(tord);
            qDebug() << "After do the work111" ;
            //qDebug() << QString(tord->UserID);
        }
    }
}
void CreateDlg::ClearInput()
{
    ui->le_symbol->clear();
    ui->le_price->clear();

}
void CreateDlg::onTrade(QString insertsql)
{
    int ret = 0;
    qDebug() << insertsql;
    //use binding I have to pass a lots params, so directly use sql string
    if(dbhelper.openstatus())
        ret = dbhelper.insert(insertsql);
    else
    {
        dbhelper.open();
        ret = dbhelper.insert(insertsql);
    }
    if (ret != 0)
    {
        //ClearInput();
        ui->te_log->setText("Inserted!");
    }
}

void CreateDlg::on_pb_order_clicked()
{
    QString insertsql,rmk1,rmk2,otimestr,strname,qty;
    QString dir,offset,prc,symbol,exc,dtstr,reqidstr;
    int ret = 0;
    QDate dt = QDate::currentDate();
    QTime tm = QTime::currentTime();
    otimestr = dt.toString(Qt::ISODate) +" ";
    otimestr = otimestr + tm.toString(Qt::ISODate);
    if (tm.hour() > 15)
        dt = dt.addDays(1);
    dtstr = dt.toString(Qt::ISODate);

    strname = ui->cb_strg->currentText();
    qty = ui->le_qty->text();
    dir = ui->cb_Dir->currentText();
    offset = ui->cb_offset->currentText();
    prc = ui->le_price->text();
    symbol = ui->le_symbol->text();
    exc = ui->cb_exch->currentText();

    insertsql = "INSERT INTO tradeorders";
    insertsql+= "(remark2,remark1,ordertime,strategyname,";
    insertsql+= "orderqty,orderdirection,orderoffset,";
    insertsql+= "entryprice,contract,exchangeid,orderdate)";
    insertsql+= "values ('"+rmk1+"','"+rmk2+"','"+otimestr+"','"+strname+"','"+qty;
    insertsql+= "','"+dir+"','"+offset+"','"+prc+"','"+symbol+"','"+exc+"','"+dtstr+"')";
    if (cnstatus)
    {
        std::cout << "start insert!" << std::endl;
        std::cout << offset.toStdString() << std::endl;
        tdthread->td->orderinsert(symbol.toStdString() ,dir.toStdString() ,offset.toStdString() ,exc.toStdString() ,prc.toDouble(),qty.toInt(),reqidstr.toInt());
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }
    else
    {
        // connect , login and so on
        ui->te_log->setText("not connected, reconnect!");
        tdthread->td->connectCtp();

    }

}

void CreateDlg::on_pb_reset_clicked()
{
    ClearInput();
}

void CreateDlg::ParseWT(CThostFtdcOrderField* pOrder)
{
    qDebug() << "Before get order return!" ;
    qDebug() << QString(pOrder->OrderStatus) ;

    //报单状态处理
    QString zt;
    if (!pOrder)
        return;
    if (pOrder->OrderStatus == '\0')
        return;
    if (pOrder->OrderStatus==THOST_FTDC_OST_AllTraded)
    {
        zt=QString::fromLocal8Bit("全部成交");
    }else if(pOrder->OrderStatus==THOST_FTDC_OST_PartTradedQueueing)
    {
        zt=QString::fromLocal8Bit("部分成交");
    }
    else if (pOrder->OrderStatus==THOST_FTDC_OST_PartTradedNotQueueing)
    {
        zt=QString::fromLocal8Bit("部分成交");
    }
    else if (pOrder->OrderStatus==THOST_FTDC_OST_NoTradeQueueing)
    {
        zt=QString::fromLocal8Bit("未成交");
    }
    else if (pOrder->OrderStatus==THOST_FTDC_OST_Canceled)
    {
        zt=QString::fromLocal8Bit("已撤单");
    }


      QString wttime = pOrder->InsertTime; //委托时间
      QString dm = pOrder->InstrumentID; //委托代码
      QString bs = QChar::fromLatin1(pOrder->Direction); //买卖方向
      QString kp=pOrder->CombOffsetFlag; //开平标志
      QString lots = QString::number(pOrder->VolumeTotalOriginal); //数量
      QString price = QString::number(pOrder->LimitPrice); //价格
      //QString zt=pOrder->OrderStatus; //报单状态
      QString wth = pOrder->OrderSysID; //委托号
      QString jsy=pOrder->ExchangeID; //交易所

      QString WTData=wttime+","+dm+","+bs+","+kp+","+lots+","+price+","+zt+","+wth+","+jsy;
      //qDebug() << WTData;

      emit uisendWT(WTData);
      qDebug() << "emit signals";

}

void CreateDlg::ReceiveWT(QString WTData)
{

     qDebug() << "Receiving!" ;
     qDebug() << WTData;

     QStringList strlist = WTData.split(",");
     qDebug() << strlist;
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
     for (int i=0;i<ui->WtTable->rowCount();i++)   //以 WTTable数量为边界
     {
         //the guy I refer use timestamp as key, should use order refer instead
         if (ui->WtTable->item(i,0)->text()==strlist.at(0))
         {

             ui->WtTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
             ui->WtTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //更新数据
             ui->WtTable->setItem(i,2,new QTableWidgetItem(buysell));	  //更新数据
             ui->WtTable->setItem(i,3,new QTableWidgetItem(openclose));	  //更新数据
             ui->WtTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //更新数据
             ui->WtTable->setItem(i,5,new QTableWidgetItem(strlist.at(5)));	  //更新数据
             ui->WtTable->setItem(i,6,new QTableWidgetItem(strlist.at(6)));	  //更新数据
             ui->WtTable->setItem(i,7,new QTableWidgetItem(strlist.at(7)));	  //更新数据
             ui->WtTable->setItem(i,8,new QTableWidgetItem(strlist.at(8)));	  //更新数据

             return;
         }

     }


     int row=ui->WtTable->rowCount();
     ui->WtTable->insertRow(row);
     ui->WtTable->setItem(row,0,new QTableWidgetItem(strlist.at(0)));
     ui->WtTable->setItem(row,1,new QTableWidgetItem(strlist.at(1)));
     ui->WtTable->setItem(row,2,new QTableWidgetItem(buysell));
     ui->WtTable->setItem(row,3,new QTableWidgetItem(openclose));
     ui->WtTable->setItem(row,4,new QTableWidgetItem(strlist.at(4)));
     ui->WtTable->setItem(row,5,new QTableWidgetItem(strlist.at(5)));
     ui->WtTable->setItem(row,6,new QTableWidgetItem(strlist.at(6)));
     ui->WtTable->setItem(row,7,new QTableWidgetItem(strlist.at(7)));
     ui->WtTable->setItem(row,8,new QTableWidgetItem(strlist.at(8)));

     qDebug() << "After Receiving" ;

}


void CreateDlg::ConnActs()
{

    cnstatus = tdthread->td->is_connected();
    if (!cnstatus)
    {
        tdthread->td->connectCtp();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    if(cnstatus)
    {
        //init activities
        tdthread->td->settlementinfoConfirm();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        tdthread->td->qryInstrument();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        ui->te_log->setText("CTP Ready!");
    }
    else
        ui->te_log->setText("Cannot Connect to CTP!");
}
void CreateDlg::on_pb_ctp_clicked()
{
    ConnActs();
}

void CreateDlg::on_pb_db_clicked()
{
    QString insertsql,rmk1,rmk2,otimestr,strname,qty;
    QString dir,offset,prc,symbol,exc,dtstr,reqidstr;
    QDate dt = QDate::currentDate();
    QTime tm = QTime::currentTime();
    otimestr = dt.toString(Qt::ISODate) +" ";
    otimestr = otimestr + tm.toString(Qt::ISODate);
    if (tm.hour() > 15)
        dt = dt.addDays(1);
    dtstr = dt.toString(Qt::ISODate);

    strname = ui->cb_strg->currentText();
    qty = ui->le_qty->text();
    dir = ui->cb_Dir->currentText();
    offset = ui->cb_offset->currentText();
    prc = ui->le_price->text();
    symbol = ui->le_symbol->text();
    exc = ui->cb_exch->currentText();
    rmk1 = "";
    rmk2 = "";
    insertsql = "INSERT INTO tradeorders";
    insertsql+= "(remark2,remark1,ordertime,strategyname,";
    insertsql+= "orderqty,orderdirection,orderoffset,";
    insertsql+= "entryprice,contract,exchangeid,orderdate)";
    insertsql+= "values ('"+rmk1+"','"+rmk2+"','"+otimestr+"','"+strname+"','"+qty;
    insertsql+= "','"+dir+"','"+offset+"','"+prc+"','"+symbol+"','"+exc+"','"+dtstr+"')";
    emit LogOrder(insertsql);


}

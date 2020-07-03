#include "createdlg.h"
#include "ui_createdlg.h"

CreateDlg::CreateDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDlg)
    , dbhelper("/home/leon/sqllitedb/tradelog_vnpy.db")
    ,mktdata("")
    , cnstatus(true)
{
    tdthread = new TdThread(this);
    ui->setupUi(this);
    ui->cb_Dir->addItem("多");
    ui->cb_Dir->addItem("空");
    ui->cb_offset->addItems({"开仓","平仓","平昨","平今"});
    //qDebug() << dbhelper. getMaxId();
    ui->cb_strg->addItems({"DT_IntraDayCommonStrategy","TurtleUseCloseStrategy","JDualThrust_IntraDayStrategy"});
    ui->cb_exch->addItems({"SHFE","DCE","CZCE","CFFEX","INE"});
    connect(this, SIGNAL(LogOrder(QString)), this, SLOT(onTrade(QString) ));

    //if (tdthread->td)
    connect(tdthread->td,SIGNAL(QTd::sendWT(QString)),this,SLOT(CreateDlg::ReceiveWT(QString)),Qt::QueuedConnection);
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(querywork()),Qt::QueuedConnection);
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
    tdthread=new TdThread(this);
    tdthread->start();
    timer->start(1000);

}
CreateDlg::~CreateDlg()
{
    delete ui;
}
void CreateDlg::querywork()
{
    //qDebug() << "timer exec query work!";
    if (tdthread->td)
    {
        //qDebug() << "td is inited!";
        if(tdthread->td->HasWork())
        {
            qDebug() << "before do the work" ;
            tdthread->td->FwdOrdResp();
            qDebug() << "After do the work111" ;
        }
    }
}
void CreateDlg::ClearInput()
{
    ui->le_symbol->clear();
    ui->le_price->clear();
    ui->te_log->clear();
    ui->te_rmk1->clear();
    ui->te_rmk2->clear();
    ui->te_log->clear();
    ui->le_qty->clear();
    ui->le_reqid->clear();

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

    rmk1 = ui->te_rmk1->toPlainText();
    rmk2 = ui->te_rmk2->toPlainText();
    strname = ui->cb_strg->currentText();
    qty = ui->le_qty->text();
    dir = ui->cb_Dir->currentText();
    offset = ui->cb_offset->currentText();
    prc = ui->le_price->text();
    symbol = ui->le_symbol->text();
    exc = ui->cb_exch->currentText();
    reqidstr = ui->le_reqid->text();

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

void CreateDlg::ReceiveWT(QString WTData)
{
     qDebug() << "Receiving!" ;
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
     for (int i=0;i<ui->WtTable->rowCount();i++)   //以 WTTable数量为边界
     {
         if (ui->WtTable->item(i,0)->text()==strlist.at(0))
         {

             ui->WtTable->setItem(i,0,new QTableWidgetItem(strlist.at(0)));	  //更新数据
             ui->WtTable->setItem(i,1,new QTableWidgetItem(strlist.at(1)));	  //更新数据
             ui->WtTable->setItem(i,2,new QTableWidgetItem(buysell));	  //更新数据
             ui->WtTable->setItem(i,3,new QTableWidgetItem(openclose));	  //更新数据
             ui->WtTable->setItem(i,4,new QTableWidgetItem(strlist.at(4)));	  //更新数据
             ui->WtTable->setItem(i,5,new QTableWidgetItem(strlist.at(6)));	  //更新数据
             ui->WtTable->setItem(i,6,new QTableWidgetItem(strlist.at(7)));	  //更新数据
             ui->WtTable->setItem(i,7,new QTableWidgetItem(strlist.at(8)));	  //更新数据
             ui->WtTable->setItem(i,8,new QTableWidgetItem(strlist.at(9)));	  //更新数据

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
     ui->WtTable->setItem(row,5,new QTableWidgetItem(strlist.at(6)));
     ui->WtTable->setItem(row,6,new QTableWidgetItem(strlist.at(7)));
     ui->WtTable->setItem(row,7,new QTableWidgetItem(strlist.at(8)));
     ui->WtTable->setItem(row,8,new QTableWidgetItem(strlist.at(9)));

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

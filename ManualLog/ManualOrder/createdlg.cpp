#include "createdlg.h"
#include "ui_createdlg.h"

CreateDlg::CreateDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateDlg)
    , dbhelper("/home/leon/sqllitedb/tradelog_vnpy.db")
    , trade("./cfg/j123.json")
    , cnstatus(false)
{
    ui->setupUi(this);
    ui->cb_Dir->addItem("多");
    ui->cb_Dir->addItem("空");
    ui->cb_offset->addItems({"开","平"});
    //qDebug() << dbhelper. getMaxId();
    ui->cb_strg->addItems({"DT_IntraDayCommonStrategy","TurtleUseCloseStrategy","JDualThrust_IntraDayStrategy"});
    ui->cb_exch->addItems({"SHFE","DCE","CZCE","CFFEX","INE"});
    connect(this, SIGNAL(LogOrder(QString)), this, SLOT(onTrade(QString) ));
}

CreateDlg::~CreateDlg()
{
    delete ui;
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
        ClearInput();
        ui->te_log->setText("Inserted!");
    }
}

void CreateDlg::on_pb_order_clicked()
{
    QString insertsql,rmk1,rmk2,otimestr,strname,qty;
    QString dir,offset,prc,symbol,exc,dtstr;
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

    insertsql = "INSERT INTO tradeorders";
    insertsql+= "(remark2,remark1,ordertime,strategyname,";
    insertsql+= "orderqty,orderdirection,orderoffset,";
    insertsql+= "entryprice,contract,exchangeid,orderdate)";
    insertsql+= "values ('"+rmk1+"','"+rmk2+"','"+otimestr+"','"+strname+"','"+qty;
    insertsql+= "','"+dir+"','"+offset+"','"+prc+"','"+symbol+"','"+exc+"','"+dtstr+"')";
    if (cnstatus)
    {
        trade.orderinsert(symbol.toStdString() ,dir.toStdString() ,offset.toStdString() ,exc.toStdString() ,prc.toDouble(),qty.toInt());
        std::this_thread::sleep_for(std::chrono::seconds(5));
        //want to trigger signal within OnRtnTrade event of trade
        // However, did not find a easy way to work it out without inheriate from QObject.
        //temporary solution is insert log 5 seconds later.
        int countdown = 120;
        bool isbreak = false;
        while(!trade.is_goodorder())
        {

            std::this_thread::sleep_for(std::chrono::seconds(1));
            ++countdown;
            if (countdown >120)
                isbreak = true;
        }
        if (!isbreak)
            emit LogOrder(insertsql);

    }
    else
    {
        // connect , login and so on
        ui->te_log->setText("not connected, reconnect!");
        trade.connect();

    }

}

void CreateDlg::on_pb_reset_clicked()
{
    ClearInput();
}
void CreateDlg::ConnActs()
{
    trade.connect();
    std::this_thread::sleep_for(std::chrono::seconds(3));
    cnstatus = trade.is_connected();
    if (!cnstatus)
    {
        trade.connect();
        std::this_thread::sleep_for(std::chrono::seconds(3));
    }
    if(cnstatus)
    {
        //init activities
        trade.settlementinfoConfirm();
        std::this_thread::sleep_for(std::chrono::seconds(2));
        trade.qryInstrument();
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

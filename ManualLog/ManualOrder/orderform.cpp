#include "orderform.h"
#include "ui_orderform.h"
#include <QDebug>
OrderForm::OrderForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderForm)
    , dbhelper("/home/leon/sqllitedb/tradelog_vnpy.db")

{
    ui->setupUi(this);
    ui->cb_Dir->addItem("多");
    ui->cb_Dir->addItem("空");
    ui->cb_offset->addItems({"开","平"});
    //qDebug() << dbhelper.getMaxId();
    ui->cb_strg->addItems({"DT_IntraDayCommonStrategy","TurtleUseCloseStrategy","JDualThrust_IntraDayStrategy"});
    ui->cb_exch->addItems({"XSGE","XDCE","XZCE","XSIE"});
}

OrderForm::~OrderForm()
{
    delete ui;
}

void OrderForm::ClearInput()
{
    ui->le_symbol->clear();
    ui->le_price->clear();
    ui->te_log->clear();
    ui->te_rmk1->clear();
    ui->te_rmk2->clear();
    ui->te_log->clear();
    ui->le_qty->clear();

}
void OrderForm::on_pb_order_clicked()
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

void OrderForm::on_pb_reset_clicked()
{
    ClearInput();

}

void OrderForm::on_pb_del_clicked()
{
    QString orderid = ui->le_del->text();
    QString sqlstr = "Delete from tradeorders where orderid = "+orderid;
    int ret = 0;
    qDebug() << sqlstr;
    //use binding I have to pass a lots params, so directly use sql string
    if(dbhelper.openstatus())
        ret = dbhelper.remove(sqlstr);
    else
    {
        dbhelper.open();
        ret = dbhelper.remove(sqlstr);
    }
    if (ret != 0)
    {
        ClearInput();
        ui->te_log->setText("Deleted!");
    }
}

void OrderForm::on_pushButton_clicked()
{
    //test ctp connection
    TradeWrapper tr("./cfg/j123.json");
    std::cout << "wrapper created!" << std::endl;
    tr.connect();
    //test finish, exit
    std::this_thread::sleep_for(std::chrono::seconds(20));//Sleep(1000);
    tr.release();

}

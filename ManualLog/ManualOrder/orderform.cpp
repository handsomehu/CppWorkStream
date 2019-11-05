#include "orderform.h"
#include "ui_orderform.h"

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
    ui->cb_exch->addItems({"sqs","dss","zzs"});
}

OrderForm::~OrderForm()
{
    delete ui;
}


void OrderForm::on_pb_order_clicked()
{
    QString insertsql,rmk1,rmk2,otime,strname,qty;
    QString dir,offset,prc,symbol,exc,dt;
    rmk1 = ui->te_rmk1->toPlainText();
    rmk2 = ui->te_rmk2->toPlainText();
    //strname = ui->cb_strg->sele
    insertsql = "INSERT INTO tradeorders";
    insertsql+= "(remark2,remark1,ordertime,strategyname,";
    insertsql+= "orderqty,orderdirection,orderoffset,";
    insertsql+= "entryprice,contract,exchangeid,orderdate)";
    insertsql+= "values (:rmk1,:rmk2,:otime,:strname,:qty";
    insertsql+= ",:dir,:offset,:prc,:symbol,:exc,:dt)";
    //use binding I have to pass a lots params, so directly use sql string

}

void OrderForm::on_pb_reset_clicked()
{
    ui->le_symbol->setText("");
    ui->le_price->setText("");
    ui->te_log->setText("");
    ui->te_rmk1->setText("");
    ui->te_rmk2->setText("");
    //ui->te_infor->setText("");

}

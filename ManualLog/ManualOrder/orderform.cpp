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
}

OrderForm::~OrderForm()
{
    delete ui;
}


void OrderForm::on_pb_order_clicked()
{
    ui->te_infor->setText("Here we are ordering for " + ui->le_symbol->text()+dbhelper.getMaxId("tradeorders"));
}

void OrderForm::on_pb_reset_clicked()
{
    ui->le_symbol->setText("");
    ui->le_price->setText("");
    ui->te_infor->setText("");
}

#include "removedlg.h"
#include "ui_removedlg.h"

RemoveDlg::RemoveDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoveDlg)
    , dbhelper("/home/leon/sqllitedb/tradelog_vnpy.db")
    //, trade("./cfg/j123.json")
    , cnstatus(false)
{
    ui->setupUi(this);
}

RemoveDlg::~RemoveDlg()
{
    delete ui;
}

void RemoveDlg::on_pb_del_clicked()
{
    //QString ddd = ui->le_del->text();
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
        //ClearInput();
        ui->label_infor->setText("Log Removed!");
    }
    else
        ui->label_infor->setText("Removing failed,please check");
}

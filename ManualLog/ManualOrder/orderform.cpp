#include "orderform.h"
#include "ui_orderform.h"
#include <QDebug>
OrderForm::OrderForm(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::OrderForm)

{
    ui->setupUi(this);
}

OrderForm::~OrderForm()
{
    delete ui;
}

void OrderForm::on_actionCreate_triggered()
{
    QDialog *newtrade = new CreateDlg(this);
    newtrade->show();
    newtrade->exec();

}

void OrderForm::on_actionRemove_triggered()
{
    QDialog *deltrade = new  RemoveDlg(this);
    deltrade->show();
}

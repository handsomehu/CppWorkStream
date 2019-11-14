#include "myform.h"
#include "ui_myform.h"

myForm::myForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::myForm)
{
    ui->setupUi(this);
}

myForm::~myForm()
{
    delete ui;
}

void myForm::on_pushButton_clicked()
{
    emit SendData(ui->lineEdit->text());
    this->close();
}

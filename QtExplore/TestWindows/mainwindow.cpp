#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //QAction::triggered()

    //connect(padd,SINGAL(triggered(bool)),this,SLOT(onAddpress()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    QDialog *dlg = new QDialog(this);
    dlg->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    myForm *form = new myForm(this);
    connect(form, SIGNAL(SendData(QString)),this,SLOT(ReceieveData(QString)));
    form->exec();
}

void MainWindow::ReceieveData(QString Data)
{
    ui->lineEdit->setText(Data);
}



#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //新增主菜单
    QMenu* menu = ui->menubar->addMenu(tr("CodeMenu"));
    //创建子菜单
    QAction* subCodeMenuAction = new QAction(tr("subCodeMenu"),this);
    //把子菜单和父菜单关联
    menu->addAction(subCodeMenuAction);
    //添加信号槽
    connect(subCodeMenuAction,SIGNAL(QAction::triggered(bool)),this,SLOT(clickSubCodeMenuAction(bool)));

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    std::cout << "test" << std::endl;
}

void MainWindow::clickSubCodeMenuAction(bool checked)
{
    std::cout << "menu pressed!" << std::endl;
}

void MainWindow::on_actionadd_triggered(bool checked)
{
    std::cout << "generated!" << std::endl;
}

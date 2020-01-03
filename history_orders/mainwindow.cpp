#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_query_clicked()
{
    std::string cfgpath = "./cfg/j123.json";
    std::vector<std::string> vdate{"20191230","20191231","20200102"};
    bool cnstatus = 0;
    //= trader.is_connected();
    TradeWrapper trader{cfgpath};
    trader.connect();
    std::this_thread::sleep_for(std::chrono::seconds(10));
    cnstatus = trader.is_connected();
    std::cout << "before connect" << std::endl;
    if (cnstatus)
    {
        std::cout << "connected" << std::endl;
        for (auto dt:vdate)
        {

            trader.qrySettlement(dt);
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::cout << dt << std::endl;
        }


    }



}

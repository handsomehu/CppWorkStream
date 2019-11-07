#include <QCoreApplication>
#include "ctraderhandler.h"
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    CTraderHandler *trader = new CTraderHandler();

    trader->connect();

    std::this_thread::sleep_for(std::chrono::seconds(2));//Sleep(1000);//Sleep(2000);

    trader->login();

    std::this_thread::sleep_for(std::chrono::seconds(2));//Sleep(1000);//Sleep(2000);

    trader->settlementinfoConfirm();

    std::this_thread::sleep_for(std::chrono::seconds(2));//Sleep(1000);//Sleep(2000);

    trader->qryInstrument();

    std::this_thread::sleep_for(std::chrono::seconds(2));//Sleep(1000);//Sleep(2000);

    trader->orderinsert();

    std::this_thread::sleep_for(std::chrono::seconds(1000));//Sleep(1000);//Sleep(2000);//Sleep(INFINITE);

    return 1;
    return a.exec();
}

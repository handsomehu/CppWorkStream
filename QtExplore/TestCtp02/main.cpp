#include <QCoreApplication>
#include <chrono>
#include "tradewrapper.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    TradeWrapper td("./cfg/j123.json");
    td.connect();
    std::this_thread::sleep_for(std::chrono::seconds(6));
    if(td.is_connected())
    {
        td.settlementinfoConfirm();
        std::this_thread::sleep_for(std::chrono::seconds(3));
        std::cout << "confirmed!" << std::endl;
        td.orderinsert("rb2001","多","开","SHFE",3620,1);
        std::this_thread::sleep_for(std::chrono::seconds(30));
        //td.qryInstrument();
    }
    td.release();
    std::cout << "released!" << std::endl;
    return a.exec();
}

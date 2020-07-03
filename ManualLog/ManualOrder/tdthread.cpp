#include "tdthread.h"
#include "qtd.h"

TdThread::TdThread(QObject *parent)
{
    td = new QTd{parent, "./cfg/j123.json"};
}


void TdThread::run()
{

    td->connectCtp();

    QThread::sleep(3);
    td->settlementinfoConfirm();

    //std::this_thread::sleep_for(std::chrono::seconds(2));
    td->qryInstrument();

//    while(true)
//    {
//        dowork();
//        std::this_thread::sleep_for(std::chrono:: milliseconds (100));

//    }



}

void TdThread::dowork()
{
    while(td->HasWork())
    {
        qDebug() << "before do the work" ;
        td->FwdOrdResp();
        qDebug() << "After do the work" ;
    }
}

//============================================================================
// Name        : average_price.cpp
// Author      : Leon Zhao
// Version     : 0.1
// Copyright   : Initial
// Description : C++ Journey Begin, Wow!
//============================================================================

#include <QCoreApplication>
#include "mdWrapper.h"

/*
#include <limits.h>
#include <unistd.h>
std::string getexepath()
{
  char result[ PATH_MAX ];
  ssize_t count = readlink( "/proc/self/exe", result, PATH_MAX );
  return std::string( result, (count > 0) ? count : 0 );
}
*/
std::string GetTradingDay()
{
    return "20191108";
}
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    {
        //DbHelper dh;
        //int ret = dh.PersistVwap("20190804","rb2001",3420,1000);
        //std::cout << ret << std::endl;
    }

    // Create a std::promise object
    std::promise<void> exitSignal;

    //Fetch std::future object associated with promise
    std::future<void> futureObj = exitSignal.get_future();

    // Starting Thread & move the future object in lambda function by reference
    //std::thread th(&threadFunction, std::move(futureObj));

    static int trycnt = 0;
    static bool loginOK = false;
    std::vector<char*> symbollist = {"rb2005","i2005","MA005"};
    std::cout << "C++ CTP Journey Begin, Wow!" << std::endl;
    std::shared_ptr<CmdWrapper> mdApi = std::make_shared<CmdWrapper>();
    //std::cout << getexepath() << std::endl;
    mdApi->connect();
    while(trycnt < 10)
    {
        loginOK = mdApi->getloginstatus();
        if (!loginOK)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            trycnt ++;
            std::cout <<"Tried to login times:";
            std::cout << trycnt <<std::endl;
        }
        else
            break;
    }


    if (loginOK)
    {
        mdApi->subscribe(symbollist);
        std::thread processqueue(&CmdWrapper::ProcessTaskFromQueue,mdApi,std::move(futureObj));
        //std::thread setfin(&CmdWrapper::SetComplete,mdApi);
        std::thread printvwap(&CmdWrapper::persistvwap,mdApi);
        //void CmdWrapper::persistvwap()

        //send stop signal:
        mdApi->SetComplete();
        exitSignal.set_value();
        processqueue.join();
        std::cout << "process queue joined" << std::endl;
        //setfin.join();
        mdApi->apijoin();  //will continue run if uncommented
                             //will terminate and have dump if commented out
        //mdApi->getavg() ;
        std::cout << "exit, next cmd is apirelease to terminate" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1000*60*2));
        mdApi->apirelease();


    }
    else
        std::cout << "Cannot login to the system, please check!" << std::endl;

    /*
    nlohmann::json jtest;
    jtest["hello"] = "World";
    jtest["url"] = "github.com";
    std::ofstream file("key.json");
    file << jtest;
     */

    return a.exec();
}



/*
#include <vector>
#include <string>
#include <iostream>
#include "sqlite3.h"
//using namespace std;

sqlite3* db;

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
  Records* records = static_cast<Records*>(p_data);
  try {
    records->emplace_back(p_fields, p_fields + num_fields);
  }
  catch (...) {
    // abort select on failure, don't let exception propogate thru sqlite3 call-stack
    return 1;
  }
  return 0;
}

Records select_stmt(const char* stmt)
{
  Records records;
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
  else {
    std::cerr << records.size() << " records returned.\n";
  }

  return records;
}

void sql_stmt(const char* stmt)
{
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
}

int main()
{
  if (sqlite3_open("test.db", &db) != SQLITE_OK) {
    std::cerr << "Could not open database.\n";
    return 1;
  }

  Records records = select_stmt("SELECT * FROM test");
  sqlite3_close(db);

  for (auto& record : records) {
    // do something with your records
  }

  return 0;
}

 */

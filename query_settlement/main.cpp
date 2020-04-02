#include <iostream>
#include <fstream>
#include <ctime>
#include <iomanip>
#include <sstream>
//#include <codecvt>
#include "tradewrapper.h"



//extern int GbkToUtf8(char *str_str, size_t src_len, char *dst_str, size_t dst_len);
//extern int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len);
std::vector<std::string>&& getdate()
{
    std::vector<std::string> dates{};
    struct tm date;

    date.tm_mon = 0;
    date.tm_mday = 2;
    date.tm_year = 2020-1900;
    std::ostringstream os;
    os << std::put_time(&date, "%Y%m%d");
    //std::cout << os.str() << std::endl;

    time_t end = time(nullptr);
    std::string tmp{""};

    for (; mktime(&date) < end; ++date.tm_mday) {

        char buffer[16];

        strftime(buffer, sizeof(buffer), "%Y%m%d", &date);
        tmp = buffer;
        //std::cout << tmp << "\n";

        dates.push_back(tmp);
        //break;
    }
    return std::move(dates);

}

void getdate(std::vector<std::string>& dates)
{

    struct tm date;

    date.tm_mon = 0;
    date.tm_mday = 1;
    date.tm_year = 2018 - 1900;
    time_t end = time(nullptr);

    for (; mktime(&date) < end; ++date.tm_mday) {
        char buffer[16];
        strftime(buffer, sizeof(buffer), "%Y%m%d", &date);
        std::cout << buffer << "\n";
        dates.push_back(std::string(buffer));
        //break;
    }
    //return std::move(dates);

}

int main()
{
    TradeWrapper api("./cfg/j123.json");
    api.connect();
    std::this_thread::sleep_for(std::chrono::seconds(5));
      // array to hold the result.
    //char oneline[501];
    std::vector<std::string> datelist=getdate();
    for(auto a:datelist)
    {
        std::string t = a;
        std::cout << "aaa\t" << a << std::endl;
    }
    char resultsets[2000001]{0};
    char dst_utf8_set[2000001] = {0};
    int ixx = 0;
    for(std::string dt:datelist)
    {
        std::cout << ++ixx << std::endl;
        std::cout << "date is 0\t" << dt << std::endl;
        api.qrySettlement(dt);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto rst = api.getsettlements();



        char ts1[501]{0};
        //resultsets[0]='\0';
        strcpy(resultsets,ts1);
        memset(resultsets,'\0',sizeof(resultsets));
        memset(dst_utf8_set,'\0',sizeof(dst_utf8_set));
        if (rst.size()==0)
        {
            std::cout << "no data for " << dt << std::endl;
            continue;
        }
        for(auto part:rst)
        {
            //strcpy(oneline,part);
            std::copy(part.get(),part.get()+501,ts1);
            strcat(resultsets,ts1);//not safe, find a way to fix it later.

        }

        GbkToUtf8(resultsets, strlen(resultsets), dst_utf8_set, sizeof(dst_utf8_set));
        //std::cout << "gbk to utf8: " << dst_utf8_set << std::endl;
        std::cout << "date is " << dt << "all good " << std::endl;
        std::string fname = "./data/trade_"+dt+".txt";
        std::cout << "before write to file" << std::endl;
        std::ofstream os(fname);
        os << dst_utf8_set;
        std::cout << "after write to file" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));

        //break;


    }
    //std::Sleep(INFINITE);
    std::cout << "finish it" << std::endl;
    return 0;
}

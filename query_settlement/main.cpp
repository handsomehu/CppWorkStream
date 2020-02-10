#include <iostream>
#include <fstream>
//#include <codecvt>
#include "tradewrapper.h"



//extern int GbkToUtf8(char *str_str, size_t src_len, char *dst_str, size_t dst_len);
//extern int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len);

int main()
{
    std::vector<std::string> datelist{"20200123","20200203"};
    TradeWrapper api("./cfg/j123.json");
    api.connect();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    char resultsets[200001];   // array to hold the result.
    //char oneline[501];
    for(auto dt:datelist)
    {
        api.qrySettlement(dt);
        std::this_thread::sleep_for(std::chrono::seconds(2));
        auto rst = api.getsettlements();


        char ts1[501]{0};
        //resultsets[0]='\0';
        strcpy(resultsets,ts1);
        for(auto part:rst)
        {
            //strcpy(oneline,part);
            std::copy(part.get(),part.get()+501,ts1);
            strcat(resultsets,ts1);//not safe, find a way to fix it later.

        }
        char dst_utf8_set[200001] = {0};
        GbkToUtf8(resultsets, strlen(resultsets), dst_utf8_set, sizeof(dst_utf8_set));
        //std::cout << "gbk to utf8: " << dst_utf8_set << std::endl;
        std::string fname = "./data/trade_"+dt+".txt";
        std::ofstream os(fname);
        os << dst_utf8_set;
        std::this_thread::sleep_for(std::chrono::seconds(1));


    }
    std::cout << "finish it" << std::endl;
    return 0;
}

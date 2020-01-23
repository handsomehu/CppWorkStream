#include <iostream>
#include <fstream>
//#include <codecvt>
#include "tradewrapper.h"



//extern int GbkToUtf8(char *str_str, size_t src_len, char *dst_str, size_t dst_len);
//extern int Utf8ToGbk(char *src_str, size_t src_len, char *dst_str, size_t dst_len);

int main()
{

    //wchar_t z = L'中';

    //std::ios::sync_with_stdio(false);
    //std::wcout.imbue(std::locale("zh_CN.UTF-8"));
    //std::wcout << z << '\n';    // ??

    char *src_str = "葡萄美酒夜光杯";
    std::cout << "origin string: " << src_str << std::endl;

    // unix default is utf8
    char dst_gbk[1024] = {0};
    Utf8ToGbk(src_str, strlen(src_str), dst_gbk, sizeof(dst_gbk));
    std::cout << "utf8 to gbk: " << dst_gbk << std::endl;

    char dst_utf8[1024] = {0};
    GbkToUtf8(dst_gbk, strlen(dst_gbk), dst_utf8, sizeof(dst_utf8));
    std::cout << "gbk to utf8: " << dst_utf8 << std::endl;

    std::ifstream ifs("./t1.txt");
    char gbkstr[1024];
    while(ifs)
    {
        ifs >> gbkstr;
        GbkToUtf8(gbkstr, strlen(gbkstr), dst_utf8, sizeof(dst_utf8));
        std::cout << std::string(dst_utf8) << std::endl ;
    }
    return 0;



    //return 0;

    std::vector<std::string> datelist{"20200120","20200121","20200122","20200123"};
    TradeWrapper api("./cfg/j123.json");
    api.connect();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for(auto dt:datelist)
    {
        api.qrySettlement(dt);
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }

    auto rst = api.getsettlements();
    for (auto set:rst)
    {
        for(auto part:set)
            std::cout << part ;
        std::wcout << std::endl;
    }

    std::cout << "finish it" << std::endl;
    return 0;
}

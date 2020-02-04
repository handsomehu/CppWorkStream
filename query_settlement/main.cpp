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
    //return 0;



    //return 0;

    std::vector<std::string> datelist{"20200123","20200203"};
    TradeWrapper api("./cfg/j123.json");
    api.connect();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    for(auto dt:datelist)
    {
        api.qrySettlement(dt);
        std::this_thread::sleep_for(std::chrono::seconds(2));

    }

    char resultsets[200001];   // array to hold the result.
    char oneline[501];
    //strcpy(result,one); // copy string one into the result.
     // append string two to the result.
    auto rst = api.getsettlements();
    nlohmann::json jsonj;
    //jsonj["data"]=rst;
    //std::ofstream os1("test_all.json");
    //os1 << jsonj.dump(0) << std::endl;
    int iii=0,jjj=0;
    for (auto set:rst)
    {

        std::cout << ++iii << std::endl;
        char ts1[501]{0};
        //resultsets[0]='\0';
        strcpy(resultsets,ts1);
        for(auto part:set)
        {
            //strcpy(oneline,part);
            std::copy(part.get(),part.get()+501,ts1);
            strcat(resultsets,ts1);//not safe, find a way to fix it later.
            std::cout << ++jjj << std::endl;
            std::cout << "size of: " << sizeof(part) << std::endl;
            std::cout << part << std::endl;
        }
        std::cout << resultsets << std::endl;
        char dst_utf8_set[200001] = {0};
        GbkToUtf8(resultsets, strlen(resultsets), dst_utf8_set, sizeof(dst_utf8_set));
        std::cout << "gbk to utf8: " << dst_utf8_set << std::endl;
        std::string fname = "./data/trade_"+std::to_string(iii)+".txt";
        std::ofstream os(fname);
        os << fname;

    }

    std::cout << "finish it" << std::endl;
    return 0;
}

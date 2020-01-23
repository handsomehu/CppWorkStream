#include <iostream>
#include <codecvt>
#include "tradewrapper.h"

int main()
{

    wchar_t z = L'中';

    std::ios::sync_with_stdio(false);
    std::wcout.imbue(std::locale("zh_CN.UTF-8"));
    std::wcout << z << '\n';    // ??


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
            std::wcout << part ;
        std::wcout << std::endl;
    }

    std::cout << "finish it" << std::endl;
    return 0;
}

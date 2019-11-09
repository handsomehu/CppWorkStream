#ifndef BAR_H
#define BAR_H
#include <string>
struct BarStruct
{
    std::string tradeday;
    std::string symbol;
    std::string exchangeid;
    double baropen,barhigh,barlow,barclose;
    int volumn, openintrest,tickcnt;
    double twap,vwap;
};
struct TickStruct
{
    double lastprice;
    int volumn,openintrest;
};

class Bar
{
public:
    Bar()=default;
    Bar(const std::string &tradeday,const std::string &symbol);
    Bar(const std::string &tradeday,const BarStruct &logbar);
    void NewTick(const TickStruct &tick);
private:
    std::string tradeday,symbol, exchangeid;
    double baropen,barhigh,barlow,barclose;
    int volumn, openintrest,tickcnt;
    double twap,vwap;


};

#endif // BAR_H

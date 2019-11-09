#include "bar.h"

Bar::Bar(const std::string &tradeday,const std::string &symbol)
    :tradeday(tradeday),symbol(symbol), exchangeid("")
    ,baropen(0),barhigh(0),barlow(0),barclose(0),
    volumn(0), openintrest(0), tickcnt(0),twap(0),vwap(0)
{

}

Bar::Bar(const std::string &tradeday,const BarStruct &logbar)
    :tradeday(tradeday),symbol(logbar.symbol), exchangeid(logbar.symbol),
    baropen(logbar.baropen),barhigh(logbar.barhigh),
    barlow(logbar.barlow),barclose(logbar.barclose),
    volumn(logbar.volumn), openintrest(logbar.openintrest),
    tickcnt(logbar.tickcnt),twap(logbar.twap),vwap(logbar.vwap)
{
    if (tradeday != logbar.tradeday)
    {
        baropen = 0;
        barhigh = 0 ;
        barlow = 0;
        barclose = 0;
        volumn = 0;
        openintrest = 0;
        tickcnt = 0;
        twap = 0;
        vwap = 0;
    }

}

void Bar::NewTick(const TickStruct &tick)
{
    double vavg = 0,tavg = 0;
    if (tick.lastprice > barhigh)
        barhigh = tick.lastprice;
    else if (tick.lastprice < barlow)
        barlow = tick.lastprice;
    barclose = tick.lastprice;
    openintrest = tick.openintrest;

    if (baropen != 0)
    {


        vavg = vwap * volumn + tick.lastprice * tick.volumn;
        tavg = twap * tickcnt + tick.lastprice;
        volumn += tick.volumn;
        tickcnt += 1;
        vwap  = vavg / volumn;
        twap = tavg/tickcnt;
    }
    else
    {
        baropen = tick.lastprice;
        vwap = twap = tick.lastprice ;
        volumn = tick.volumn;
        tickcnt = 1;
    }
}

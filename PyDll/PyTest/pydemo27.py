# -*- coding: utf-8 -*-
import thosttraderapi as api
#credit https://blog.csdn.net/pjjing/article/details/77338423
#borrow from CSDN guy, thank you man!
#Addr
FrontAddr="tcp://180.168.146.187:10100"
#FrontAddr="tcp://180.168.146.187:10130"
#LoginInfo
BROKERID="9999"
USERID="00001"
PASSWORD="00001"
#OrderInfo
INSTRUMENTID="rb2005"
PRICE=3200
VOLUME=1
DIRECTION=api.THOST_FTDC_D_Sell
#DIRECTION=api.THOST_FTDC_D_Buy
#open
OFFSET="0"
#close
#OFFSET="1"

def ReqorderfieldInsert(tradeapi):
    print "ReqOrderInsert Start"
    orderfield=api.CThostFtdcInputOrderField()
    orderfield.BrokerID="8000"
    orderfield.InstrumentID="rb2005"
    orderfield.UserID="000005"
    orderfield.InvestorID="000005"
    orderfield.Direction=api.THOST_FTDC_D_Sell
    orderfield.LimitPrice=52050
    orderfield.VolumeTotalOriginal=1
    orderfield.OrderPriceType=api.THOST_FTDC_OPT_LimitPrice
    orderfield.ContingentCondition = api.THOST_FTDC_CC_Immediately
    orderfield.TimeCondition = api.THOST_FTDC_TC_GFD
    orderfield.VolumeCondition = api.THOST_FTDC_VC_AV
    orderfield.CombHedgeFlag="1"
    orderfield.CombOffsetFlag="0"
    orderfield.GTDDate=""
    orderfield.orderfieldRef="1"
    orderfield.MinVolume = 0
    orderfield.ForceCloseReason = api.THOST_FTDC_FCC_NotForceClose
    orderfield.IsAutoSuspend = 0
    tradeapi.ReqOrderInsert(orderfield,0)
    print "ReqOrderInsert End"


class CTradeSpi(api.CThostFtdcTraderSpi):
    tapi=''
    def __init__(self,tapi):
        api.CThostFtdcTraderSpi.__init__(self)
        self.tapi=tapi
    def OnRspUserLogin(self, *args):
        print "OnRspUserLogin"
        rsploginfield=args[0]
        rspinfofield=args[1]
        print "SessionID=",rsploginfield.SessionID
        print "ErrorID=",rspinfofield.ErrorID
        print "ErrorMsg=",rspinfofield.ErrorMsg
        ReqorderfieldInsert(self.tapi)      

    def OnRtnOrder(self, *args):
        print "OnRtnOrder"
        rtnfield=args[0]
        print "OrderStatus=",rtnfield.OrderStatus
        print "StatusMsg=",rtnfield.StatusMsg
        print "LimitPrice=",rtnfield.LimitPrice

    def OnRspOrderInsert(self, *args):
        print "OnRspOrderInsert"
        rspinfofield=args[1]
        print "ErrorID=",rspinfofield.ErrorID
        print "ErrorMsg=",rspinfofield.ErrorMsg

def main():
    tradeapi=api.CThostFtdcTraderApi_CreateFtdcTraderApi()
    tradespi=CTradeSpi(tradeapi)
    loginfield = api.CThostFtdcReqUserLoginField()
    loginfield.BrokerID="8000"
    loginfield.UserID="000005"
    loginfield.Password="123456"
    loginfield.UserProductInfo="python dll"
    tradeapi.RegisterFront("tcp://172.19.125.39:39233")
    tradeapi.RegisterSpi(tradespi)
    tradeapi.SubscribePrivateTopic(api.THOST_TERT_RESUME)
    tradeapi.SubscribePublicTopic(api.THOST_TERT_RESUME)
    tradeapi.Init()
    time.sleep(2)
    tradeapi.ReqUserLogin(loginfield,0)
    tradeapi.Join()

if __name__ == '__main__':
    main()

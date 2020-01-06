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
	print ("ReqOrderInsert Start")
	orderfield=api.CThostFtdcInputOrderField()
	orderfield.BrokerID=BROKERID
	orderfield.InstrumentID=INSTRUMENTID
	orderfield.UserID=USERID
	orderfield.InvestorID=USERID
	orderfield.Direction=DIRECTION
	orderfield.LimitPrice=PRICE
	orderfield.VolumeTotalOriginal=VOLUME
	orderfield.OrderPriceType=api.THOST_FTDC_OPT_LimitPrice
	orderfield.ContingentCondition = api.THOST_FTDC_CC_Immediately
	orderfield.TimeCondition = api.THOST_FTDC_TC_GFD
	orderfield.VolumeCondition = api.THOST_FTDC_VC_AV
	orderfield.CombHedgeFlag="1"
	orderfield.CombOffsetFlag=OFFSET
	orderfield.GTDDate=""
	orderfield.OrderRef="1"
	orderfield.MinVolume = 0
	orderfield.ForceCloseReason = api.THOST_FTDC_FCC_NotForceClose
	orderfield.IsAutoSuspend = 0
	tradeapi.ReqOrderInsert(orderfield,0)
	print ("ReqOrderInsert End")
	

class CTradeSpi(api.CThostFtdcTraderSpi):
	tapi=''
	def __init__(self,tapi):
		api.CThostFtdcTraderSpi.__init__(self)
		self.tapi=tapi
		
	def OnFrontConnected(self):
		#print "OnFrontConnected"
		loginfield = api.CThostFtdcReqUserLoginField()
		loginfield.BrokerID=BROKERID
		loginfield.UserID=USERID
		loginfield.Password=PASSWORD
		loginfield.UserProductInfo="python dll"
		self.tapi.ReqUserLogin(loginfield,0)
		print "send login ok"
		
	def OnRspUserLogin(self, pRspUserLogin, pRspInfo, nRequestID, bIsLast) :
		print "OnRspUserLogin"
		print "TradingDay=",pRspUserLogin.TradingDay
		print "SessionID=",pRspUserLogin.SessionID
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg

		qryinfofield = api.CThostFtdcQrySettlementInfoField()
		qryinfofield.BrokerID=BROKERID
		qryinfofield.InvestorID=USERID
		qryinfofield.TradingDay=pRspUserLogin.TradingDay
		self.tapi.ReqQrySettlementInfo(qryinfofield,0)
		print "send ReqQrySettlementInfo ok"
		

	def OnRspQrySettlementInfo(self, pSettlementInfo, pRspInfo, nRequestID, bIsLast) :
		print ("OnRspQrySettlementInfo")
		if  pSettlementInfo is not None :
			print "content:",pSettlementInfo.Content
		else :
			print "content null"
		if bIsLast :
			pSettlementInfoConfirm=api.CThostFtdcSettlementInfoConfirmField()
			pSettlementInfoConfirm.BrokerID=BROKERID
			pSettlementInfoConfirm.InvestorID=USERID
			self.tapi.ReqSettlementInfoConfirm(pSettlementInfoConfirm,0)
			print "send ReqSettlementInfoConfirm ok"
		
	def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast) :
		print "OnRspSettlementInfoConfirm"
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg
		ReqorderfieldInsert(self.tapi)
		print "send ReqorderfieldInsert ok"


	def OnRtnOrder(self, pOrder) :
		print "OnRtnOrder"
		print "OrderStatus=",pOrder.OrderStatus
		print "StatusMsg=",pOrder.StatusMsg
		print "LimitPrice=",pOrder.LimitPrice
		
	def OnRspOrderInsert(self, pInputOrder, pRspInfo, nRequestID, bIsLast) :
		print "OnRspOrderInsert"
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg
		
def main():
	tradeapi=api.CThostFtdcTraderApi_CreateFtdcTraderApi()
	tradespi=CTradeSpi(tradeapi)
	tradeapi.RegisterSpi(tradespi)
	tradeapi.SubscribePrivateTopic(api.THOST_TERT_QUICK)
	tradeapi.SubscribePublicTopic(api.THOST_TERT_QUICK)
	tradeapi.RegisterFront(FrontAddr)	
	tradeapi.Init()
	tradeapi.Join()
	
if __name__ == '__main__':
	main()

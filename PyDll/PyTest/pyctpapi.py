# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf8')
import thosttraderapi as api
import io
import time
import json
import unicodedata
#credit https://blog.csdn.net/pjjing/article/details/77338423
#borrow from CSDN guy, thank you man!
#OrderInfo

#DIRECTION=api.THOST_FTDC_D_Sell
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
	
def save_file(filename, contents):
    with io.open(filename, "w", encoding='utf-8') as f:
        f.write(u'{}\n'.format(contents))
class CTradeSpi(api.CThostFtdcTraderSpi):
	tapi=''
	daysettle = []
	allsettle = []
	reqid = 0
	theqrydate = ""
	FrontAddr=""#cfg["tdAddress"]
	#FrontAddr="tcp://180.168.146.187:10130"
	#LoginInfo
	BROKERID=""#cfg["brokerID"]
	USERID=""#cfg["userID"]
	PASSWORD=""#cfg["password"]
	APPID=""#cfg["appID"]
	AUTHCODE=""#cfg["authCode"]
	def __init__(self,tapi):
		api.CThostFtdcTraderSpi.__init__(self)
		self.tapi=tapi
		self.daysettle = []
		self.allsettle = []
		self.reqid = 0
		self.theqrydate = ""
		dataContent = ""
		with open('./j123.json', 'r') as f:
			dataContent = f.read()
			#print(dataContent)
		cfg = json.loads(dataContent) 
		#print cfg["brokerID"]
		self.FrontAddr=cfg["tdAddress"].encode('ascii', 'ignore')
		self.BROKERID=cfg["brokerID"].encode('ascii', 'ignore')
		print self.BROKERID
		self.USERID=cfg["userID"].encode('ascii', 'ignore')
		self.PASSWORD=cfg["password"].encode('ascii', 'ignore')
		self.APPID=cfg["appID"].encode('ascii', 'ignore')
		self.AUTHCODE=cfg["authCode"].encode('ascii', 'ignore')
		
	
	def OnFrontConnected(self):
		print "OnFrontConnected"
		#print self.BROKERID
		#print "after"
		authfield = api.CThostFtdcReqAuthenticateField()
		print "aaaaa"
		#loginfield = api.CThostFtdcReqUserLoginField()
		authfield.BrokerID=self.BROKERID
		print "ddd"
		authfield.UserID=self.USERID
		print "ddd"
		#authfield.Password=PASSWORD
		authfield.UserProductInfo="python dll"
		authfield.AuthCode = self.AUTHCODE
		authfield.AppID = self.APPID
		print "ddd"
		self.reqid += 1
		
		print self.BROKERID,self.USERID,self.AUTHCODE,self.APPID
		self.tapi.ReqAuthenticate(authfield,self.reqid)
		#self.tapi.ReqUserLogin(loginfield,0)
		print "send auth request ok"
	def OnRspAuthenticate(self, pRspAuthenticateField, pRspInfo, nRequestID, bIsLast):	
		print ("BrokerID=",pRspAuthenticateField.BrokerID)
		print ("UserID=",pRspAuthenticateField.UserID)
		print ("AppID=",pRspAuthenticateField.AppID)
		print ("AppType=",pRspAuthenticateField.AppType)		
		print ("ErrorID=",pRspInfo.ErrorID)
		print ("ErrorMsg=",pRspInfo.ErrorMsg)
		if not pRspInfo.ErrorID :
			loginfield = api.CThostFtdcReqUserLoginField()
			loginfield.BrokerID=self.BROKERID
			loginfield.UserID=self.USERID
			loginfield.Password=self.PASSWORD
			loginfield.UserProductInfo="python dll"
			self.tapi.ReqUserLogin(loginfield,0)
			print ("send login ok")
		
	def OnRspUserLogin(self, pRspUserLogin, pRspInfo, nRequestID, bIsLast) :
		print "OnRspUserLogin"
		print "TradingDay=",pRspUserLogin.TradingDay
		print "SessionID=",pRspUserLogin.SessionID
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg		
	
	def ReqQryHist(self,dt,reqid):
		qryinfofield = api.CThostFtdcQrySettlementInfoField()
		qryinfofield.BrokerID=self.BROKERID#"118907"
		qryinfofield.InvestorID=self.BROKERID
		qryinfofield.TradingDay=dt.encode('ascii', 'ignore')
		ret = self.tapi.ReqQrySettlementInfo(qryinfofield,reqid)
		print("query settle",ret)
		
	def OnRspQrySettlementInfo(self, pSettlementInfo, pRspInfo, nRequestID, bIsLast) :
		print ("OnRspQrySettlementInfo")
		#print (pSettlementInfo.Content)
		if  pSettlementInfo is not None :
			print ("content:",pSettlementInfo.Content)
			self.daysettle.append(pSettlementInfo.Content)
			#print(pSettlementInfo.Content)
		else :
		    print "content null"
		if bIsLast :
			if len(self.daysettle) > 0:
				self.allsettle.append(self.daysettle)
				self.daysettle.clear()
			print "confirmed date"
		print self.daysettle
		
	def OnRspSettlementInfoConfirm(self, pSettlementInfoConfirm, pRspInfo, nRequestID, bIsLast) :
		print "OnRspSettlementInfoConfirm"
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg
		#ReqorderfieldInsert(self.tapi)
		#print "send ReqorderfieldInsert ok"


	def OnRtnOrder(self, pOrder) :
		print "OnRtnOrder"
		print "OrderStatus=",pOrder.OrderStatus
		print "StatusMsg=",pOrder.StatusMsg
		print "LimitPrice=",pOrder.LimitPrice
		
	def OnRspOrderInsert(self, pInputOrder, pRspInfo, nRequestID, bIsLast) :
		print "OnRspOrderInsert"
		print "ErrorID=",pRspInfo.ErrorID
		print "ErrorMsg=",pRspInfo.ErrorMsg
		



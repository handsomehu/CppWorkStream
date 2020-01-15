# -*- coding: utf-8 -*-
import sys
reload(sys)
sys.setdefaultencoding('utf8')
import thosttraderapi as api
import io
import time
from pyctpapi import CTradeSpi
import pickle 

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

		
def main():
	txdates = ["20200113","20200114","20200115",]
	tradeapi=api.CThostFtdcTraderApi_CreateFtdcTraderApi()
	tradespi=CTradeSpi(tradeapi)
	tradeapi.RegisterSpi(tradespi)
	tradeapi.SubscribePrivateTopic(api.THOST_TERT_QUICK)
	tradeapi.SubscribePublicTopic(api.THOST_TERT_QUICK)
	FrontAddr1="tcp://180.168.146.187:10130"
	tradeapi.RegisterFront(FrontAddr1)	
	tradeapi.Init()
	qryinfofield = api.CThostFtdcQrySettlementInfoField()
	qryinfofield.BrokerID="118907"
	qryinfofield.InvestorID="118907"
	#qryinfofield.TradingDay="20200113"
	lv_reqid = 10000		
	for dt in txdates:
		lv_reqid += 1
		qryinfofield.TradingDay=dt
		tradeapi.ReqQrySettlementInfo(qryinfofield,lv_reqid)
		time.sleep(5)
	
	rst = tradespi.allsettle
	filehandler = open("./tx.pkl", 'w') 
	pickle.dump(rst, filehandler)
	#tradeapi.Join()
	
if __name__ == '__main__':
	main()


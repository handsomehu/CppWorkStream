CTP自动交易,日内系统
什么条件开平仓:
	如果当前价格大于开盘价,开多;
	如果当前价格小雨开盘价,开空;

	如果持多仓并且小于开盘价,那么平多反空;
	如果持空仓并且价格大于开盘价,那么平空反多;

	如果持仓当天次数大于5次,不再开仓
	如果一直持仓到收盘,比如15:19平仓;

风控:
	满足条件,用可用资金的N%来开仓;
	当天亏损超过N%停止开仓;


多线程





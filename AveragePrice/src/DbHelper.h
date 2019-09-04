/*
 * DbHelper.h
 *
 *  Created on: Sep 4, 2019
 *      Author: leon
 */

#ifndef SRC_DBHELPER_H_
#define SRC_DBHELPER_H_
#include <sstream>
#include <iomanip>
#include "sqlite3.h"
#include <chrono>
#include <string>
#include <cstring>
#include "./libhead/ThostFtdcMdApi.h"

class DbHelper {
public:
	sqlite3* db = nullptr;
	DbHelper();
	virtual ~DbHelper();
	int PersistVwap(TThostFtdcDateType tradeday,TThostFtdcInstrumentIDType InID, double price,int vol);
	int RunInsertParamSQL(sqlite3 *db, TThostFtdcDateType tradeday,TThostFtdcInstrumentIDType InID, double price,int vol);
};

#endif /* SRC_DBHELPER_H_ */

/*
 * DbHelper.cpp
 *
 *  Created on: Sep 4, 2019
 *      Author: leon
 */

#include "DbHelper.h"

DbHelper::DbHelper() {
	// TODO Auto-generated constructor stub
	  if (sqlite3_open("/home/leon/sqllitedb/leontest.db", &db) == SQLITE_OK) {
	    //std::cout << "DB Opened.\n" << std::endl;
		  int i = 0;
	  }

}

DbHelper::~DbHelper() {
	// TODO Auto-generated destructor stub
	if (db)
		sqlite3_close(db);
}
int DbHelper::PersistVwap(TThostFtdcDateType tradeday,TThostFtdcInstrumentIDType InID, double price,int vol)
{
	static int rt = RunInsertParamSQL(db,tradeday,InID, price,vol);
	return rt;
}
int DbHelper::RunInsertParamSQL(sqlite3 *db, TThostFtdcDateType tradeday,TThostFtdcInstrumentIDType InID, double price,int vol)
{
	  if (!db)
	    return 1;

	  char *zErrMsg = 0;
	  sqlite3_stmt *stmt;
	  const char *pzTest;
	  char *szSQL;

	  // Insert data item into myTable
	  szSQL = "insert into vwaps (tradeday,symbol, price,vol,updatetime) values (?,?,?,?,?)";

	  int rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);

	  if( rc == SQLITE_OK ) {
	    // bind the value
		auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		//转为字符串
		std::stringstream ss;
		ss << std::put_time(std::localtime(&t), "%F %T");
		std::string str = ss.str();
		const char* cstr = str.c_str();
		sqlite3_bind_text(stmt, 1, tradeday, strlen(tradeday),0);
	    sqlite3_bind_text(stmt, 2, InID, strlen(InID), 0);
	    sqlite3_bind_double(stmt, 3, price);
	    sqlite3_bind_int(stmt, 4, vol);
		sqlite3_bind_text(stmt, 5, cstr, strlen(cstr),0);
	    // commit
	    sqlite3_step(stmt);
	    sqlite3_finalize(stmt);
	  }
	    return 0;
}


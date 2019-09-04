/*
 *  Created on: Sep 3, 2019
 *      Author: leon
 */
#include <vector>
#include <string>
#include <cstring>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "sqlite3.h"
#include <chrono>
//using namespace std;

sqlite3* db;

using Record = std::vector<std::string>;
using Records = std::vector<Record>;

int select_callback(void *p_data, int num_fields, char **p_fields, char **p_col_names)
{
  Records* records = static_cast<Records*>(p_data);
  try {
    records->emplace_back(p_fields, p_fields + num_fields);
  }
  catch (...) {
    // abort select on failure, don't let exception propogate thru sqlite3 call-stack
    return 1;
  }
  return 0;
}

Records select_stmt(const char* stmt)
{
  Records records;
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, select_callback, &records, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
  else {
    std::cerr << records.size() << " records returned.\n";
  }

  return records;
}
int insert_stmt(const char* stmt)
{
	  int recordcnt = 0;
	  char *errmsg;
	  int ret = sqlite3_exec(db, stmt, NULL, NULL, &errmsg);
	  if (ret != SQLITE_OK) {
	    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
	  }
	  else {
	    std::cerr << ret << " records returned.\n";
	  }

	  return ret;
}
void RunInsertParamSQL(sqlite3 *db, char *prd, double prc, int qty)
{
  if (!db)
    return;

  char *zErrMsg = 0;
  sqlite3_stmt *stmt;
  const char *pzTest;
  char *szSQL;

  // Insert data item into myTable
  szSQL = "insert into tborders (orderdate,product, price,qty) values (?,?,?,?)";

  int rc = sqlite3_prepare(db, szSQL, strlen(szSQL), &stmt, &pzTest);

  if( rc == SQLITE_OK ) {
    // bind the value
	auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	//转为字符串
	std::stringstream ss;
	ss << std::put_time(std::localtime(&t), "%F %T");
	std::string str = ss.str();
	const char* cstr = str.c_str();
	sqlite3_bind_text(stmt, 1, cstr, strlen(cstr),0);
    sqlite3_bind_text(stmt, 2, prd, strlen(prd), 0);
    sqlite3_bind_double(stmt, 3, prc);
    sqlite3_bind_int(stmt, 4, qty);

    // commit
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    std::cout << "insert finish!" << std::endl;
  }
}
void sql_stmt(const char* stmt)
{
  char *errmsg;
  int ret = sqlite3_exec(db, stmt, 0, 0, &errmsg);
  if (ret != SQLITE_OK) {
    std::cerr << "Error in select statement " << stmt << "[" << errmsg << "]\n";
  }
}

int main()
{
  if (sqlite3_open("/home/leon/sqllitedb/leontest.db", &db) != SQLITE_OK) {
    std::cerr << "Could not open database.\n";
    return 1;
  }

  Records records = select_stmt("SELECT product,price FROM tborders");


  for (auto& record : records) {
    // do something with your records
	  std::cout << record[0] << "\t" << record[1] << std::endl;
  }

  //int rt = insert_stmt("insert into tborders (orderdate,product,price,qty) values (?,'PC',5666,1)");
  //if (rt == SQLITE_OK)
	//  std::cout << "insert OK" << std::endl;
  RunInsertParamSQL(db,"TV",2000,1);
  sqlite3_close(db);
  return 0;
}

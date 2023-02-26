#pragma once
#include "DBINFO.h"
#include <mysql/mysql.h>
#include <iostream>
#include <string>

class DBconnect
{
public:
	DBconnect();
	~DBconnect();
	
	MYSQL* getConnectDB();
	void RealConnectDB(DBINFO info);
	void Query(std::string qry);
	void ShowSelectQuery();
	MYSQL_RES* getResult();
	MYSQL_ROW getRow();
	int getField();
	
	void Destroy();
	
private:
	int field;
	MYSQL_RES* res;
	MYSQL_ROW row;
	MYSQL* con;	
};

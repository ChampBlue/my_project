#include "DBconnect.h"
#include <string>

DBconnect::DBconnect() :
	field(0)
{
	con = mysql_init(NULL);
	if(con == NULL)
	{
		std::cout << "mysql_init() failed" << std::endl;
	} 
}

DBconnect::~DBconnect()
{
	if(con != NULL)
	{
		mysql_close(con);
	}
	if (res != NULL)
	{
		mysql_free_result(res);
	}
}

MYSQL* DBconnect::getConnectDB()
{
	return con;
}

void DBconnect::RealConnectDB(DBINFO info)
{
	if(mysql_real_connect( con, info.ip, info.user, info.pwd, 			info.db_name, info.port, NULL, 0) == NULL) {
	std::cout << mysql_error(con);
	mysql_close(con);
	exit(1);
	}
}

void DBconnect::Query(std::string qry)
{
	std::string query = qry.substr(0, 6);
	
	if(mysql_query(con, qry.c_str()))
	{
		std::cout << mysql_error(con) << std::endl;
		mysql_close(con);
	}
	res = mysql_store_result(con);
	
	if(query == "select" || query == "SELECT") {
		ShowSelectQuery();
	}
}

void DBconnect::ShowSelectQuery()
{
	MYSQL_ROW _row;
	while((_row = getRow()) != NULL) {
		for(int i = 0; i < getField(); i++) {
			std::cout << (_row[i] ? _row[i] : NULL) << "\t";
		}
		std::cout << std::endl;
	}
}

MYSQL_RES* DBconnect::getResult()
{
	return res;
}

MYSQL_ROW DBconnect::getRow()
{
	row = mysql_fetch_row(res);
	return row;
}

int DBconnect::getField()
{
	field = mysql_num_fields(res);
	return field;
}

void DBconnect::Destroy()
{
    if (con != NULL)
    {
        mysql_close(con);
    }
    if (res != NULL)
    {
        mysql_free_result(res);
    }
}


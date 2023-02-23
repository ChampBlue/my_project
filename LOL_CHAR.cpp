#include <iostream>
#include <mysql/mysql.h>

void finish_with_error(MYSQL* con)
{
    fprintf(stderr, "%s\n", mysql_error(con));
    mysql_close(con);
    exit(1);
}

int main()
{
    MYSQL *con = mysql_init(NULL);

    if(con == NULL){
        fprintf(stderr, "%s\n", mysql_error(con));
        exit(1);
    }

    if (mysql_real_connect(con, "localhost", "root", "iot123", NULL, 3306, NULL, 0) == NULL){
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}

	if (mysql_query(con, "CREATE DATABASE LOL_CHAR"))	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		exit(1);
	}

    if (mysql_query(con, "USE LOL_CHAR"))
    {
        finish_with_error(con);
    }

    if (mysql_query(con, "CREATE TABLE AD(Name TEXT, Role TEXT, Grade CHAR, Rp INT)")) {
        finish_with_error(con);
    }

    if (mysql_query(con, "CREATE TABLE AP(Name TEXT, Role TEXT, Grade CHAR, Rp INT)")) {
        finish_with_error(con);
    }

    if(mysql_query(con, "INSERT INTO AP VALUES('말파이트', '탱커', 'A', 1350)")){
        finish_with_error(con);
    }
    if(mysql_query(con, "INSERT INTO AP VALUES('오른', '탱커', 'A', 6300)")){
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('제라스', '원딜', 'B', 3150)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('다이애나', '근딜', 'C', 3150)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('르블랑', '원딜', 'S', 1350)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('에코', '근딜', 'A', 4800)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('말자하', '원딜', 'D', 3150)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('라이즈', '원딜', 'D', 450)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('람머스', '탱커', 'C', 1350)")) {
        finish_with_error(con);
    }
    if(mysql_query (con, "INSERT INTO AP VALUES('모데카이저', '탱커', 'B', 1350)")) {
        finish_with_error(con);
    }

    mysql_close(con);

    return 0;
}

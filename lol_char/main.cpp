#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main()
{
	int menu = 0;
	
	mysql_query(con, "CREATE DATABASE LOL_CHAR");
	
	mysql_query(con, "USE LOL_CHAR");
	
	mysql_query(con, "CREATE TABLE char_list(Name INT, Role TEXT, Grade CHAR, Rp INT)");
	
	while(1) {
		
		cout<<"====================" << endl;
		cout << "		 메뉴		" << endl;
		cout << "1. 캐릭터 조회"  <<endl;
		cout << "2. 캐릭터 추가" <<endl;
		cout << "3. 캐릭터 수정" <<endl;
		cout << "4. 캐릭터 삭제" <<endl;
		cout << "5. 종료" <<endl;
		cout << "==================" <<endl;
		cout << endl;
		cout << "원하는 메뉴를 선택하시오 : ";
		cin >> menu;
		cout << endl;
		
		switch (menu) {
			case 1:
			{
				cout << "캐릭터 이름\t 역할군\t OP등급\t rp" << endl;
				db.Query("SELECT * FROM char_list");
				cout << endl << endl;
				
				break;
			}
			case 2:
			{
				string name, string role, char grade, int rp;
				cout << "캐릭터 이름을 입력하시오 : ";
				cin >> name;
				cout << "역할군을 입력하시오 : ";
				cin >> role;
				cout << "OP등급을 입력하시오 : ";
				cin >> grade;
				cout << "rp를 입력하시오 : ";
				cin >> rp;
				
				db.Query("INSERT INTO char_list(Name, Role, Grade, Rp) 					VALUES('"+ name +"', '"+ role +"', '"+ grade +"', '"+ rp 					+"')");
				break;
			}
			case 3:
			{
				string name_, string role_, char grade_, int rp_;
				cout << "이름을 입력하시오 : ";
				cin >> name_;
				cout << "역할군을 입력하시오 : ";
				cin >> role_;
				cout << "OP등급을 입력하시오 : ";
				cin >> grade_;
				cout << "rp를 입력하시오 : ";
				cin >> rp_;
				db.Query("UPDATE char_list SET Name_ = '" + name_ +"', role_ = '"role_'", grade_ = '"grade_"', rp_ = '"+rp_"' WHERE Name = "+ name_ +"'); 
				break;
			}
			case 4:
			{
				string name;
				cout << "삭제할 캐릭터의 이름을 입력하시오 : ";
				cin >> name;
				db.Query("DELETE FROM char_list WHERE Name = " + name + "");
				break;
			}
			case 5:
	
		
				break;
			
			default:
				break;
		}
	}

	return 0;
}

#include "raise_class.hpp"
#include "raise_func.hpp"

int main()
{
    short choice = 0;
    short menu = 0;
    string _name = "";
    
    cout << "당신의 이름은? : ";
    cin >> _name;
    cout << endl;

    User user(_name);

    cout << "당신의 동물 이름은? : ";
    cin >> _name;
    cout << endl;

    Pig pig(_name);

    while(true){
        cout << endl << "========메뉴========" << endl;
        cout << "1. 유저 메뉴" <<endl;
        cout << "2. 동물 메뉴" << endl; 
        cout << "3. 턴 종료" << endl;
        cout << "4. 게임 종료" <<endl << endl;

        switch(menu){
            case 1:
                cout << "유저 메뉴를 선택하시오 : ";
                cin >> choice;
                cout << endl;

                for(;;) {
                    cout << endl << "========메뉴========" << endl;
                    cout << "1. 유저 상태창" << endl;
                    cout << "2. 물 사기" << endl;
                    cout << "3. 먹이 사기" << endl;
                    cout << "4. 도박" << endl;
                    cout << "5. 동물 판매"<< endl;
                    cout << "6. 나가기" << endl;

                    switch(choice) {
                        case 1:
                            user.user_status();
                            break;

                        case 2:
                            user.buy_water();
                            break;
                        
                        case 3:
                            user.buy_food();
                            break;

                        case 4:
                            int bet_money = 0;
                            cout << "얼마나 배팅 하실껀가요?  ";
                            cin >> bet_money;
                            cout << endl;
                            user.gamble(bet_money);
                            break;

                        case 5:

                            break;

                        case 6:

                            break;
                    }
                }
                
                break;
        
            case 2:
                cout << "동물 메뉴를 선택하시오 : ";
                cin >> choice;
                cout << endl;
                for(;;) {
                    cout << endl << "========메뉴========" << endl;
                    cout << "1. 동물 상태창" << endl;
                    cout << "2. 물 사기" << endl;
                    cout << "3. 먹이 사기" << endl;
                    cout << "4. 도박" << endl;
                    cout << "5. 동물 판매"<< endl;
                    cout << "6. 나가기" << endl;

                    switch(choice) {
                        case 1:
                            pig.show_status();
                            break;
                    }

                }


                break;
        
            case 3:

                break;

            case 4:

                return 0;
        }
    }

    return 0;
}
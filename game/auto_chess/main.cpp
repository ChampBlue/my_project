#include "class.hpp"
#include "func.hpp"

int main()
{
    Map map1;
    Map map2;
    short menu = 0;
    bool end_turn = false;
    string p1 = "";
    cout << "플레이어 1의 이름 : ";
    cin >> p1;
    string p2 = "";
    cout << "플레이어 2의 이름 : ";
    cin >> p2;
    
    Player player1(p1, map1);
    Player player2(p2, map2);
    Player* current_player = &player1;
    Player* next_player = &player2;
    
    while(true) {
        cout << current_player->get_name() <<"의 차례 입니다." << endl; 
        
        cout << "이번 턴 선택할 수 있는 유닛" << endl;
        std::array<short, 3> rand_units = random_unit();
        cout << "종족 값" << endl;
        cout << "1. 인간" << ", " << "2. 그린스킨" << ", " << "3. 뱀파이어" << ", "<< "4. 카오스" << ", " << "5. 하이엘프" << ", " <<"6. 비스트맨" << ", " << "7. 다크엘프" << endl; 
        cout << "1. :  " << rand_units[0] <<"번" << " " << "2. :  " << rand_units[1] << "번"<<" " << "3. :  " << rand_units[2] <<"번"<< endl;
        
        for(;;) {
            short choice = 0;
            cout<< "3가지 옵션 중 하나를 고르시오"<<endl;
            cin >> choice;
            cout<< "선택 : " << choice << endl << endl;
        
            switch(choice) {
                case 1:
                    if (rand_units[0] == 1) {
                        vector<Human> human;
                        current_player->show_map_player();
                        cout <<"배치 할 위치를 선택 하시오" << endl;
                        short x, y;
                        cout << endl << "x 좌표 : ";
                        cin >> x;
                        cout << endl << "y 좌표 : ";
                        cin >> y;
                        cout << endl;
                        if(x < 0 || x >= )

                    }

                    break;
                
                case 2:

                    break;

                case 3:

                    break;
            }
        }

        cout << "원하시는 메뉴를 선택하시오" << endl;
        cout << "====== 메뉴 ======" << endl;
        cout << "1. 상태창 " << endl;
        cout << "2. 도박" << endl;
        cout << "3. 조합" << endl;
        cout << "4. 강화도박" << endl;
        cout << "5. 턴 종료" << endl;
        cout << "6. 게임 종료" << endl;

        cin >> menu;
        cout << "선택한 메뉴 : " << menu << endl;
        cout<<endl;

        if(menu != 1 && menu != 2 && menu != 3 && menu != 4 && menu != 5 && menu != 6) {
            cout << "선택할 메뉴를 다시 적으시오!!!" << endl;
            continue;
        }

        short _coin = 0;

        switch(menu) {
            case 1:
                current_player->player_status();
                break;

            case 2:
                while(true) {
                    cout << "도박 할 코인 수 : " << endl;
                    cin >> _coin;
                    if(_coin > current_player->get_coin()) {
                        cout << "사기치지 마라!" << endl;
                        continue;
                    }
                    else    {
                        current_player->gamble_coin(_coin);
                    }
                    break;
                }
                
                break;
            
            case 3:
            //조합


                break;
            
            case 4:
            //강화도박


                break;
            
            case 5:
            //전투는 여기에 구현

                end_turn = true;

                break;

            case 6:
                cout << "게임 종료" <<endl;
                return 0;
            
            default:

                break;
        }

        if (end_turn) {
            end_turn = false;
            Player* temp = current_player;
            current_player = next_player;
            next_player = temp;
        }
    }

    return 0;
}
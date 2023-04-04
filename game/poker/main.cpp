#include "poker_class.hpp"
#include "include.hpp"

int main()
{
    char choice_bet = 0;
    bool end_turn = false;
    short turn_cnt = 0;
    short menu = 0;
    string p_name ="";
    long p_bet_money = 0;
    long whole_bet_money = 0;

    cout << "플레이어 1의 이름 : ";
    cin >> p_name;
    Player p1(p_name);
    cout << endl << "플레이어 2의 이름 :";
    cin >> p_name;
    Player p2(p_name);
    cout << endl;
    Player* current_player = &p1;
    Player* next_player = &p2;

    vector<Card> card;
    for(short i = 2; i < 11; i++){
        Card space_i("space", i);
        card.push_back(space_i);
    }
    for(short i = 2; i < 11; i++){
        Card heart_i("heart", i);
        card.push_back(heart_i);
    }
    for(short i = 2; i < 11; i++){
        Card diamond_i("diamond", i);
        card.push_back(diamond_i);
    }
    for(short i = 2; i < 11; i++){
        Card club_i("club", i);
        card.push_back(club_i);
    }
    for(char c ='A'; c < 'Z'; c++) {
        if(c == 'A' || c == 'J' || c =='K' || c == 'Q'){
            Card space_c("space" , c);
            card.push_back(space_c);
        }
    }
    for(char c ='A'; c < 'Z'; c++) {
        if(c == 'A' || c == 'J' || c =='K' || c == 'Q'){
            Card heart_c("heart" , c);
            card.push_back(heart_c);
        }
    }
    for(char c ='A'; c < 'Z'; c++) {
        if(c == 'A' || c == 'J' || c =='K' || c == 'Q'){
            Card diamond_c("diamond" , c);
            card.push_back(diamond_c);
        }
    }
    for(char c ='A'; c < 'Z'; c++) {
        if(c == 'A' || c == 'J' || c =='K' || c == 'Q'){
            Card club_c("club" , c);
            card.push_back(club_c);
        }
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(card.begin(), card.end(), gen);

    for(int i = 0; i < 2; i++) {
        p1.add_card(card.back());
        card.pop_back();
        p2.add_card(card.back());
        card.pop_back();
    }

    cout << "초기 배팅" << endl;
    cout << p1.get_name() << "님의 배팅 값 : ";
    cin >> p_bet_money;
    cout << endl;
    p1.set_coin(p_bet_money);
    p2.set_coin(p_bet_money);
    cout << "추가 배팅을 하시겠습니까? y or n : ";
    cin >> choice_bet;
    if(choice_bet == 'y' || 'Y') {
        cout << p2.get_name() << "님의 추가 배팅 값 : ";
        cin >> p_bet_money;
        cout << endl;
        p2.set_coin(p_bet_money);
        p1.set_coin(p_bet_money);
    }
    else if(choice_bet == 'n' || 'N')
        cout << "그대로 간다" << endl;
    
    while(true){
        cout << endl << "========메뉴========" << endl;
        cout << "1. 턴 시작" <<endl;
        cout << "2. 패 확인" <<endl;
        cout << "3. 배팅" <<endl;
        cout << "4. 턴 종료" << endl;
        cout << "5. 게임 종료" <<endl << endl;
    
        cout << "메뉴 선택 : ";
        cin >> menu;
        cout << endl;
        cout << "선택한 메뉴 : " << menu << endl <<endl;

        switch (menu) {
            case 1:
                turn_cnt ++;
                if(turn_cnt == 5) {
                    cout << current_player->get_name() <<"님의 마지막 턴"<< endl;
                }else if(turn_cnt == 6) {
                    cout << current_player->get_name() <<"님의 마지막 턴"<< endl;
                }
                cout << current_player->get_name() <<"님의 턴" << endl;
                current_player->add_card(card.back());
                card.pop_back();
                break;

            case 2:
                current_player->show_status();
                break;

            case 3:
                
                cout << "배팅 할 금액 : ";
                cin >> p_bet_money;
                current_player->set_coin(p_bet_money);
                whole_bet_money += p_bet_money;
                cout << endl;

                break;

            case 4:
                short winner;
                end_turn = true;

                if (turn_cnt == 6) {
                    cout << "게임 끝" << endl;
                    p1.show_card();
                    p2.show_card();
                    cout << "winner : " << endl;
                    cin >> winner;

                    if(winner == 1) {
                        p1.winner_coin(whole_bet_money);
                    }
                    else if(winner == 2){
                        p2.winner_coin(whole_bet_money);
                    }

                }

                break;            

            case 5:
                cout << "게임 종료" << endl;
                return 0;
        }
        if (end_turn) {
            end_turn = false;
            Player* temp = current_player;
            current_player = next_player;
            next_player = temp;
        }

    }
}

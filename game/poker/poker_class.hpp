#include "include.hpp"

class Player
{
    long coin;
    string name;
    vector<Card> hand;

    public:
        Player(string _name):coin(100000000000){
            name = _name;
        }
        void show_status();
        void add_card(Card new_card);
        void set_coin(long bet_money);
        void winner_coin(long bet_money);
        void show_card();
        string get_name();
};
void Player::show_status(){
    cout << name << endl;
    cout << "현재 잔액 : " << coin <<endl << endl;
    cout << "현재 패 : ";
    for (auto& card : hand) {
        card.card_info();
    } 
}
void Player::add_card(Card new_card){
    hand.push_back(new_card);
}
void Player::set_coin(long bet_money){
    coin -= bet_money;
}
void Player::winner_coin(long bet_money) {
    coin += bet_money;
}
void Player::show_card(){
    cout << "현재 패 : ";
    for (auto& card : hand) {
        card.card_info();
    } 
}
string Player::get_name(){
    return name;
}

class Card
{
    char sign = 0;
    short number = 0;
    string card_name = "";

    public:
        Card(){}
        Card(string _card_name, short _number){
            number = _number;
        }
        Card(string _card_name, char _sign){
            sign = _sign;
        }
        void card_info();
};
void Card::card_info(){
    cout<< "|" << card_name << "|" <<endl;
    cout<< "|" << "     " << "|" <<endl;
    if(number == 0) {
        cout<< "| " << sign << "  |" <<endl;
    }
    else if(sign == 0) {
        if(number < 10)
            cout<< "| " << number << "   |" <<endl;
        else if(number > 9) {
            cout<< "| " << number << "  |" <<endl;
        }
    }
    cout<< "|" << "     " <<"|" <<endl;
    cout<< "|" << "     " <<"|" <<endl; 
    cout << "_______" << endl <<endl;
}
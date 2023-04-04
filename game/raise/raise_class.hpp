#include "include.hpp"

class User
{
    int money;
    int water;
    int food;
    string name;

    public:
        User(string _name):money(1000000), water(0), food(0){
            name = _name;
        }

        void user_status();
        void buy_water();
        void buy_food();
        void sell_animal(string animal_name);
        void gamble(int _money);
};
void User::user_status(){
    cout << "당신의 이름 : " << name << endl;
    cout << "현재 보유 금액 : " << money << endl;
    cout << "현재 보유 음식 : " << food << "KG"<< endl;
    cout << "현재 보유 물 : " << water << "L"<<endl;
}

void User::buy_water(){
    int liter = 0;
    cout << "얼마 만큼 사실껀가요? : ";
    cin >> liter;
    cout << " L" << endl;
    water = liter;
    money -= liter * 500;
}
void User::buy_food(){
    int killogram = 0;
    cout << "얼마 만큼 사실껀가요? : ";
    cin >> killogram;
    cout << " kg" << endl;
    food = killogram;
    money -= killogram * 1000;
}
void User::gamble(int beting_money){
    short your_choice;
    short computer_choice;
    money -= beting_money;
    srand(time(NULL));
    string hand[3] = {"가위", "바위", "보"};

    cout << "0. 가위" << endl;
    cout << "1. 바위" << endl;
    cout << "2. 보" << endl;
    cout << "선택 : ";
    cin >> your_choice;
    cout << endl;

    computer_choice = rand() % 3;

    cout << "user : " << hand[your_choice] << endl;
    cout << "computer : " << hand[computer_choice] << endl;

    if (computer_choice == your_choice) {
        cout << "비겼습니다" << endl;
        money += beting_money;
    }else if (computer_choice == (your_choice + 1) % 3) {
        cout << "패배" << endl;
        money -= beting_money;
    }else {
        cout << "승리" << endl;
        money += beting_money * 2;
    }

    cout << endl;
}
void User::sell_animal(string animal_name){
    
}

class Animal
{
    protected:
        bool death;
        short age;
        short weight;
        short height;
        short dirth;
        short mental;
        short hunger;
        string name;

    public:
        Animal(){}
        Animal(string _name):death(false), age(1), weight(10), height(50), dirth(0), mental(0), hunger(0){
            name = _name;
        }
        
        void show_status();
        
};
void Animal::show_status(){
    cout << "이름 : " << name << endl;
    cout << "개월 수 : " << age <<endl;
    cout << "무게 : " << weight << endl;
    cout << "신장 : " << height << endl;
    cout << "청결도 : " << dirth << endl;
    cout << "스트레스 : " << mental <<endl; 
    cout << "배고픔 : " << hunger << endl;
    
}


class Pig : public Animal
{
    string animal_class;

    public:
        Pig(string _name):Animal(){
            animal_class = "pig";
            name = _name;
        }
        void show_status();
};
void Pig::show_status(){
    cout << "동물의 종류 : " << animal_class << endl;
    Animal::show_status();
}

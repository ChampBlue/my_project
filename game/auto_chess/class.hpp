#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#ifndef CLASS_HPP
#define CLASS_HPP

using namespace std;

class Map
{
    short map[3][3] = {{0,0,0},
                    {0,0,0,},
                    {0,0,0}};
    short map_size = 3;

    public:
        Map(){};
        void show_map();
};
void Map::show_map() {
    cout << "===맵===" <<endl;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            cout << map[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

class Player
{
    bool dead;
    short turn;
    short life;
    short coin;
    string name;
    Map& game_map;

    public:
        Player(string _name, Map& _map): dead(false), turn(1), life(30), coin(10),game_map(_map){
            name = _name;
            game_map = _map;
        }

        short get_coin();
        string get_name();
        void player_status();
        void player_gg();
        void gamble_coin(short _coin);
        void show_map_player();
};

short Player::get_coin(){
    return coin;
}
string Player::get_name(){
    return name;
}
void Player::player_status() {
    cout << "플레이어 이름 : " << name << endl;
    cout << "남은 체력 : " << life << endl;
    cout << "보유한 코인 : " << coin << endl;
    game_map.show_map();
}
void Player::player_gg(){
    if(life <= 0) {
        cout << "루져 외톨이 센척하는 겁쟁이~~~~ 패배ㅋ" << endl;
        exit(1);
    }
}
void Player::gamble_coin(short _coin){
    std::random_device seed_value;
    std::mt19937 gen(seed_value());
    std::uniform_int_distribution<int> rand(1, 1000);
    short temp_coin = rand(gen);

    if(temp_coin == 1000)
        coin = _coin * 10;
    else if(temp_coin >= 890 && temp_coin <= 899)
        coin = _coin * 5;        
    else if(temp_coin >= 900 && temp_coin <= 999)
        coin = _coin * 3;
    else if(temp_coin >= 700 && temp_coin <= 799)
        coin = _coin / 2;
    else if(temp_coin >= 880 && temp_coin <= 889)
        coin = _coin / 4;
    else coin = coin;

    cout << "도박 결과 보유 코인 : " << coin << endl;
}
void Player::show_map_player(){
    map.show_map();
}

class Unit
{
    protected:
        short grade;
        short star;
        int damage;
        int defence;
        string name;

    public:
        Unit():star(1), damage(0), defence(0), grade(0), name(""){}

        Unit(short y, short x):star(1), damage(0), defence(0), grade(0), name(""){}
};

class Human: public Unit
{
    short x;
    short y;

    public:
        Human(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 101;
            name = "인간 보병";
            y = _y;
            x = _x;
        }
};

class GreenSkin: public Unit
{
    short x;
    short y;

    public:
        GreenSkin(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 201;
            name = "오크 보병";
            y = _y;
            x = _x;
        }
};

class Vampire: public Unit
{
    short x;
    short y;

    public:
        Vampire(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 301;
            name = "스켈레톤 보병";
            y = _y;
            x = _x;
        }
};

class Chaos: public Unit
{
    short x;
    short y;

    public:
        Chaos(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 401;
            name = "노스카 보병";
            y = _y;
            x = _x;
        }
};

class HighElf: public Unit
{
    short x;
    short y;

    public:
        HighElf(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 501;
            name = "실버문 보병";
            y = _y;
            x = _x;
        }
};

class BeastMan: public Unit
{
    short x;
    short y;

    public:
        BeastMan(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 601;
            name = "언고어 보병";
            y = _y;
            x = _x;
        }
};

class DarkElf: public Unit
{
    short x;
    short y;

    public:
        DarkElf(short _y, short _x):Unit(){
            damage = 10;
            defence = 13;
            grade = 701;
            name = "검은방주 보병";
            y = _y;
            x = _x;
        }
};

#endif
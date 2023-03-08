#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Player
{
    short _player_cost = 1;
    short _HP = 30;
    string _player_name;

    public:
    Player(){}
    //Player(string player_name):_player_name(player_name){}
    //Player(short player_cost, short HP, string player_name) : _player_cost(player_cost), _HP(HP), _player_name(player_name) {}
    
    static void TurnOff();
    
    
    
    void Show_Status()
    {
        cout << "플레이어 이름 : " << _player_name << endl;
        cout << "플레이어 HP : "<< _HP << endl;
        cout << "플레이어 코스트 : " << _player_cost << endl;
    }
};
void Player:: TurnOff()
{
    this->_player_cost = player_cost;
}
class Card
{   
    short cost;
    int attack;
    int defence;
    string name;
    string effect;
    string inchant;

    public:
    Card(){}

    //int attacking();
    //int defencing();
};
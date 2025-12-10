#include "object.hpp"



// OBJECT  #################################################################################################



Object::Object(unsigned int seed)
{
    srand(seed);
    _rare = floor(abs(boxMuller(0, 3, seed))/1.8);
    _throw = rand()%100+1>=95;
    _damage = abs(boxMuller(0, 33, seed))*float(_rare)/5.0;
    _defense = abs(boxMuller(0, 33, seed))*float(_rare)/5.0;
    _pushback = floor(abs(boxMuller(0, 2, seed)))*float(_rare)/5.0;
    if(rand()%100+1==95 || rand()%100+1<10){ 
        _power = rand()%2+1;
    }
    _position = {rand()%COLS+1, rand()%LINES+1};
}

Object::Object(Object_parms o, unsigned int seed)
{
    srand(seed);
    _name = o._name;
    _rare = rand()%5+1;
    _throw = rand()%100+1>=95;
    _damage = o._damage;
    _defense = o._defense;
    _pushback = o._pushback;
    _power = o._power;
    _position = {rand()%COLS+1, rand()%LINES+1};
}

Object::~Object()
{
    _subObject.clear();
}

void Object::update_subObject()
{

    std::pair<int, int> subTest;
    for(SubObject sub : _subObject)
    {
        subTest = {0, 0};
        subTest = sub._position+sub._direction;
        if(subTest.first< COLS-1 && subTest.first>1
                && subTest.second < LINES-1 && subTest.second>1) sub._position = subTest;
       
    }
}

void Object::set_subObject(const std::pair<int, int> &pos,
                            const std::pair<int, int> &dir,
                            const float &dmg)
{
    _subObject.push_back(SubObject(pos, dir, dmg));
}

// Weapon  #################################################################################################
/**
 * @brief 
 * 
 * @param pos 
 * @param dir 
 * @param t 1:distance, 2:AOE, 3:
 */
void Weapon::use(std::pair<int, int> &pos,
                std::pair<int, int> &dir, int t)
{
    switch(t){
        case 1:
            set_subObject(pos, dir, _damage);
            break;
        default:
            set_subObject(pos, dir, _damage);
    }
}



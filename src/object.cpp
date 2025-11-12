#include "object.hpp"
#include "miscellaneous.hpp"

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
} 


// OBJECT  #################################################################################################



Object::Object(unsigned int seed)
{
    srand(seed);
    _rare = floor(abs(boxMuller(0, 3, seed))/1.8);
}

Object::~Object()
{
    _flyControl.clear();
}

void Object::use(const int &x, const int &y,
         const int &look)
{
    //attack(x, y, look);
}

void Object::updateFlyingObj()
{

    std::pair<int, int> ufoTest;
    for(flyingObject ufo : _flyControl)
    {
        ufoTest = {0, 0};
        ufoTest = ufo._position+ufo._direction;
        if(ufoTest.first< COLS-1 && ufoTest.first>1
                && ufoTest.second < LINES-1 && ufoTest.second>1) ufo._position = ufoTest;
       
    }
}

void Object::set_flyControl(const std::pair<int, int> &pos,
                            const std::pair<int, int> &dir,
                            const float &dmg)
{
    _flyControl.push_back(flyingObject(pos, dir, dmg));
}

// WEAPON  #################################################################################################

Weapon::Weapon(unsigned int seed):Object()
{
    srand(seed);
    _id = floor(abs(boxMuller(0, 1400.0/3.0, seed)));
    _throw = rand()%100+1>=95;
    _damage = abs(boxMuller(0, 33, seed))*float(_rare)/5.0;
    _defense = abs(boxMuller(0, 33, seed))*float(_rare)/5.0;
    _pushback = floor(abs(boxMuller(0, 2, seed)))*float(_rare)/5.0;
    if(rand()%100+1==95 || rand()%100+1<10){ 
        _power = rand()%2+1;
    }
}

void initialize()
{

}



void Weapon::use(const int &x, const int &y,
         const int &look)
{
    
}



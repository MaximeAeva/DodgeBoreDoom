#include "living.hpp"

// LIVING  #################################################################################################

/**
 * @brief Build a living creature
 * 
 */
Living::Living(unsigned int seed)
{
    srand(seed);
    _rare = floor(abs(boxMuller(0, 3, seed))/1.8);
    _attackSpeed = floor(abs(boxMuller(0, 3, seed)) + 1);
    _dashSpeed = floor(abs(boxMuller(0, 2, seed)));
    _speed = floor(abs(boxMuller(0, 3, seed)) + 1);
    _life = floor(abs(boxMuller(20, 33, seed)));
    _life %= int(100*(_rare+1)/5.0);
    _life++;
    _currentLife = _life - floor(abs(boxMuller(0, _life/3, seed)));
    _resistance = floor(abs(boxMuller(20, 33, seed)));
    _resistance %= int(100*(_rare+1)/5.0);
    _resistance++;
    _force = floor(abs(boxMuller(20, 33, seed)));
    _force %= int(100*(_rare+1)/5.0);
    _force++;
    _bpSize = 1 + floor(boxMuller(5, 5, seed));//floor(abs(boxMuller(10, 1, seed)) + 1);
    add_backpack(Weapon());
}

/**
 * @brief Construct a new Living:: Living object according to design.txt
 * 
 * @param seed 
 * @param l 
 */
Living::Living(Living_parms l, unsigned int seed)
{
    srand(seed);
    _name = l._name;
    _rare = l._rare;
    _team = l._team;
    _attackSpeed = floor(abs(boxMuller(0, 3, seed)) + 1);
    _dashSpeed = floor(abs(boxMuller(0, 2, seed)));
    _speed = floor(abs(boxMuller(0, 3, seed)) + 1);
    _life = l._life;
    _currentLife = _life - floor(abs(boxMuller(0, _life/3, seed)));
    _resistance = floor(abs(boxMuller(20, 33, seed)));
    _resistance %= int(100*(_rare+1)/5.0);
    _resistance++;
    _force = l._force;
    _bpSize = l._bpSize;//floor(abs(boxMuller(10, 1, seed)) + 1);
    add_backpack(Weapon(object_roll_dice("weapon")));
    _selectedObj = &_backpack[0];
}

/**
 * @brief Destroy life
 * 
 */
Living::~Living()
{
    _backpack.clear();
}


/**
 * @brief Move the living
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void Living::move(std::pair<int, int> vector)
{
    _position = _position + vector;
}

/**
 * @brief Attack !!
 * 
 */
void Living::attack(std::pair<int, int> dir)
{
    if(_selectedObj!=nullptr)
        _selectedObj->use(_position, dir);
}

void Living::add_backpack(Object o)
{
    if(get_bpSize()>_backpack.size()) _backpack.push_back(o);
}

// HERO #################################################################################################




// MOB  #################################################################################################

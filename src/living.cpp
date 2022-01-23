#include "living.hpp"

/**
 * @brief Build a living creature
 * 
 */
living::living() : life(20), currentLife(20), lookTo(1), footPos(false), selectedObj(0)
{
    // Create a weapon
    weapon myWeapon;
    // Create the backpack
    backPack = new object*[bpSize]();
    // Put the weapon in the backpack
    backPack[0] = &myWeapon;
}

/**
 * @brief Destroy life
 * 
 */
living::~living()
{
    // Emptying the backpack
    for(int i = 0; i<bpSize; i++)
    {
        delete backPack[i];
        backPack[i] = NULL;
    }
    // Destroy backpack itself
    delete [] backPack;
}

/**
 * @brief Entering the maze
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void living::place(const int &x, const int &y)
{
    this->position.first=x;
    this->position.second=y;
}

/**
 * @brief Move the living
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void living::move(const int &x, const int &y)
{
    position = {position.first+x, position.second+y};
}

/**
 * @brief Attack !!
 * 
 */
void living::attack(int dir)
{
    if(backPack[selectedObj]!=NULL)
        backPack[selectedObj]->attack(position.first, position.second, dir);
}
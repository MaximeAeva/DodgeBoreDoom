#include "living.hpp"

float Living::boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
}

/**
 * @brief Build a living creature
 * 
 */
Living::Living(unsigned int seed)
{
    srand(seed);
    rare = floor(abs(boxMuller(0, 3, seed))/1.8);
    attackSpeed = floor(abs(boxMuller(0, 3, seed)) + 1);
    dashSpeed = floor(abs(boxMuller(0, 2, seed)));
    speed = floor(abs(boxMuller(0, 3, seed)) + 1);
    life = floor(abs(boxMuller(20, 33, seed)));
    life %= int(100*(rare+1)/5.0);
    life++;
    currentLife = life - floor(abs(boxMuller(0, life/3, seed)));
    resistance = floor(abs(boxMuller(20, 33, seed)));
    resistance %= int(100*(rare+1)/5.0);
    resistance++;
    force = floor(abs(boxMuller(20, 33, seed)));
    force %= int(100*(rare+1)/5.0);
    force++;
    bpSize = 3;//floor(abs(boxMuller(10, 1, seed)) + 1);
    Weapon* myWeapon = new Weapon();
    backPack.push_back(myWeapon);
}

/**
 * @brief Destroy life
 * 
 */
Living::~Living()
{
    // Emptying the backpack
    for(int i = 0; i<bpSize; i++)
    {
        delete backPack[i];
        backPack[i] = NULL;
    }
}

/**
 * @brief Entering the maze
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void Living::place(const int &x, const int &y)
{
    position.first=x;
    position.second=y;
}

/**
 * @brief Move the living
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void Living::move(const int &x, const int &y)
{
    position = {position.first+x, position.second+y};
}

/**
 * @brief Attack !!
 * 
 */
void Living::attack(int dir)
{
    if(backPack[selectedObj]!=NULL)
        backPack[selectedObj]->use(position.first, position.second, dir);
}
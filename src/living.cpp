#include "living.hpp"

// LIVING  #################################################################################################

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
    bpSize = 1 + floor(boxMuller(5, 5, seed));//floor(abs(boxMuller(10, 1, seed)) + 1);
    Weapon* myWeapon = new Weapon();
    addbackpack(myWeapon);
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
        delete backpack[i];
        backpack[i] = NULL;
    }
}

/**
 * @brief Entering the maze
 * 
 * @param x 
 * @param y 
 */
void Living::setposition(const int &x, const int &y)
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
    footPos = !footPos;
}

/**
 * @brief Attack !!
 * 
 */
void Living::attack(int dir)
{
    if(backpack[selectedObj]!=NULL)
        backpack[selectedObj]->use(position.first, position.second, dir);
}

void Living::addbackpack(Object* o)
{
    if(getbpSize()>backpack.size()) backpack.push_back(o);
}

// HERO #################################################################################################

/**
 * @brief Construct a new hero::hero object
 * 
 */
Hero::Hero():Living() 
{
    setteam(1);
}

/**
 * @brief Destroy the hero::hero object
 * 
 */
Hero::~Hero(){}

/**
 * @brief Display life
 * 
 */
void Hero::overlay()
{
    init_pair(11, COLOR_RED, COLOR_RED);
    init_pair(10, COLOR_BLACK, COLOR_BLACK);
    attrset(COLOR_PAIR(10));
    int k = 5; 
    int l = 0;
    for(int i = 1; i<life+1; i++)
    {
        mvaddch(l,k,' ');
        if((i%2)) l = (l+1)%2;
        else 
        {
            if(!(i%4)) k+=2;
            else k++;
        }
    }
    attrset(COLOR_PAIR(11));
    k = 5;
    l = 0;
    for(int i = 1; i<currentLife+1; i++)
    {
        mvaddch(l,k,' ');
        if((i%2)) l = (l+1)%2;
        else 
        {
            if(!(i%4)) k+=2;
            else k++;
        }
    }
}

void Hero::display()
{
    attrset(COLOR_PAIR(rare));
    
    switch(look)
    {
        case 1: //right
            drawTexture(position.first, position.second, std::string("hero"), std::string("body"), std::string("right"));
            break;
        case 2: //up
            drawTexture(position.first, position.second, std::string("hero"), std::string("body"), std::string("up"));
            break;
        case 3: //left
            drawTexture(position.first, position.second, std::string("hero"), std::string("body"), std::string("left"));
            break;
        case 4: //down (sad man ?)
            drawTexture(position.first, position.second, std::string("hero"), std::string("body"), std::string("bottom"));
            break;
        default:
            drawTexture(position.first, position.second, std::string("hero"), std::string("body"), std::string("right"));
    }
    if(footPos%2) drawTexture(position.first, position.second, std::string("hero"), std::string("legs"), std::string("open"));
    else drawTexture(position.first, position.second, std::string("hero"), std::string("legs"));
    
    if(backpack[selectedObj]!=NULL) backpack[selectedObj]->display(position.first, position.second, look);
}

// MOB  #################################################################################################

Mob::Mob():Living()
{
}

Mob::~Mob()
{
}
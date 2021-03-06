#include "mob.hpp"

mob::mob()
{
    std::cout << "A new mob is born" << std::endl;
    this->life = 20;
    this->currentLife = 20;
    this->lookTo = 1;
    this->footPos = false;
    weapon *myWeapon = new weapon;
    this->backPack.push_back(myWeapon);
}

mob::~mob()
{
    for(int i = 0; i<this->backPack.size(); i++)
        delete this->backPack[i];
}

void mob::place(const int &x, const int &y, const int &look)
{
    std::cout << "And placed !" << std::endl;
    init_pair(MobColor, COLOR_GREEN, COLOR_BLACK);
    attrset(COLOR_PAIR(MobColor));
    this->position.first=x;
    this->position.second=y;
    mvaddch(y, x, 'A');
    mvaddch(y+1, x, 'A');
    this->backPack[0]->display(this->position.first, 
            this->position.second, this->lookTo);
}

/**
 * @brief Move the hero
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void mob::move(std::pair<int, int> *Heropos)
{
    int x = 0; int y = 0;
    std::pair<int, int> dir;
    std::cout << "mob : " << position.first << ", " << position.second << std::endl;
    dir.first = this->position.first-Heropos->first;
    std::cout << "3";
    dir.second = this->position.second-Heropos->second;
    std::cout << "da";
    if(!dir.first)
    {
        if(dir.second>0)
            attack(3);
        else 
            attack(1);
    }
    else if(!dir.second)
    {
        if(dir.first>0)
            attack(2);
        else 
            attack(4);
    }
    else if(abs(dir.first) >= abs(dir.second))
    {
        if(dir.first < 0)
        {
            x = 1;
            y = 0;
            this->lookTo = 1;
        }
        else
        {
            x = -1;
            y = 0;
            this->lookTo = 3; 
        }
    } else {
        if(dir.second < 0)
        {
            x = 0;
            y = 1;
            this->lookTo = 4;
        }
        else
        {
            x = 0;
            y = -1;
            this->lookTo = 2; 
        }
    }
    std::cout << "yep";
    init_pair(MobColor, COLOR_GREEN, COLOR_BLACK);
    this->position.first = (COLS + this->position.first + x)%COLS;
    this->position.second = (LINES + this->position.second+y)%LINES;
    this->backPack[0]->display(this->position.first, 
            this->position.second, this->lookTo);
            
    attrset(COLOR_PAIR(MobColor));
    switch (this->lookTo)
    {
        case 1:
            mvaddch(this->position.second,
            this->position.first, 'R');
            break;
        case 2:
            mvaddch(this->position.second,
            this->position.first, 'U');
            break;
        case 3:
            mvaddch(this->position.second,
            this->position.first, 'L');
            break;
        case 4:
            mvaddch(this->position.second,
            this->position.first, 'D');
            break;
    }
    
    if(this->footPos)
    {   
        mvaddch(this->position.second+1,
        this->position.first, 'A');
        this->footPos = false;
    }
    else
    {   
        mvaddch(this->position.second+1, this->position.first, 'A');
        this->footPos = true;
    }
}

/**
 * @brief Attack !!
 * 
 */
void mob::attack(int dir)
{
    this->backPack[0]->attack(this->position.first, 
            this->position.second, dir);
}
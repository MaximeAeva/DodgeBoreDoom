#include "mob.hpp"

mob::mob()
{
    this->life = 20;
    this->currentLife = 20;
    this->lookTo = 1;
    this->footPos = false;
    weapon myWeapon;
    this->backPack.push_back(myWeapon);
}

mob::~mob()
{
    backPack.clear();
}

void mob::place(const int &x, const int &y, const int &look)
{
    init_pair(MobColor, COLOR_GREEN, COLOR_BLACK);
    attrset(COLOR_PAIR(MobColor));
    this->position.first=x;
    this->position.second=y;
    mvaddch(y, x, 'A');
    mvaddch(y+1, x, 'A');
    this->backPack[0].display(this->position.first, 
            this->position.second, this->lookTo);
}

/**
 * @brief Move the hero
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void mob::move(std::pair<int, int> Heropos)
{
    
    int x = 0; int y = 0;
    std::pair<int, int> dir;
    dir.first = this->position.first-Heropos.first;
    dir.second = this->position.second-Heropos.second;
    int k;
    if(this->position.first < 3) k = this->position.first;
    else k = 1;
    mvaddstr(this->position.second, this->position.first-k, "   ");
    mvaddstr(this->position.second+1, this->position.first-k, "   ");
    std::cout << "mobpos : " << position.first << ", " << position.second << std::endl;
    std::cout << "heropos : " << Heropos.first << ", " << Heropos.second << std::endl;
    std::cout << "diff : " <<dir.first << ", " << dir.second << std::endl;
    if(!dir.first)
    {
        if(dir.second>0)
            attack(2);
        else 
            attack(4);
    }
    else if(!dir.second)
    {
        if(dir.first>0)
            attack(3);
        else 
            attack(1);
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
    init_pair(MobColor, COLOR_GREEN, COLOR_BLACK);
    this->position.first = (COLS + this->position.first + x)%COLS;
    this->position.second = (LINES + this->position.second+y)%LINES;
    this->backPack[0].display(this->position.first, 
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
    this->backPack[0].attack(this->position.first, 
            this->position.second, dir);
}
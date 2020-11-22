#include "hero.hpp"

/**
 * @brief Construct a new hero::hero object
 * 
 */
hero::hero()
{
    this->life = 3;
    this->currentLife = 3;
    this->lookTo = 1;
    this->footPos = false;
    this->selectedObj = 0;
    weapon *myWeapon = new weapon;
    this->backPack.push_back(myWeapon);
}

void hero::initialize()
{
    mvaddstr(this->position.second, this->position.first-2, "     ");
    mvaddstr(this->position.second+1, this->position.first-2, "     ");
    if(this->lookTo < 0)
    {   
        mvaddch(this->position.second,
         this->position.first, 0x0272);
        mvaddch(this->position.second,
         this->position.first-1, 0x005C);//modify to weapon class
    }
    else
    {   
        mvaddch(this->position.second,
         this->position.first, 0x0273);
        mvaddch(this->position.second,
         this->position.first+1, '/');
    }
    
    if(this->footPos)
    {   
        mvaddch(this->position.second+1,
         this->position.first, 0x0245);
        this->footPos = false;
    }
    else
    {   
        mvaddch(this->position.second+1, this->position.first, 0x0245);
        this->footPos = true;
    }
}

/**
 * @brief Place the hero on the map
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void hero::place(const int &x, const int &y, const int &look)
{
    init_pair(heroColor, COLOR_WHITE, COLOR_BLACK);
    attrset(COLOR_PAIR(heroColor));
    this->position.first=x;
    this->position.second=y;
    mvaddch(y, x, 0x0273);
    mvaddch(y+1, x, 0x0245);
    this->backPack[this->selectedObj]->display(this->position.first, 
            this->position.second, this->lookTo);
}

/**
 * @brief Move the hero
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void hero::move(const int &x, const int &y, const int &look)
{
    init_pair(heroColor, COLOR_WHITE, COLOR_BLACK);
    mvaddstr(this->position.second, this->position.first-2, "     ");
    mvaddstr(this->position.second+1, this->position.first-2, "     ");
    mvaddstr(this->position.second+2, this->position.first-2, "     ");
    mvaddstr(this->position.second-1, this->position.first-2, "     ");
    this->position.first+=x;
    this->position.second+=y;
    if(look) this->lookTo = look;
    this->backPack[this->selectedObj]->display(this->position.first, 
            this->position.second, this->lookTo);
            
    attrset(COLOR_PAIR(heroColor));
    switch (this->lookTo)
    {
        case 1:
            mvaddch(this->position.second,
            this->position.first, 0x0273);
            break;
        case 2:
            mvaddch(this->position.second,
            this->position.first, 0x0273);
            break;
        case 3:
            mvaddch(this->position.second,
            this->position.first, 0x0272);
            break;
        case 4:
            mvaddch(this->position.second,
            this->position.first, 0x0272);
            break;
    }
    
    if(this->footPos)
    {   
        mvaddch(this->position.second+1,
         this->position.first, 0x0245);
        this->footPos = false;
    }
    else
    {   
        mvaddch(this->position.second+1, this->position.first, '|');
        this->footPos = true;
    }
        
}

/**
 * @brief Attack !!
 * 
 */
void hero::attack()
{
    this->backPack[this->selectedObj]->attack(this->position.first, 
            this->position.second, this->lookTo);
}


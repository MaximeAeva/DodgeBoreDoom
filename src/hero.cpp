#include "hero.hpp"

/**
 * @brief Construct a new hero::hero object
 * 
 */
hero::hero()
{
    this->life = 3;
    this->currentLife = 3;
    this->lookTo = 0;
    this->footPos = false;
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
    this->position.first=x;
    this->position.second=y;
    mvaddch(y, x, 0x0273);
    mvaddch(y, x+1, '/');
    mvaddch(y+1, x, 0x0245);
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
    mvaddstr(this->position.second, this->position.first-2, "     ");
    mvaddstr(this->position.second+1, this->position.first-2, "     ");
    mvaddstr(this->position.second+2, this->position.first-2, "     ");
    mvaddstr(this->position.second-1, this->position.first-2, "     ");
    this->position.first+=x;
    this->position.second+=y;
    if(look) this->lookTo = look;
    switch (this->lookTo)
    {
    case 1:
        mvaddch(this->position.second,
         this->position.first, 0x0273);
        mvaddch(this->position.second,
         this->position.first+1, '/');
        break;
    case 2:
        mvaddch(this->position.second,
         this->position.first, 0x0273);
        mvaddch(this->position.second,
         this->position.first+1, '/');
        break;
    case 3:
       mvaddch(this->position.second,
         this->position.first, 0x0272);
        mvaddch(this->position.second,
         this->position.first-1, 0x005C);//modify to weapon class
        break;
    case 4:
       mvaddch(this->position.second,
         this->position.first, 0x0272);
        mvaddch(this->position.second+1,
         this->position.first-1, '/');//modify to weapon class
        break;
    default:
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
        mvaddch(this->position.second+1, this->position.first, 0x0245);
        this->footPos = true;
    }
        
}

/**
 * @brief Attack !!
 * 
 */
void hero::attack()
{
    switch(this->lookTo)
    {
    case 3:
        mvaddch(this->position.second,
        this->position.first-1, '_');
        mvaddch(this->position.second,
        this->position.first-2, '(');
        break;
    case 1:
        mvaddch(this->position.second,
        this->position.first+1, '_');
        mvaddch(this->position.second,
        this->position.first+2, ')');
        break;
    case 2:
        mvaddch(this->position.second,
        this->position.first+1, ' ');   
        mvaddch(this->position.second,
        this->position.first-1, '_');
        mvaddch(this->position.second-1,
        this->position.first, '_');
        break;
    case 4:
        mvaddch(this->position.second+1,
        this->position.first-1, ' ');
        mvaddch(this->position.second,
        this->position.first+1, '_');
        mvaddch(this->position.second+2,
        this->position.first, '-');
        break;
    }
}


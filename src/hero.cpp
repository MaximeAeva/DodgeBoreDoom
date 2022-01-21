#include "hero.hpp"

/**
 * @brief Construct a new hero::hero object
 * 
 */
hero::hero()
{
    this->life = 12;
    this->currentLife = 7;
    this->lookTo = 1;
    this->footPos = false;
    this->selectedObj = 0;
    weapon myWeapon;
    this->backPack.push_back(myWeapon);
}

hero::~hero()
{
    backPack.clear();
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
    this->backPack[this->selectedObj].display(this->position.first, 
            this->position.second, this->lookTo);
    std::cout << "!";
}

/**
 * @brief Move the hero
 * 
 * @param x 
 * @param y 
 * @param look 
 */
void hero::move(const int &look, map* myMap)
{
    std::pair<int, int> p = myMap->getCurrentPosition();
    room r = myMap->findRoom(p);
    int x, y;
    if(look == 1 && this->position.first < COLS-7)
    {
        x = 1;
        y = 0;
    }
    else if(look == 2 && this->position.second > 3)
    {
        x = 0;
        y = -1;
    }
    else if(look == 3 && this->position.first > 6)
    {
        x = -1;
        y = 0;
    }
    else if(look == 4 && this->position.second < LINES-5)
    {
        x = 0;
        y = 1;
    }
    else
    {
        if(look == 1 && r.neighboors[0]==1 && abs(this->position.second-(LINES/2))<3)
        {
            if(myMap->getDoorInPosition(&r, 0).state)
            {
                x = 1;
                y = 0;
            } else return;
        }   
        else if(look == 2 && r.neighboors[1]==1 && abs(this->position.first-(COLS/2))<3)
        {
            if(myMap->getDoorInPosition(&r, 1).state)
            {
                x = 0;
                y = -1;
            } else return;
        }
        else if(look == 3 && r.neighboors[2]==1 && abs(this->position.second-(LINES/2))<3)
        {
            if(myMap->getDoorInPosition(&r, 2).state)
            {
                x = -1;
                y = 0;
            } else return;
        }
        else if(look == 4 && r.neighboors[3]==1 && abs(this->position.first-(COLS/2))<3)
        {
            if(myMap->getDoorInPosition(&r, 3).state)
            {
                x = 0;
                y = 1;
            } else return;
        }
        else return;
    }
    init_pair(heroColor, COLOR_WHITE, COLOR_BLACK);
    if(this->position.first + x == COLS)
    {
        myMap->setCurrentRoom({r.position.first+1, r.position.second});
        for(int u = 0; u<this->getBackPack().size(); u++) 
            this->getBackPack()[u].killFlyingObj();
    }
    else if(this->position.first + x == -1)
    {
        myMap->setCurrentRoom({r.position.first-1, r.position.second});
        for(int u = 0; u<this->getBackPack().size(); u++) 
            this->getBackPack()[u].killFlyingObj();
    }
    else if(this->position.second + y == LINES)
    {
        myMap->setCurrentRoom({r.position.first, r.position.second+1});
        for(int u = 0; u<this->getBackPack().size(); u++) 
            this->getBackPack()[u].killFlyingObj();
    }
    else if(this->position.second + y == -1)
    {
        myMap->setCurrentRoom({r.position.first, r.position.second-1});
        for(int u = 0; u<this->getBackPack().size(); u++) 
            this->getBackPack()[u].killFlyingObj();
    }
    int k;
    if(this->position.first < 3) k = this->position.first;
    else k = 1;
    mvaddstr(this->position.second, this->position.first-k, "   ");
    mvaddstr(this->position.second+1, this->position.first-k, "   ");
    this->position.first = (COLS + this->position.first + x)%COLS;
    this->position.second = (LINES + this->position.second+y)%LINES;
    if(look) this->lookTo = look;
    this->backPack[this->selectedObj].display(this->position.first, 
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
void hero::attack(int dir)
{
    this->backPack[this->selectedObj].attack(this->position.first, 
            this->position.second, dir);
}

void hero::overlay()
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
    attrset(heroColor);
}

#include "weapon.hpp"

float boxMuller(float mu, float sigma)
{
    float a = (rand() % 100 + 0.001)/100;
    float b = (rand() % 100 + 0.001)/100;

    return (sqrt(-2*log(a))*cos(2*3.141592*b))*sigma + mu;
}

weapon::weapon()
            :object()
{
    int id = rand() % 10 + 1;
    this->id = id;
    switch (id)
    {
    case 1: //sword damage [common 4 to 10 legendary]
        this->damage = 4 + abs(boxMuller(0, 2));
        break;
    case 2:
    case 3: //bow damage [common 2 to 5 legendary]
        this->damage = 2 + abs(boxMuller(0, 1));
        break;
    default: //random thing
        this->damage = 1 + abs(boxMuller(0, 1))/3.0;
        break;
    }
}

void initialize()
{

}

void weapon::display(const int &x, const int &y,
         const int &look)
{
    init_pair(mainstream, COLOR_WHITE, COLOR_BLACK);
    init_pair(common, COLOR_RED, COLOR_BLACK);
    init_pair(supp, COLOR_YELLOW, COLOR_BLACK);
    init_pair(topTier, COLOR_GREEN, COLOR_BLACK);
    init_pair(godLike, COLOR_BLUE, COLOR_BLACK);
    init_pair(legendary, COLOR_CYAN, COLOR_BLACK);

    std::cout << this->damage;
    switch(this->id)
    {
        case 1:
            attrset(COLOR_PAIR(floor(this->damage)-4));
            switch(look)
            {
            case 1: //right
                mvaddch(y, x+1, '/');
                break;
            case 2: //up
                mvaddch(y, x+1, '/');
                break;
            case 3: //left
                mvaddch(y, x-1, 0x005C);
                break;
            case 4: //down (sad man ?)
                mvaddch(y+1, x-1, '/');
                break;
            }
        break;
        case 2:
        case 3:
            attrset(COLOR_PAIR(floor((this->damage-2)*2)));
            switch(look)
            {
            case 1: //right
                mvaddch(y, x+1, 0x025F);
                break;
            case 2: //up
                mvaddch(y, x+1, 0x025F);
                break;
            case 3: //left
                mvaddch(y, x-1, 0x01AD);
                break;
            case 4: //down (sad man ?)
                mvaddch(y+1, x-1, 0x01AD);
                break;
            }
        break;
        default:
            attrset(COLOR_PAIR(floor((this->damage-1)*6)));
            switch(look)
            {
            case 1: //right
                mvaddch(y, x+1, 0x0840);
                break;
            case 2: //up
                mvaddch(y, x+1, 0x0840);
                break;
            case 3: //left
                mvaddch(y, x-1, 0x0840);
                break;
            case 4: //down (sad man ?)
                mvaddch(y+1, x-1, 0x0840);
                break;
            }
        break;
    }
}
void attack(const int &x, const int &y,
         const int &look)
{

}


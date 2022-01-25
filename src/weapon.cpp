#include "weapon.hpp"

float weapon::boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
}

weapon::weapon(unsigned int seed):object()
{
    srand(seed);
    id = floor(abs(boxMuller(0, 1400.0/3.0, seed)));
    if(rand()%100+1>=95){ 
        weapon flyer;
        daughterObj = &flyer;
    }
    damage = abs(boxMuller(0, 33, seed))*float(rare)/5.0;
    defense = abs(boxMuller(0, 33, seed))*float(rare)/5.0;
    pushback = floor(abs(boxMuller(0, 2, seed)))*float(rare)/5.0;
    if(rand()%100+1==95 || rand()%100+1<10){ 
        power = rand()%2+1;
    }
}

weapon::~weapon()
{
    id = 0;
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
    attrset(COLOR_PAIR(rare));
    switch(look)
    {
        case 1: //right
            drawTexture(y, x, std::string("weapon"), std::string(std::to_string(id)), std::string("right"));
            break;
        case 2: //up
            drawTexture(y, x, std::string("weapon"), std::string(std::to_string(id)), std::string("up"));
            break;
        case 3: //left
            drawTexture(y, x, std::string("weapon"), std::string(std::to_string(id)), std::string("left"));
            break;
        case 4: //down (sad man ?)
            drawTexture(y, x, std::string("weapon"), std::string(std::to_string(id)), std::string("bottom"));
            break;
    }
    
}

void weapon::use(const int &x, const int &y,
         const int &look)
{
    init_pair(mainstream, COLOR_WHITE, COLOR_BLACK);
    init_pair(common, COLOR_RED, COLOR_BLACK);
    init_pair(supp, COLOR_YELLOW, COLOR_BLACK);
    init_pair(topTier, COLOR_GREEN, COLOR_BLACK);
    init_pair(godLike, COLOR_BLUE, COLOR_BLACK);
    init_pair(legendary, COLOR_CYAN, COLOR_BLACK);

    switch(this->id)
    {
        case 1:
            switch(look)
            {
                case 1: //right
                    addFlyingObject({x+2, y}, COLOR_PAIR(floor(this->damage)-4), 
                        {1, 0}, this->id, look, this->damage);
                    break;
                case 2: //up
                    addFlyingObject({x, y-1}, COLOR_PAIR(floor(this->damage)-4), 
                        {0, -1}, this->id, look, this->damage);
                    break;
                case 3: //left
                    addFlyingObject({x-2, y}, COLOR_PAIR(floor(this->damage)-4), 
                        {-1, 0}, this->id, look, this->damage);
                    break;
                case 4: //down (sad man ?)
                    addFlyingObject({x, y+2}, COLOR_PAIR(floor(this->damage)-4), 
                        {0, 1}, this->id, look, this->damage);
                    break;
            }
        break;
        case 2:
        case 3:
            switch(look)
            {
                case 1: //right
                    addFlyingObject({x+2, y}, COLOR_PAIR(floor((this->damage-2)*2)), 
                        {1, 0}, this->id, look, this->damage);
                    break;
                case 2: //up
                    addFlyingObject({x, y-1}, COLOR_PAIR(floor((this->damage-2)*2)), 
                        {0, -1}, this->id, look, this->damage);
                    break;
                case 3: //left
                    addFlyingObject({x-2, y}, COLOR_PAIR(floor((this->damage-2)*2)), 
                        {-1, 0}, this->id, look, this->damage);
                    break;
                case 4: //down (sad man ?)
                    addFlyingObject({x, y+2}, COLOR_PAIR(floor((this->damage-2)*2)), 
                        {0, 1}, this->id, look, this->damage);
                    break;
            }
        break;
        default:
            switch(look)
            {
                case 1: //right
                    addFlyingObject({x+2, y}, COLOR_PAIR(floor((this->damage-1)*6)), 
                        {1, 0}, this->id, look, this->damage);
                    break;
                case 2: //up
                    addFlyingObject({x, y-1}, COLOR_PAIR(floor((this->damage-1)*6)), 
                        {0, -1}, this->id, look, this->damage);
                    break;
                case 3: //left
                    addFlyingObject({x-2, y}, COLOR_PAIR(floor((this->damage-1)*6)), 
                        {-1, 0}, this->id, look, this->damage);
                    break;
                case 4: //down (sad man ?)
                    addFlyingObject({x, y+2}, COLOR_PAIR(floor((this->damage-1)*6)), 
                        {0, 1}, this->id, look, this->damage);
                    break;
            }
        break;
    }
}



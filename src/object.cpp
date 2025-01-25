#include "object.hpp"


// OBJECT  #################################################################################################

float Object::boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
}

Object::Object(unsigned int seed)
{
    srand(seed);
    rare = floor(abs(boxMuller(0, 3, seed))/1.8);
}

Object::~Object()
{
    flyControl.clear();
}

void Object::display(const int &x, const int &y,
         const int &look)
{
    std::cout<< "disp obj"<<std::endl;
    mvaddch(y, x+2, 'a');
}

void Object::use(const int &x, const int &y,
         const int &look)
{
    //attack(x, y, look);
}

void Object::updateFlyingObj()
{
    init_pair(0, COLOR_WHITE, COLOR_BLACK);
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    for(int i = 0; i<flyControl.size(); i++)
    {
        if(flyControl[i].currentPosition.first< COLS-6 && flyControl[i].currentPosition.first>5
                && flyControl[i].currentPosition.second < LINES-4 && flyControl[i].currentPosition.second>3)
        {
            attrset(flyControl[i].color);
            int xInit = flyControl[i].currentPosition.second;
            int yInit = flyControl[i].currentPosition.first;
            flyControl[i].currentPosition.first += flyControl[i].direction.first;
            flyControl[i].currentPosition.second += flyControl[i].direction.second;
            
            switch(flyControl[i].id)
            {
                case 1:
                    switch(flyControl[i].look)
                    {
                        case 1: //right
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, '}');
                            break;
                        case 2: //up
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, '^');
                            break;
                        case 3: //left
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, '{');
                            break;
                        case 4: //down (sad man ?)
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 'v');
                            break;
                    }
                break;
                case 2:
                case 3:
                    switch(flyControl[i].look)
                    {
                        case 1: //right
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 0x2192);
                            break;
                        case 2: //up
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 0x2191);
                            break;
                        case 3: //left
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 0x2190);
                            break;
                        case 4: //down (sad man ?)
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 0x2193);
                            break;
                    }
                break;
                default:
                    switch(flyControl[i].look)
                    {
                        case 1: //right
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 'x');
                            break;
                        case 2: //up
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 'x');
                            break;
                        case 3: //left
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 'x');
                            break;
                        case 4: //down (sad man ?)
                            mvaddch(flyControl[i].currentPosition.second, 
                            flyControl[i].currentPosition.first, 'x');
                            break;
                    }
                break;
            }
            mvaddch(xInit, yInit, ' ');
        }
    }
}

void Object::addFlyingObject(const std::pair<int, int> &currentPosition, const chtype &color,
                const std::pair<int, int> &direction, const int &id, const int &look, const float &dmg)
{
    flyingObject ufo;
    ufo.color = color;
    ufo.currentPosition = currentPosition;
    ufo.direction = direction;
    ufo.id = id;
    ufo.look = look;
    ufo.dmg = dmg;
    flyControl.push_back(ufo);
}

void Object::killFlyingObj()
{
    for(int i = 0; i<flyControl.size(); i++)
        mvaddch(flyControl[i].currentPosition.second,
                flyControl[i].currentPosition.first, ' ');

    flyControl.clear();
}


// WEAPON  #################################################################################################

float Weapon::boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
}

Weapon::Weapon(unsigned int seed):Object()
{
    srand(seed);
    id = floor(abs(boxMuller(0, 1400.0/3.0, seed)));
    if(rand()%100+1>=95){ 
        Weapon flyer;
        daughterObj = &flyer;
    }
    damage = abs(boxMuller(0, 33, seed))*float(rare)/5.0;
    defense = abs(boxMuller(0, 33, seed))*float(rare)/5.0;
    pushback = floor(abs(boxMuller(0, 2, seed)))*float(rare)/5.0;
    if(rand()%100+1==95 || rand()%100+1<10){ 
        power = rand()%2+1;
    }
}

Weapon::~Weapon()
{
    id = 0;
}

void initialize()
{

}

void Weapon::display(const int &x, const int &y,
         const int &look)
{
    
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

void Weapon::use(const int &x, const int &y,
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



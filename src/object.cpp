#include "object.hpp"
#include <iostream>

float object::boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
}

object::object(unsigned int seed)
{
    srand(seed);
    rare = floor(abs(boxMuller(0, 3, seed))/1.8);
}

object::~object()
{
    flyControl.clear();
}

void object::display(const int &x, const int &y,
         const int &look)
{
    mvaddch(y, x+2, 'a');
    std::cout<< "disp obj"<<std::endl;
}

void object::use(const int &x, const int &y,
         const int &look)
{
    //attack(x, y, look);
}

void object::updateFlyingObj()
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

void object::addFlyingObject(const std::pair<int, int> &currentPosition, const chtype &color,
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

void object::killFlyingObj()
{
    for(int i = 0; i<flyControl.size(); i++)
        mvaddch(flyControl[i].currentPosition.second,
                flyControl[i].currentPosition.first, ' ');

    flyControl.clear();
}
#include "object.hpp"

object::~object()
{
    for(int i = 0; i<this->flyControl.size(); i++)
        delete this->flyControl[i];
}

void object::display(const int &x, const int &y,
         const int &look)
{
    display(x, y, look);
}

void object::attack(const int &x, const int &y,
         const int &look)
{
    attack(x, y, look);
}

void object::updateFlyingObj()
{
    for(int i = 0; i<flyControl.size(); i++)
    {
        attrset(flyControl[i]->color);
        mvaddch(flyControl[i]->currentPosition.second,
         flyControl[i]->currentPosition.first, ' ');
        flyControl[i]->currentPosition.first += flyControl[i]->direction.first;
        flyControl[i]->currentPosition.second += flyControl[i]->direction.second;
        switch(flyControl[i]->id)
        {
            case 1:
                switch(flyControl[i]->look)
                {
                    case 1: //right
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, ')');
                        break;
                    case 2: //up
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '_');
                        break;
                    case 3: //left
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '(');
                        break;
                    case 4: //down (sad man ?)
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '_');
                        break;
                }
            break;
            case 2:
            case 3:
                switch(flyControl[i]->look)
                {
                    case 1: //right
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '-');
                        break;
                    case 2: //up
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '|');
                        break;
                    case 3: //left
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '-');
                        break;
                    case 4: //down (sad man ?)
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, '|');
                        break;
                }
            break;
            default:
                switch(flyControl[i]->look)
                {
                    case 1: //right
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, 'x');
                        break;
                    case 2: //up
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, 'x');
                        break;
                    case 3: //left
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, 'x');
                        break;
                    case 4: //down (sad man ?)
                        mvaddch(flyControl[i]->currentPosition.second, 
                        flyControl[i]->currentPosition.first, 'x');
                        break;
                }
            break;
        }
    }
}

void object::addFlyingObject(const std::pair<int, int> &currentPosition, const chtype &color,
                const std::pair<int, int> &direction, const int &id, const int &look)
{
    flyingObject *ufo = new flyingObject;
    ufo->color = color;
    ufo->currentPosition = currentPosition;
    ufo->direction = direction;
    ufo->id = id;
    ufo->look = look;
    this->flyControl.push_back(ufo);
}
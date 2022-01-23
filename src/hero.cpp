#include "hero.hpp"

/**
 * @brief Construct a new hero::hero object
 * 
 */
hero::hero() : living(){}

/**
 * @brief Destroy the hero::hero object
 * 
 */
hero::~hero(){}

/**
 * @brief Display life
 * 
 */
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

void display()
{
    
}
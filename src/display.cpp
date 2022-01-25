#include "display.hpp"

/**
 * @brief Draw the desired object at the wanted place
 * 
 * @param x x coordinate
 * @param y y coordinate
 * @param category cat (hero, mob, objects, weapons ...)
 * @param subcat subcat (bigMonster, sword)
 * @param position which one (right, left, up, down)
 */
void drawTexture(const int &x, const int &y, std::string category, std::string subcat, std::string position)
{
    if(category=="hero")
    {
        if(subcat=="body")
        {
            if(position=="left"||position=="bottom")
                mvaddch(y-1, x, 0x0272);// ɲ
            else
                mvaddch(y-1, x, 0x0273);// ɳ
        }
        else if(subcat=="legs")
        {
            if(position=="open")
                mvaddch(y, x, 0x0245);// Ʌ
            else
                mvaddch(y, x, 0x007C);// |
        }
        else
        {
            std::cout<<"Problem on texture arguments"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else if(category=="weapon")
    {
        if(position=="left")
            mvaddch(y-1, x-1, std::stoi(subcat));// ↽
        else if(position=="right")
            mvaddch(y-1, x+1, std::stoi(subcat));// ⇁
        else if(position=="up")
            mvaddch(y-1, x+1, std::stoi(subcat));// ↾
        else
            mvaddch(y, x-1, std::stoi(subcat));// ⇃
    }
    else if(category=="object")
    {
        if(subcat=="chest")
        {
        }
        else if(subcat=="key")
        {
        }
        else if(subcat=="potion")
        {
        }
        else
        {
            std::cout<<"Problem on texture arguments"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
    else if(category=="door")
    {
    }
    else if(category=="wall")
    {
    }
    else
    {
        std::cout<<"Problem on texture arguments"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
}
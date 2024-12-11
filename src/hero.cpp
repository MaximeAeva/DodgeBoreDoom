#include "hero.hpp"

/**
 * @brief Construct a new hero::hero object
 * 
 */
Hero::Hero():Living() 
{
    setTeam(1);
}

/**
 * @brief Destroy the hero::hero object
 * 
 */
Hero::~Hero(){}

/**
 * @brief Display life
 * 
 */
void Hero::overlay()
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
}

void Hero::display()
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
            drawTexture(position.second, position.first, std::string("hero"), std::string("body"), std::string("right"));
            break;
        case 2: //up
            drawTexture(position.second, position.first, std::string("hero"), std::string("body"), std::string("up"));
            break;
        case 3: //left
            drawTexture(position.second, position.first, std::string("hero"), std::string("body"), std::string("left"));
            break;
        case 4: //down (sad man ?)
            drawTexture(position.second, position.first, std::string("hero"), std::string("body"), std::string("bottom"));
            break;
        default:
            drawTexture(position.second, position.first, std::string("hero"), std::string("body"), std::string("right"));
    }
    if(footPos) drawTexture(position.second, position.first, std::string("hero"), std::string("legs"), std::string("open"));
    else drawTexture(position.second, position.first, std::string("hero"), std::string("legs"));
    
    if(backPack[selectedObj]!=NULL) backPack[selectedObj]->display(position.first, position.second, look);
}
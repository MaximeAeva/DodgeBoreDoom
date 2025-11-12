#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <PDCurses-3.9/curses.h>
#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "living.hpp"
#include "display.hpp"
#include "map.hpp"



int main(int argc, char *argv[])
{
    time_t seed;
    seed = time((time_t *)0);
    srand(seed);

    //Screen initialisation
    screenInit();
 
    // Creating map
    Map gameMap(5);

    Room r;
    Door d;

    for(int i = 0; i<5; i++){
        r = gameMap.get_room(i);
        std::cout << r.get_position().first << "; " << r.get_position().second << std::endl;
        std::cout << r.get_neighboors()[0]<< "; " <<r.get_neighboors()[1]<< "; " <<r.get_neighboors()[2]<< "; " <<r.get_neighboors()[3]<< std::endl;
    }

    d = gameMap.get_door(0);
    std::cout << d.get_rooms().first->get_position().first << ", " << d.get_rooms().first->get_position().second;
    std::cout << " : ";
    std::cout << d.get_rooms().second->get_position().first << ", " << d.get_rooms().second->get_position().second;
    std::cout << std::endl;
    

    Hero hero;
    hero.setposition(int(COLS/2), int(LINES/2));
    hero.display();
    hero.overlay();
    
    int att_tempo = 0;
    int av_tempo = 0;
    int dsh_tempo = 0;
    int mob_tempo = 0;
    int obj_tempo = 0;

    while(true)
    {

        //Initialize timers
        att_tempo++;
        av_tempo++;
        dsh_tempo++;
        mob_tempo++;
        obj_tempo++;

        

        
        switch (getch())
        {
            case 'p':
            case 'P':
                curs_set(1);
                endwin();
                return EXIT_SUCCESS;
                break;
            #ifdef KEY_RESIZE    
                case KEY_RESIZE:
                    # ifdef PDCURSES
                        resize_term(0, 0);
                    # endif
            #endif
        }
        
        if(GetAsyncKeyState(0x5A))   
        {
            if(att_tempo>10)
            {
                hero.attack(2);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x51))   
        {
            if(att_tempo>10)
            {
                hero.attack(3);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x53))   
        {
            if(att_tempo>10)
            {
                hero.attack(4);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x44))   
        {
            if(att_tempo>10)
            {
                hero.attack(1);
                att_tempo = 0;
            }
            flushinp();
        }
        

        if(GetAsyncKeyState(VK_UP))   
        {
            if(av_tempo>2)
            {
                hero.move(0, -1);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_DOWN))   
        {
            if(av_tempo>2)
            {
                hero.move(0, 1);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            if(av_tempo>2)
            {
                hero.move(2, 0);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            if(av_tempo>2)
            {
                hero.move(-2, 0);
                av_tempo = 0;
            }
            flushinp();
        }

        erase();
        hero.overlay();
        hero.display();
        napms(50);
        
        
    }

    return(0);
}

#define PDC_WIDE

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
#include "miscellaneous.hpp"



int main(int argc, char *argv[])
{
    time_t seed;
    seed = time((time_t *)0);
    srand(seed);

    // Upload design.txt file
    loadDesign();
 
    // Creating map
    Map gameMap(5);
    
    // Create a display
    Display dsp;

    //Create a hero
    Hero hero(living_find("hero"));
    hero.set_position({int(LINES/2), int(COLS/2)});

<<<<<<< HEAD
=======
    //gameMap.set_livings(hero);

>>>>>>> 59e9fe3b176c105ce004994a1af9e436691e916b
    dsp.draw_living(hero);
    dsp.draw_map(gameMap);

    int att_tempo = 0;
    int av_tempo = 0;
    int dsh_tempo = 0;
    int mob_tempo = 0;
    int obj_tempo = 0;

    while(true)//Main loop
    {
        
        //Initialize timers
        att_tempo++;
        av_tempo++;
        dsh_tempo++;
        mob_tempo++;
        obj_tempo++;
        if(av_tempo!=0)
        {
            dsp.erase_object(*hero.get_selectedObj());
        }   
        hero.update_backpack();
        

        
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
                hero.attack({-1, 0});
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x51))   
        {
            if(att_tempo>10)
            {
                hero.attack({0, -1});
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x53))   
        {
            if(att_tempo>10)
            {
                hero.attack({1, 0});
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x44))   
        {
            if(att_tempo>10)
            {
                hero.attack({0, 1});
                att_tempo = 0;
            }
            flushinp();
        }
        

        if(GetAsyncKeyState(VK_UP))   
        {
            if(av_tempo>2)
            {
                dsp.erase_living(hero);
                hero.move({-1, 0});
                dsp.draw_living(hero);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_DOWN))   
        {
            if(av_tempo>2)
            {
                dsp.erase_living(hero);
                hero.move({1, 0});
                dsp.draw_living(hero);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            if(av_tempo>2)
            {
                dsp.erase_living(hero);
                hero.move({0, 2});
                dsp.draw_living(hero);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            if(av_tempo>2)
            {
                dsp.erase_living(hero);
                hero.move({0, -2});
                dsp.draw_living(hero);
                av_tempo = 0;
            }
            flushinp();
        }
        if(av_tempo!=0)
        {
            dsp.draw_object(*hero.get_selectedObj());
        } 

        
        refresh();
        napms(20);
        
        
    }

    return(0);
}

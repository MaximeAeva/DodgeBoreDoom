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
    Map gameMap(3);
    
    Hero Vanessa;
    Vanessa.setposition(int(COLS/2), int(LINES/2));
    Vanessa.display();
    Vanessa.overlay();
    
    int att_tempo = 0;
    int av_tempo = 0;
    int dsh_tempo = 0;
    int mob_tempo = 0;
    int obj_tempo = 0;
    
    gameMap.setRoom();

    while(true)
    {

        //Initialize timers
        att_tempo++;
        av_tempo++;
        dsh_tempo++;
        mob_tempo++;
        obj_tempo++;

        
        if(!(obj_tempo % 2))
            for(int i = 0; i<Vanessa.getbackpack().size(); i++)
                Vanessa.getbackpack()[i]->updateFlyingObj();

        /*
        if(!(obj_tempo % 4))
        {
            for(int i = 0; i<gameMap.mobs.size(); i++)
                gameMap.mobs[i].backPack[0]->updateFlyingObj();
            obj_tempo = 0;
        }
        
        
        if(mob_tempo >= 8)
        {
            gameMap.updateRoomNMobs(Vanessa.getPosition());                
            mob_tempo = 0;
        }

        */
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
                Vanessa.attack(2);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x51))   
        {
            if(att_tempo>10)
            {
                Vanessa.attack(3);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x53))   
        {
            if(att_tempo>10)
            {
                Vanessa.attack(4);
                att_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(0x44))   
        {
            if(att_tempo>10)
            {
                Vanessa.attack(1);
                att_tempo = 0;
            }
            flushinp();
        }
        

        if(GetAsyncKeyState(VK_UP))   
        {
            if(av_tempo>2)
            {
                Vanessa.move(0, 1);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_DOWN))   
        {
            if(av_tempo>2)
            {
                Vanessa.move(0, -1);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            if(av_tempo>2)
            {
                Vanessa.move(2, 0);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            if(av_tempo>2)
            {
                Vanessa.move(-2, 0);
                av_tempo = 0;
            }
            flushinp();
        }

        erase();
        Vanessa.overlay();
        Vanessa.display();
        napms(10);
        
        
    }

    return(0);
}

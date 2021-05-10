#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <PDCurses-3.8/curses.h>

#include <stdlib.h>
#include <windows.h>
#include <time.h>

#include "hero.hpp"

int main(int argc, char *argv[])
{
    time_t seed;
    int x, y, j, r, c;



#ifdef XCURSES
    Xinitscr(argc, argv);
#else
    initscr();
#endif
    seed = time((time_t *)0);
    srand(seed);
    

    map gameMap(15);

    if (has_colors())
    {
        short bg = COLOR_BLACK;

        start_color();

#if defined(NCURSES_VERSION) || (defined(PDC_BUILD) && PDC_BUILD > 3000)
        if (use_default_colors() == OK)
            bg = -1;
#endif
        init_pair(1, COLOR_RED, bg);
        init_pair(2, COLOR_BLUE, bg);
        init_pair(3, COLOR_WHITE, bg);
    }

    nl();
    noecho();
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
    
    r = LINES - 4;
    c = COLS - 4;

    hero Vanessa;
    Vanessa.place(round(COLS/2), round(LINES/2));
    int att_tempo = 0;
    int av_tempo = 0;
    int dsh_tempo = 0;
    int mob_tempo = 0;
    int obj_tempo = 0;
    gameMap.designRoom();
    while(true)
    {
        att_tempo++;
        av_tempo++;
        dsh_tempo++;
        mob_tempo++;
        obj_tempo++;

        if(mob_tempo >= 15)
        {
            for(int i = 0; i<Vanessa.getBackPack().size(); i++)
            {
                Vanessa.getBackPack()[i]->updateFlyingObj();
                for(int j = 0; j<gameMap.mobs.size(); j++)
                    gameMap.mobs[j].getBackPack()[0]->updateFlyingObj();
            }
            obj_tempo = 0;
        }
        
        Vanessa.overlay();
        if(mob_tempo >= 20)
        {
            gameMap.updateRoomNMobs(Vanessa.getPosition());                
            mob_tempo = 0;
        }

        
        switch (getch())
        {
        case 'p':
        case 'P':
            curs_set(1);
            endwin();
            return EXIT_SUCCESS;
        #ifdef KEY_RESIZE
            break;
        case KEY_RESIZE:
            # ifdef PDCURSES
                        resize_term(0, 0);
            # endif
                        r = LINES - 4;
                        c = COLS - 4;
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
        if(GetAsyncKeyState(0x45))   
        {
            if(dsh_tempo>20)
            {
                Vanessa.dash(&gameMap);
                dsh_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_UP))   
        {
            if(av_tempo>2)
            {
                Vanessa.move(2, &gameMap);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_DOWN))   
        {
            if(av_tempo>2)
            {
                Vanessa.move(4, &gameMap);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            if(av_tempo>2)
            {
                Vanessa.move(1, &gameMap);
                av_tempo = 0;
            }
            flushinp();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            if(av_tempo>2)
            {
                Vanessa.move(3, &gameMap);
                av_tempo = 0;
            }
            flushinp();
        }

        
        napms(10);
    }
}
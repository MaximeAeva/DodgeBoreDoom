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

    x = 50;
    y = 20;

    hero Vanessa;
    Vanessa.place(x, y);

    for (j = 0;;)
    {
        for(int i = 0; i<Vanessa.getBackPack().size(); i++)
            Vanessa.getBackPack()[i]->updateFlyingObj();
        

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
            Vanessa.attack(2);
            flushinp();
        }
        if(GetAsyncKeyState(0x51))   
        {
            Vanessa.attack(3);
            flushinp();
        }
        if(GetAsyncKeyState(0x53))   
        {
            Vanessa.attack(4);
            flushinp();
        }
        if(GetAsyncKeyState(0x44))   
        {
            Vanessa.attack(1);
            flushinp();
        }
        if(GetAsyncKeyState(VK_UP))   
        {
            Vanessa.move(0, -1, 2);
            flushinp();
        }
        if(GetAsyncKeyState(VK_DOWN))   
        {
            Vanessa.move(0, 1, 4);
            flushinp();
        }
        if(GetAsyncKeyState(VK_RIGHT))
        {
            Vanessa.move(1, 0, 1);
            flushinp();
        }
        if(GetAsyncKeyState(VK_LEFT))
        {
            Vanessa.move(-1, 0, 3);
            flushinp();
        }

        
        napms(50);
    }
}
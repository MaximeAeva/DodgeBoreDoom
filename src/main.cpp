#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
#include <PDCurses-3.8/curses.h>

#include <stdlib.h>
#include <time.h>

#include "hero.hpp"

int main(int argc, char *argv[])
{
    time_t seed;
    int x, y, j, r, c;
    static int xpos[5], ypos[5];

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

    for (j = 5; --j >= 0;)
    {
        xpos[j] = rand() % c + 2;
        ypos[j] = rand() % r + 2;
    }

    x = rand() % c + 2;
    y = rand() % r + 2;

    hero Vanessa;
    Vanessa.place(x, y);

    for (j = 0;;)
    {
        //Vanessa.initialize();
        attrset(COLOR_PAIR(2));
        switch (getch())
        {
        case 'q':
        case 'Q':
            curs_set(1);
            endwin();
            return EXIT_SUCCESS;
        case 'b':
            Vanessa.attack();
            break;
        case KEY_UP:    // key up
            Vanessa.move(0, -1, 2);
            flushinp();
        break;
        case KEY_DOWN:    // key down
            Vanessa.move(0, 1, 4);
            flushinp();
        break;
        case KEY_RIGHT:    // key right
            Vanessa.move(1, 0, 1);
            flushinp();
        break;
        case KEY_LEFT:    // key left
            Vanessa.move(-1, 0, 3);
            flushinp();
        break;
        case 's':
            nodelay(stdscr, FALSE);
            break;
        case ' ':
            nodelay(stdscr, TRUE);
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
        napms(50);
    }
}
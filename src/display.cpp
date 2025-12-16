#include "display.hpp"


Display::Display(){

    #ifdef XCURSES
        Xinitscr(argc, argv);
    #else
        initscr();
        int row, col;
        getmaxyx(stdscr, row, col);
        wresize(stdscr, row-1, col-1);
                     
    #endif
    if (has_colors())
    {
        short bg = COLOR_BLACK;

        start_color();

        #if defined(NCURSES_VERSION) || (defined(PDC_BUILD) && PDC_BUILD > 3000)
                if (use_default_colors() == OK)
                    bg = -1;
        #endif
        
        init_pair(1, COLOR_WHITE, COLOR_BLACK);
        init_pair(2, COLOR_RED, COLOR_BLACK);
        init_pair(3, COLOR_YELLOW, COLOR_BLACK);
        init_pair(4, COLOR_GREEN, COLOR_BLACK);
        init_pair(5, COLOR_BLUE, COLOR_BLACK);
        init_pair(6, COLOR_CYAN, COLOR_BLACK);
        init_pair(12, COLOR_BLACK, COLOR_RED);
    }

    nl();
    noecho();
    cbreak(); 
    curs_set(0);
    timeout(0);
    keypad(stdscr, TRUE);
}

/**
 * @brief Display Living according to design.txt
 * 
 * @param l 
 */
void Display::draw_living(Living &l){
    attron(COLOR_PAIR(l.get_rare()));
    int dspIdx = 0;
    
    Living_parms lp = living_find("", l.get_name());
    //Upper body
    dspIdx = 0+lookValue(l.get_look());
    mvaddch(l.get_position().first-1, l.get_position().second, lp._display[dspIdx]);
    //Lower body
    dspIdx = 3+lookValue(l.get_look());
    mvaddch(l.get_position().first, l.get_position().second, lp._display[dspIdx]);

    attroff(COLOR_PAIR(l.get_rare()));

    if(l.get_selectedObj()!=nullptr)draw_object(*l.get_selectedObj());
 }

 /**
  * @brief Erase Living from the display
  * 
  * @param l 
  */
 void Display::erase_living(Living &l){
    chtype ch = ' ' | COLOR_PAIR(1);
    mvaddch(l.get_position().first-1, l.get_position().second, ch);
    mvaddch(l.get_position().first, l.get_position().second, ch);

    if(l.get_selectedObj()!=nullptr)erase_object(*l.get_selectedObj());
}

void Display::draw_object(Object &o){
    attron(COLOR_PAIR(o.get_rare()));
    int dspIdx = 0;
    
    Object_parms op = object_find("", o.get_name());
    //Upper body
    dspIdx = lookValue(o.get_look());
    mvaddch(o.get_position().first, o.get_position().second, op._display[dspIdx]);

    attroff(COLOR_PAIR(o.get_rare()));

    if(o.get_subObject().size()){
        dspIdx += 4;
        attron(COLOR_PAIR(12));
            for(SubObject so: o.get_subObject())
                mvaddch(so._position.first, so._position.second, op._display[dspIdx]);
        attroff(COLOR_PAIR(12));
    }

}

 void Display::erase_object(Object &o){
    chtype ch = ' ' | COLOR_PAIR(1);
    mvaddch(o.get_position().first, o.get_position().second, ch);
    if(o.get_subObject().size()){
        for(SubObject so: o.get_subObject())
            mvaddch(so._position.first, so._position.second, ch);
    }
 }


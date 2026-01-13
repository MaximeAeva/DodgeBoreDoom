#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <PDCurses-3.9/curses.h>

#include "miscellaneous.hpp"
#include "living.hpp"
#include "object.hpp"
#include "map.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class Display{
    public:
        Display();

        void draw_living(Living &l);
        void draw_object(Object &o);
        void draw_map(Map &m);
        void draw_overlay(); 

        void erase_living(Living &l);
        void erase_object(Object &o);

};


#endif
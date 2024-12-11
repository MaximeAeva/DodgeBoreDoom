#ifndef HERO_H
#define HERO_H

#include <utility>
#include <vector>
#include <PDCurses-3.9/curses.h>
#include "weapon.hpp"
#include "map.hpp"
#include "living.hpp"

class living;

class Hero : public Living {
    public:
        Hero();
        ~Hero();
        void overlay();
        void display();
};

#endif
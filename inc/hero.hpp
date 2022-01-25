#ifndef HERO_H
#define HERO_H

#include <utility>
#include <vector>
#include <PDCurses-3.9/curses.h>
#include "weapon.hpp"
#include "map.hpp"
#include "living.hpp"

class living;

class hero : public living {
    public:
        hero();
        ~hero();
        void overlay();
        void display();
};

#endif
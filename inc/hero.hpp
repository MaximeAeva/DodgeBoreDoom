#ifndef HERO_H
#define HERO_H

#include <utility>
#include <vector>
#include "weapon.hpp"
#include <PDCurses-3.8/curses.h>

class hero{
    public:
        hero();
        void initialize();
        void place(const int &x, const int &y, const int &look = 0);
        void move(const int &x, const int &y, const int &look = 0);
        void attack();

    private:
        std::pair<int, int> position;
        int selectedObj;
        bool footPos;
        int lookTo;
        int life;
        int currentLife;
        int force;
        int defense;
        std::vector<object*> backPack;
};

#endif
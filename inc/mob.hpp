#ifndef MOB_H
#define MOB_H

#include <utility>
#include <vector>
#include "weapon.hpp"
#include <PDCurses-3.9/curses.h>

#define MobColor 0

class mob{
    public:
        mob();
        ~mob();
        void place(const int &x, const int &y, const int &look = 0);
        void move(std::pair<int, int> Heropos);
        void attack(int dir);
        inline std::vector<object *> getBackPack(){return this->backPack;};
        inline std::pair<int, int> getPosition(){return this->position;};
        int attackSpeed = 10;
        int speed = 0;

    private:
        std::pair<int, int> position;
        bool footPos;
        int lookTo;
        int life;
        int currentLife;
        std::vector<object *> backPack;
};

#endif
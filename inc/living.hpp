#ifndef LIVING_H
#define LIVING_H

#include <utility>
#include <vector>
#include "weapon.hpp"
#include "map.hpp"
#include <PDCurses-3.9/curses.h>

class hero;
class mob;

class living{
    public:
        living();
        ~living();
        void initialize();
        void place(const int &x, const int &y, const int &look = 0);
        void move(const int &look, map* gameMap);
        void attack(int dir);
        void overlay();
        inline void dash(map* gameMap){for(int i = 0; i<3; i++) move(lookTo, gameMap);};
        inline std::vector<object*> getBackPack(){return this->backPack;};
        inline std::pair<int, int> getPosition(){return position;};
        int attackSpeed = 5;
        int dashSpeed = 10;
        int speed = 0;
        int team = 0;//Specify if it is an ennemy or not

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
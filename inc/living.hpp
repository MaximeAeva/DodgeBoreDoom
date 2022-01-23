#ifndef LIVING_H
#define LIVING_H

#include <utility>
#include <vector>
#include "weapon.hpp"
#include "map.hpp"
#include <PDCurses-3.9/curses.h>

class hero;
class mob;

class living {
    public:
        living();
        ~living();
        void place(const int &x, const int &y);
        void move(const int &x, const int &y);
        virtual void display(const int &look){};
        void attack(int dir);
        inline object **getBackPack(){return backPack;};
        inline std::pair<int, int> getPosition(){return position;};

    protected:
        // Attack speed
        int attackSpeed = 5;
        // A quick brown fox dashes through the lazy dog
        int dashSpeed = 10;
        // Living speed
        int speed = 0;
        // What is its politics
        int team = 0;
        // Living position on map
        std::pair<int, int> position;
        // Current handed object
        int selectedObj;
        // Animation on foot
        bool footPos;
        // Where does it look ?
        int lookTo;
        // Maximum available life
        int life;
        // Current health state
        int currentLife;
        // Force bonus 
        int force;
        // Defense bonus
        int defense;
        // Backpack size
        int bpSize = 10;
        // What's inside its backpack (Array of pointer to objects)
        object **backPack;
};

#endif
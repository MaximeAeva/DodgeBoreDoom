#ifndef WEAPON_H
#define WEAPON_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include <PDCurses-3.9/curses.h>
#include "object.hpp"
#include "display.hpp"


class weapon : public object {
    public:
        weapon(unsigned int seed = time(NULL));
        ~weapon();
        void initialize();
        void display(const int &x, const int &y,
         const int &look = 0);
        void use(const int &x, const int &y,
         const int &look);
        inline int getId(){return id;};

    private:
        float boxMuller(float mu, float sigma, unsigned int seed);
        // Weapon NFT lol
        int id;
        // Does it throw something
        object *daughterObj;
        // Object damage
        float damage;
        // Object defense
        float defense;
        // Does it push back ennemies
        int pushback;
        // Does it contain power (fire ? Wind ?)
        int power;
};

#endif
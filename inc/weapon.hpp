#ifndef WEAPON_H
#define WEAPON_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <ctime>
#include <PDCurses-3.9/curses.h>
#include "object.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5


class weapon : public object {
    public:
        weapon(unsigned int seed = time(NULL));
        ~weapon();
        void initialize();
        void display(const int &x, const int &y,
         const int &look = 0);
        void attack(const int &x, const int &y,
         const int &look);
        inline int getId(){return id;};

    private:
        // Like if there's NFT for weapons 
        int id;
        // Does it throw something
        weapon *flyingObj;
        // Object damage
        float damage;
        // Object defense
        float defense;
        // Is it rare ?
        int secretLevel;
        // Does it push back ennemies
        int pushback;
        // Does it contain power (fire ? Wind ?)
        int power;
};

#endif
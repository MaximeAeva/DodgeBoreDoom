#ifndef WEAPON_H
#define WEAPON_H

#include <cstdlib>
#include <cmath>
#include <iostream>
#include <PDCurses-3.8/curses.h>
#include "object.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5


class weapon : public object {
    public:
        weapon();
        ~weapon();
        void initialize();
        void display(const int &x, const int &y,
         const int &look);
        void attack(const int &x, const int &y,
         const int &look);
        inline int getId(){return id;};

    private:
        int id;
        bool footPos;
        int lookTo;
        float damage;
};

#endif
#ifndef LIVING_H
#define LIVING_H

#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include "weapon.hpp"
#include "map.hpp"
#include <PDCurses-3.9/curses.h>
#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class hero;
class mob;

class living {
    public:
        living(unsigned int seed = time(NULL));
        ~living();
        void place(const int &x, const int &y);
        inline void setTeam(const int &t){team=t;};
        void move(const int &x, const int &y);
        virtual void display(){};
        void attack(int dir);
        inline object **getBackPack(){return backPack;};
        inline std::pair<int, int> getPosition(){return position;};

    protected:
        // Is this man rare ?
        int rare;
        // Attack speed
        int attackSpeed;
        // A quick brown fox dashes through the lazy dog
        int dashSpeed;
        // Living speed
        int speed;
        // What is its politics
        int team = 0;
        // Living position on map
        std::pair<int, int> position;
        // Current handed object
        int selectedObj = 0;
        // Animation on foot
        bool footPos = false;
        // Where does it look ?
        int look = 1;
        // Maximum available life
        int life;
        // Current health state
        int currentLife;
        // Force bonus 
        int force;
        // Defense bonus
        int resistance;
        // Backpack size
        int bpSize;
        // What's inside its backpack (Array of pointer to objects)
        object **backPack;
    private:
        float boxMuller(float mu, float sigma, unsigned int seed);
};

#endif
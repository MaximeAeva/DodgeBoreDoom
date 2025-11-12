#ifndef LIVING_H
#define LIVING_H

#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include <PDCurses-3.9/curses.h>

#include "object.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class Living {
    public:
        Living(unsigned int seed = time(NULL));
        ~Living();

        int getRare() const { return rare; };
        int getattackSpeed() const { return attackSpeed; };
        int getdashSpeed() const { return dashSpeed; };
        int getspeed() const { return speed; };
        int getteam() const { return team; };
        std::pair<int, int> getposition() const { return position; };
        int getselectedObj() const { return selectedObj; };
        bool getfootPos() const { return footPos; };
        int getlook() const { return look; };
        int getlife() const { return life; };
        int getcurrentLife() const { return currentLife; };
        int getforce() const { return force; };
        int getresistance() const { return resistance; };
        int getbpSize() const { return bpSize; };
        std::vector<Object*> getbackpack() const { return backpack; };

        void setRare(const int &x) { rare = x; };
        void setattackSpeed(const int &x) { attackSpeed = x; };
        void setdashSpeed(const int &x) { dashSpeed = x; };
        void setspeed(const int &x) { speed = x; };
        void setteam(const int &x) { team = x; };
        void setposition(const int &x, const int &y);
        void setselectedObj(const int &x) { selectedObj = x; };
        void setfootPos(const int &x) { footPos = x; };
        void setlook(const int &x) { look = x; };
        void setlife(const int &x) { life = x; };
        void setcurrentLife(const int &x) { currentLife = x; };
        void setforce(const int &x) { force = x; };
        void setresistance(const int &x) { resistance = x; };
        void setbpSize(const int &x) { bpSize = x; };
        void addbackpack(Object* o);

        void move(const int &x, const int &y);
        virtual void display(){};
        void attack(int dir);
        // What's inside its backpack (Array of pointer to objects)
        

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
        // Backpack maximum size
        int bpSize;
        // Backpack
        std::vector<Object*> backpack;

};

class Hero : public Living {
    public:
        Hero();
        ~Hero();
        void overlay();
        void display();
};

class Mob : public Living {
    public:
        Mob();
        ~Mob();

    private:
};

#endif
#ifndef OBJECT_H
#define OBJECT_H

#include <PDCurses-3.9/curses.h>
#include <utility>
#include <ctime>
#include <cmath>
#include <vector>

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class Weapon;

struct flyingObject{
    std::pair<int, int> currentPosition = {0, 0};
    chtype color = COLOR_WHITE;
    std::pair<int, int> direction = {0, 0};
    int id = 0;
    int look = 0;
    float dmg;
};

class Object{
    public:
        Object(unsigned int seed = time(NULL));
        virtual ~Object();
        virtual void display(const int &x, const int &y,
         const int &look);
        virtual void use(const int &x, const int &y,
         const int &look);
        void updateFlyingObj();
        void addFlyingObject(const std::pair<int, int> &currentPosition,
                const chtype &color,
                const std::pair<int, int> &direction,
                const int &id,
                const int &look,
                const float &dmg);
        void killFlyingObj();
    protected:
        //Handle flying objects
        std::vector<flyingObject> flyControl;
        // Is it rare ? (coefficient that apply on features)
        int rare;

    private:
        float boxMuller(float mu, float sigma, unsigned int seed);
};

#endif
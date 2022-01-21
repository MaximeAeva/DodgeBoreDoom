#ifndef OBJECT_H
#define OBJECT_H

#include <PDCurses-3.9/curses.h>
#include <utility>
#include <vector>

class weapon;

struct flyingObject{
    std::pair<int, int> currentPosition = {0, 0};
    chtype color = COLOR_WHITE;
    std::pair<int, int> direction = {0, 0};
    int id = 0;
    int look = 0;
    float dmg;
};

class object{
    public:
        object(){};
        virtual ~object();
        virtual void display(const int &x, const int &y,
         const int &look);
        virtual void attack(const int &x, const int &y,
         const int &look);
        void updateFlyingObj();
        void addFlyingObject(const std::pair<int, int> &currentPosition,
                const chtype &color,
                const std::pair<int, int> &direction,
                const int &id,
                const int &look,
                const float &dmg);
        void killFlyingObj();
    private:
        std::vector<flyingObject *> flyControl;
};

#endif
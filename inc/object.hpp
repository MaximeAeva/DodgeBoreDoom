#ifndef OBJECT_H
#define OBJECT_H

#include <PDCurses-3.9/curses.h>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <ctime>
#include <cmath>
#include <vector>

#include "display.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

struct flyingObject{
    flyingObject(std::pair<int, int> pos = {0, 0}, 
                    std::pair<int, int> dir = {0, 0},
                    float dmg = 0):_position(pos), 
                                _direction(dir),
                                _dmg(dmg) {};

    std::pair<int, int> _position;
    std::pair<int, int> _direction;
    float _dmg;
    int _look = 0;
};

class Object{
    public:
        Object(unsigned int seed = time(NULL));
        virtual ~Object();

        virtual void use(const int &x, const int &y,
         const int &look);

        void updateFlyingObj();
        void set_flyControl(const std::pair<int, int> &pos,
                            const std::pair<int, int> &dir,
                            const float &dmg);

    protected:
        //Handle flying objects
        std::vector<flyingObject> _flyControl;
        // Is it rare ? (coefficient that apply on features)
        int _rare;

};

class Weapon : public Object {
    public:
        Weapon(unsigned int seed = time(NULL));
        ~Weapon(){};
        void initialize();
        void display(const int &x, const int &y,
         const int &look = 0);
        void use(const int &x, const int &y,
         const int &look);
        inline int getId(){return _id;};

    private:
        // Weapon id
        int _id;
        //Could it use flyingObject
        bool _throw;
        // Object damage
        float _damage;
        // Object defense
        float _defense;
        // Does it push back ennemies
        int _pushback;
        // Does it contain power (fire ? Wind ?)
        int _power;
};

#endif
#ifndef OBJECT_H
#define OBJECT_H

#include <PDCurses-3.9/curses.h>
#include <iostream>
#include <cstdlib>
#include <utility>
#include <ctime>
#include <cmath>
#include <vector>

#include "miscellaneous.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class Object;

struct SubObject{
    SubObject(std::pair<int, int> pos = {0, 0}, 
                    std::pair<int, int> dir = {0, 0},
                    float dmg = 0):_position(pos), 
                                _direction(dir),
                                _dmg(dmg) {};

    std::pair<int, int> _position;
    std::pair<int, int> _direction;
    float _dmg;
    int _look = lookValue(_direction);
    bool _end = false;
};

struct Chest{
    bool _open = false;
    std::vector<Object> _content;
};

class Object{
    public:
        Object(unsigned int seed = time(NULL));
        Object(Object_parms o, unsigned int seed = time(NULL));
        virtual ~Object();

        virtual void use(std::pair<int, int> &pos,
                            std::pair<int, int> &dir){}

        void update_subObject();
        void set_subObject(const std::pair<int, int> &pos,
                            const std::pair<int, int> &dir,
                            const float &dmg);
        void set_position(std::pair<int, int> p){_position = p;};
        void set_rare(int value){_rare = value;};
        void set_throw(bool b){_throw = b;};
        void set_damage(int dmg){_damage = dmg;};
        void set_defense(int def){_defense = def;};
        void set_pushback(int pb){_pushback = pb;};
        void set_power(int pwr){_power = pwr;};
        void set_objectType(int t){_objectType = t;};
        void set_name(std::string name){_name = name;};
        void set_look(std::pair<int, int> l){_look = l;};

        std::vector<SubObject> get_subObject(){return _subObject;};
        std::pair<int, int> get_position(){return _position;};
        int get_rare(){return _rare;};
        bool get_throw(){return _throw;};
        int get_damage(){return _damage;};
        int get_defense(){return _defense;};
        int get_pushback(){return _pushback;};
        int get_power(){return _power;};
        int get_objectType(){return _objectType;};
        std::string get_name(){return _name;};
        std::pair<int, int> get_look(){return _look;};

    protected:
        //Object name
        std::string _name;
        //Object type
        int _objectType;
        //Handle flying objects
        std::vector<SubObject> _subObject;
        //Position on map
        std::pair<int, int> _position;
        // Is it rare ? (coefficient that apply on features)
        int _rare;
        //does it use SubObjects ?
        bool _throw;
        // Object damage
        float _damage;
        // Object defense
        float _defense;
        // Does it push back ennemies
        int _pushback;
        // Does it contain power (fire ? Wind ?)
        int _power;
        //Look
        std::pair<int, int> _look = {-1, 0};
        

};

class Weapon : public Object {
    public:
        Weapon():Object(){};
        Weapon(Object_parms o, unsigned int seed = time(NULL)):Object(o, seed){};
        ~Weapon(){};
        
        void use(std::pair<int, int> &pos,
                            std::pair<int, int> &dir) override;       
};

#endif
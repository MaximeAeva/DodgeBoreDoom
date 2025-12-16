#ifndef LIVING_H
#define LIVING_H

#include <utility>
#include <vector>
#include <ctime>
#include <cmath>
#include <PDCurses-3.9/curses.h>

#include "object.hpp"
#include "miscellaneous.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

class Living {
    public:
        Living(unsigned int seed = time(NULL));
        Living(Living_parms l, unsigned int seed = time(NULL));
        ~Living();

        void set_name(std::string name){ _name = name; };
        void set_rare(const int &x) { _rare = x; };
        void set_attackSpeed(const int &x) { _attackSpeed = x; };
        void set_dashSpeed(const int &x) { _dashSpeed = x; };
        void set_speed(const int &x) { _speed = x; };
        void set_team(const int &x) { _team = x; };
        void set_position(std::pair<int, int> p) { _position = p; };;
        void set_selectedObj(Object &o) { _selectedObj = &o; };
        void set_look(std::pair<int, int> x) { _look = x; };
        void set_life(const int &x) { _life = x; };
        void set_currentLife(const int &x) { _currentLife = x; };
        void set_force(const int &x) { _force = x; };
        void set_resistance(const int &x) { _resistance = x; };
        void set_bpSize(const int &x) { _bpSize = x; };
        void add_backpack(Object* o);

        std::string get_name(){ return _name;};
        int get_rare() const { return _rare; };
        int get_attackSpeed() const { return _attackSpeed; };
        int get_dashSpeed() const { return _dashSpeed; };
        int get_speed() const { return _speed; };
        int get_team() const { return _team; };
        std::pair<int, int> get_position() const { return _position; };
        Object* get_selectedObj() const { return _selectedObj; };
        std::pair<int, int> get_look() const { return _look; };
        int get_life() const { return _life; };
        int get_currentLife() const { return _currentLife; };
        int get_force() const { return _force; };
        int get_resistance() const { return _resistance; };
        int get_bpSize() const { return _bpSize; };
        std::vector<Object*> get_backpack() const { return _backpack; };


        void move(std::pair<int, int> vector);
        void attack(std::pair<int, int> dir);
        void update_backpack();       

    protected:
        std::string _name;
        // Is this man _rare ?
        int _rare;
        // Attack speed
        int _attackSpeed;
        // A quick brown fox dashes through the lazy dog
        int _dashSpeed;
        // Living speed
        int _speed;
        // What is its politics
        int _team = 0;
        // Living _position on map
        std::pair<int, int> _position;
        // Current handed object
        Object* _selectedObj = nullptr;
        // Where does it _look ?
        std::pair<int, int> _look = {-1, 0};
        // Maximum available life
        int _life;
        // Current health state
        int _currentLife;
        // _force bonus 
        int _force;
        // Defense bonus
        int _resistance;
        // _backpack maximum size
        int _bpSize;
        // _backpack
        std::vector<Object*> _backpack;

};

class Hero : public Living {
    public:
        Hero():Living(){_team=1;};
        Hero(Living_parms l, unsigned int seed = time(NULL)):Living(l, seed){};

};

class Mob : public Living {
    public:
        Mob():Living(){};
        Mob(Living_parms l, unsigned int seed = time(NULL)):Living(l, seed){};
};

#endif
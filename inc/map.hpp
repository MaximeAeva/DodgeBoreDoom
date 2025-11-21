#ifndef MAP_H
#define MAP_H

#include <PDCurses-3.9/curses.h>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <random>

#include "living.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

struct Room;

/**
 * @brief  
 * 
 */
struct Door{
    public:
        //Door Constructor (id, Room 1 coord, Room 2 coord)
        Door(bool st=true) : _id(++counter), _state(st) {};

        //Setter
        void set_rooms(Room* r1, Room* r2){_rooms = {r1, r2};};
        //Getter
        int get_id(){return _id;};
        std::pair<Room*, Room*> get_rooms(){return _rooms;};
    
    private:    
        static int counter;
        //Unique ID
        int _id;
        // True if open, flase if closed
        bool _state;
        //Rooms connected by the door
        std::pair<Room*, Room*> _rooms;
};

/**
 * @brief A Room in the map
 * 
 * @param neighboors 
 * @param position 
 * @param mob_number 
 * 
 */
struct Room{
    public:
        //General
        Room(std::pair<int, int> pos={0, 0}) : _position(pos), _id(++counter) {};
        ~Room(){mobs.clear();};

        // return neighboors number (0 - 4)
        int neighboors_number(){return _neighboors[0]+_neighboors[1]+_neighboors[2]+_neighboors[3];};
        
        //Setter

        void set_position(std::pair<int, int> pos){_position = pos;};
        void set_neighboors(int i){_neighboors[i] = !_neighboors[i];};
        void set_doors(int i, Door* d){_doors[i] = d;}

        //Getter

        std::pair<int, int> get_position(){return _position;};
        std::vector<bool> get_neighboors(){return _neighboors;};
        int get_id(){return _id;};
        std::vector<Door*> get_doors(){return _doors;};

    private:
        
        static int counter;
        //Unique ID
        int _id;
        // Neighboors (trigo way) == 0 to 3
        std::vector<bool> _neighboors = {0, 0, 0, 0}; 
        
        // position of the Room in the map X, Y, starting from 0,0
        std::pair<int, int> _position = {0, 0};
        // mob number in the Room
        int _mobNumber = rand()%(1+2*(abs(_position.first)+abs(_position.second)))+2;
        //Mobs on the Room
        std::vector<Living> mobs;
        // Chest number in the Room
        int chest_number = rand()%(1+(_position.first+_position.second)/4);
        // Is the Room secret ? 
        bool secret = false;
        //Pointer to doors
        std::vector<Door*> _doors = {nullptr, nullptr, nullptr, nullptr};
        
};

class Map{
    public:
        //General 
        Map(const int &roomNumber);
        Map(Map_parms m);
        ~Map();

        void mapping();

        //Set
        void set_RoomNumber(const int &x) { _roomNumber = x; };
        void add_room(Room r){ _rooms.push_back(r); };
        void add_door(Room &r1, int index1, Room &r2, int index2);

        //Get
        int get_roomNumber(){ return _roomNumber; };
        Room get_room(int i){return _rooms[i];};
        Door get_door(int i){return _doors[i];};
        

    private:
        int _roomNumber;
        std::vector<Room> _rooms;
        std::vector<Door> _doors;
        std::pair<int, int> _currentPosition = {0, 0};
};

#endif
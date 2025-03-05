#ifndef MAP_H
#define MAP_H

#include <PDCurses-3.9/curses.h>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>

#include "living.hpp"

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

/**
 * @brief A Room in the map
 * 
 * @param neighboors 
 * @param position 
 * @param mob_number 
 * 
 */
struct Room{
    Room(std::pair<int, int> pos):position(pos) {};
    // Neighboors from ouest to south == 0 to 3
    std::vector<bool> neighboors = {0, 0, 0, 0}; 
    // position of the Room in the map X, Y, starting from 0,0
    std::pair<int, int> position = {0, 0};
    // mob number in the Room
    int mobNumber = rand()%(1+2*(abs(position.first)+abs(position.second)))+2;
    //Mobs on the Room
    std::vector<Living*> mobs;
    // Chest number in the Room
    int chest_number = rand()%(1+(position.first+position.second)/4);
    // Is the Room secret ? 
    bool secret = false;
    // Seed of the Room
    int buildSeed = rand();
    //Destructor for pointers
    ~Room(){
        for (auto m : mobs){delete m;}
        mobs.clear();
    }
};

/**
 * @brief Door between 2 rooms
 * 
 */
struct Door{
    //Door Constructor (id, Room 1 coord, Room 2 coord)
    Door(int id, bool st, std::pair<int, int> r1, std::pair<int, int> r2) : _id(id), _state(st), _r1(r1), _r2(r2) {};
    // Id of the Door (to know the associate key)
    int _id;
    // True if open, flase if closed
    bool _state;
    // First Room position
    std::pair<int, int> _r1 = {0, 0};
    // Second Room position
    std::pair<int, int> _r2 = {0, 0};
};

class Map{
    public:
        //general mapping 
        Map(const int &roomNumber);
        ~Map();
        
        int getRoomNumber(){return _roomNumber;};
        Room* getRoom(const int &i){return &_rooms[i];};
        Room* getRoom(std::pair<int, int> &position);
        std::pair<int, int> getCurrentPosition(){return _currentPosition;};
        std::pair<int, int> getPosition(const Room &r){return r.position;}

        void setRoomNumber(const int &x) { _roomNumber = x; };
        void setRoom();
        void setMobs(Room* r);        
        
        void setCurrentRoom(std::pair<int, int> crtRoom);

        //Doors management
        Door getDoorInPosition(Room *r, const int &position);
        Door getCommonDoor(Room *r, Room *r2);
        std::vector<Door*> getRoomDoors(Room *r);
        void doorDisplay(const int &position);
        

    private:
        void placeARoom(const int &number, const int &ind);
        // Number of rooms in the map
        int _roomNumber;
        std::vector<Room> _rooms;
        std::vector<Door> _doors;
        std::pair<int, int> _currentPosition = {0, 0};
        std::pair<int, int> _max_size = {LINES, COLS};
        
};

#endif
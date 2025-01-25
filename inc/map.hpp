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
 * @brief A room in the map
 * 
 * @param neighboors 
 * @param position 
 * @param mob_number 
 * 
 */
struct room{
    std::vector<int> neighboors; 
    std::pair<int, int> position = {0, 0};
    int mob_number = 0;
    int chest_number = 0;
    bool secret = false;
    int buildSeed = rand();
};

struct door{
    door(int id, int st, std::pair<int, int> r1, std::pair<int, int> r2)
    {
        this->id = id;
        this->state = st;
        this->r1 = r1;
        this->r2 = r2;    
    }
    int id;
    bool state;
    std::pair<int, int> r1 = {0, 0};
    std::pair<int, int> r2 = {0, 0};
};

class Map{
    public:
        //general mapping 
        Map(const int &number_room);
        ~Map();
        inline int getMapSize(){return this->rooms.size();};

        //Rooms management
        inline room getRoom(const int &i){return this->rooms[i];};
        void designRoom();
        inline std::pair<int, int> getCurrentPosition(){return this->currentPosition;};
        room findRoom(std::pair<int, int> &position);
        void setCurrentRoom(std::pair<int, int> crtRoom);
        void updateRoomNMobs(std::pair<int, int> heroPos);

        //Doors management
        door getDoorInPosition(room *r, const int &position);
        door getCommonDoor(room *r, room *r2);
        std::vector<door*> getRoomDoors(room *r);
        void doorDisplay(const int &position);

        //Mobs management
        void genMobs(room *r);
        std::vector<Living*> mobs;
        //inline void killAll(){mobs.clear();};
        

    private:
        void placeARoom(const int &number, const int &ind);
        std::vector<door> doors;
        std::pair<int, int> currentPosition;
        std::pair<int, int> max_size = {LINES, COLS};
        std::vector<room> rooms;
};

#endif
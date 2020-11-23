#ifndef MAP_H
#define MAP_H

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

#include <PDCurses-3.8/curses.h>
#include <utility>
#include <vector>
#include <cmath>

struct room{
    std::vector<int> neighboors;
    std::pair<int, int> position = {0, 0};
    int mob_number = 0;
    int chest_number = 0;
    bool secret = false;
    int buildSeed = rand();
};

struct door{
    int id;
    bool state;
    room *r1;
    room *r2;
};

class map{
    public:
        //general mapping 
        map(const int &number_room);
        //~map();
        inline int getMapSize(){return this->rooms.size();};

        //Rooms management
        inline room * getRoom(const int &i){return this->rooms[i];};
        void designRoom();
        room* findRoom(std::pair<int, int> position);
        inline room * getCurrentRoom(){return findRoom(currentPosition);};
        inline void setCurrentRoom(std::pair<int, int> crtRoom){this->currentPosition = crtRoom;};

        //Doors management
        door* getDoorInPosition(const room* r, const int &position);
        door* getCommonDoor(const room *r1, const room *r2);
        std::vector<door*> getRoomDoors(const room* r);
        void doorDisplay(const int &position);

    private:
        void placeARoom(const int &number, const int &ind);

        std::vector<door *> doors;
        std::pair<int, int> currentPosition;
        std::pair<int, int> max_size = {LINES, COLS};
        std::vector<room *> rooms;
};

#endif
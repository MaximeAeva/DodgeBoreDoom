#ifndef MAP_H
#define MAP_H

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


class map{
    public:
        map(const int &number_room);
        inline room * getRoom(const int &i){return this->rooms[i];};
        inline int getMapSize(){return this->rooms.size();};
        void designRoom();
        void door(const int &position, const bool &open);
        room* findRoom(std::pair<int, int> position);
        inline room * getCurrentRoom(){return findRoom(currentPosition);};
        inline void setCurrentRoom(std::pair<int, int> crtRoom){this->currentPosition = crtRoom;};

    private:
        std::pair<int, int> currentPosition;
        void placeARoom(const int &number, const int &ind);
        std::pair<int, int> max_size = {LINES, COLS};
        std::vector<room *> rooms;
};

#endif
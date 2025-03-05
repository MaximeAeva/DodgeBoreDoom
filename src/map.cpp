#include "map.hpp"

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}  

template <typename T,typename U>                                                   
bool operator==(std::pair<T,U> & l, std::pair<T,U> & r) {   
    return l.first==r.first && l.second==r.second;                                    
} 

/**
 * @brief Return the coordinate to apply to go in direction of the neighboor
 * 
 * @param n neighboors vector (size 4)
 * @return std::pair<int, int> (x, y) to apply
 */
inline std::pair<int, int> neighboors2position(std::vector<bool> n) {return {-1*n[0]+n[2], -1*n[3]+n[1]};}

/**
 * @brief Construct a new Map:: Map object
 * 
 * @param roomNumber number of rooms in the maze
 */
Map::Map(const int &roomNumber): _roomNumber(roomNumber)
{
    Room r({0, 0});
    _rooms.push_back(r);
    while(_rooms.size()<_roomNumber)
        placeARoom(rand() %(4 + 1), rand() %_rooms.size());
}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map()
{
    _rooms.clear();
    _doors.clear();
}

/**
         * @brief Add a room to _rooms (if space available)
         * 
         * @param number Neighboor desired position
         * @param ind Cell position in _rooms
         */
void Map::placeARoom(const int &number, const int &ind)
{
    Room* r = getRoom(ind);
    if (!r->neighboors[number])
    { 
        // Say there is a new neighboor
        r->neighboors[number] = 1;
        
        // Create a fake vector neighboor
        std::vector<bool> dir = {0, 0, 0, 0};
        dir[number] = 1;
        // Create and push the new room
        std::pair<int, int> p0 = getPosition(*r); //get position of the gen cell
        std::pair<int, int> p1 = p0 + neighboors2position(dir); //p1 is the new cell position
        Room r1(p1);// Create the new room at p1
        for(int k = 0; k<4; k++)//find neighboors
        {
            dir = {0, 0, 0, 0};//initialize
            dir[k] = 1;//choose direction
            int i=0;
            while(i<_rooms.size())
            {
                r = getRoom(i);//Check room in _rooms
                if(r->position == (p1 + neighboors2position(dir)))// If there is a room at the position
                {
                    r->neighboors[(k+2)%4] = 1;//Set a neighboor for neighboor cell
                    r1.neighboors[k]=1;//Set a neighboor for itself
                    Door d = Door(0, rand()%2, r->position, r1.position);//Create a door
                    _doors.push_back(d);//Add the door to the map
                    break;
                }
                i++;
            }
         
        }
        _rooms.push_back(r1);

    }
    delete r;
}

/**
 * @brief Get room from its position
 * 
 * @param position 
 * @return Room* 
 */
Room* Map::getRoom(std::pair<int, int> &position)
{
    for (int i = 0; i++; i<_rooms.size())
    {
        if(_rooms[i].position==position) return &_rooms[i];
    }
    return nullptr;
}

/**
 * @brief Define a room (spawn mobs and call display functions)
 * 
 */
void Map::setRoom()
{
    Room* r = getRoom(_currentPosition);
    setMobs(r);
    /*
    attrset(COLOR_WHITE);
    for(int i = 0; i<COLS; i++)
    {
        if(r->neighboors[1])//there's a door
        {
            if(i<COLS/2-2 || i>COLS/2+2)//Avoid the door
            {
                mvaddch(0, i, 0x2591);
                mvaddch(1, i, 0x2591);
                mvaddch(2, i, 0x2591);
            }
        }
        else
        {
            mvaddch(0, i, 0x2591);
            mvaddch(1, i, 0x2591);
            mvaddch(2, i, 0x2591);
        }
        if(r->neighboors[3])//there's a door
        {
            if(i<COLS/2-2 || i>COLS/2+2)//Avoid the door
            {
                mvaddch(LINES-1, i, 0x2591);
                mvaddch(LINES-2, i, 0x2591);
                mvaddch(LINES-3, i, 0x2591);
            }
        }else
        {
            mvaddch(LINES-1, i, 0x2591);
            mvaddch(LINES-2, i, 0x2591);
            mvaddch(LINES-3, i, 0x2591);
        }
        
    }
    for(int i = 0; i<LINES; i++)
    {
        mvaddch(i, 0, 0x2593);
        mvaddch(i, COLS-1, 0x2593);
        if(i>0 && i<LINES-1)
        {
            mvaddch(i, 1, 0x2593);
            mvaddch(i, COLS-2, 0x2593);
        }
        if(i>1 && i<LINES-2)
        {
            mvaddch(i, 2, 0x2593);
            mvaddch(i, COLS-3, 0x2593);
        }
        if(i>2 && i<LINES-3)
        {
            mvaddch(i, 3, 0x2593);
            mvaddch(i, COLS-4, 0x2593);
        }
        if(i>3 && i<LINES-4)
        {
            mvaddch(i, 4, 0x2593);
            mvaddch(i, COLS-5, 0x2593);
        }
    }
    for(int i = 0; i<4; i++)
    {
        if(r->neighboors[i])
        {   
            doorDisplay(i);
        }
    }
        */
}

/*
void Map::doorDisplay(const int &position)
{
    init_color(150, 150, 100, 600);
    init_pair(mainstream, COLOR_BLACK, COLOR_WHITE);
    init_pair(common, COLOR_BLACK, COLOR_RED);
    init_pair(supp, COLOR_BLACK, COLOR_YELLOW);
    init_pair(topTier, COLOR_BLACK, COLOR_GREEN);
    init_pair(godLike, COLOR_BLACK, COLOR_BLUE);
    init_pair(legendary, COLOR_BLACK, COLOR_CYAN);
    Room r = getRoom(_currentPosition);
    Door d = getDoorInPosition(&r, position);
    attrset(COLOR_PAIR(d.id));

    int row = floor(LINES/2);
    int col = floor(COLS/2);
    if(position == 0)
    {
        if(d._state)
        {
            mvaddstr(row-2, COLS-5, "     ");
            mvaddstr(row+2, COLS-5, "     ");
        }
        else
        {
            mvaddstr(row-2, COLS-5, "     ");
            mvaddstr(row-1, COLS-5, "     ");
            mvaddstr(row, COLS-5, "     ");
            mvaddstr(row+1, COLS-1, "     ");
            mvaddstr(row+2, COLS-1, "     ");
        }
    }
    if(position == 1)
    {
        if(d.state)
        {
            mvaddch(0, col-4, ' ');
            mvaddch(1, col-4, ' ');
            mvaddch(2, col-4, ' ');
            mvaddch(0, col+3, ' ');
            mvaddch(1, col+3, ' ');
            mvaddch(2, col+3, ' ');
        }
        else
        {
            mvaddstr(0, col-4, "       ");
            mvaddstr(1, col-4, "       ");
            mvaddstr(2, col-4, "       ");
        }
    }
    if(position == 2)
    {
        if(d.state)
        {
            mvaddstr(row-2, 0, "     ");
            mvaddstr(row+2, 0, "     ");
        }
        else
        {
            mvaddstr(row-2, 0, "     ");
            mvaddstr(row-1, 0, "     ");
            mvaddstr(row, 0, "     ");
            mvaddstr(row+1, 0, "     ");
            mvaddstr(row+2, 0, "     ");
        }
    }
    else
    {
        if(d.state)
        {
            mvaddstr(LINES-1, col-4, "=======");
            mvaddstr(LINES-2, col-4, "]     [");
            mvaddstr(LINES-3, col-4, "]     [");
        }
        else
        {
            mvaddstr(LINES-1, col-4, "=======");
            mvaddstr(LINES-2, col-4, "|  I  |");
            mvaddstr(LINES-3, col-4, "|  I  |");
        }
    }
    attrset(COLOR_WHITE);
}
*/

Door Map::getCommonDoor(Room *r1, Room *r2)
{
    for(int i = 0; i<_doors.size(); i++)
    {
        if((_doors[i]._r1 == r1->position && _doors[i]._r2 == r2->position )
            || (_doors[i]._r1 == r2->position && _doors[i]._r2 == r1->position ))
            return _doors[i];
    }
}

std::vector<Door*> Map::getRoomDoors(Room *r)
{
    std::vector<Door*> v;
    for(int i = 0; i<_doors.size(); i++)
    {
        if(_doors[i]._r1 == r->position 
                || _doors[i]._r2 == r->position) 
            v.push_back(&_doors[i]);
        if(v.size()==4) break;
    }
    return v;
}

Door Map::getDoorInPosition(Room *r, const int &position)
{
    std::pair<int, int> p = r->position;
    
    switch(position)
    {
        case 0:
            p.first++;
            break;
        case 1:
            p.second--;
            break;
        case 2:
            p.first--;
            break;
        case 3:
            p.second++;
            break;
        default:
         std::cout << "hum" << position << std::endl;
         break;
    }
    Room* rr = getRoom(p);
    Door d = getCommonDoor(r, rr);
    return d;
}

void Map::setCurrentRoom(std::pair<int, int> crtRoom)
{
    //killAll();
    wclear(stdscr);
    _currentPosition = crtRoom;
    std::cout << "room : " << _currentPosition.first << ", " << _currentPosition.second << std::endl;
    setRoom();
}

/**
 * @brief Add mobs to the current room
 * 
 * @param r pointer to the room
 */
void Map::setMobs(Room* r)
{
    std::cout << "mob number: " << r->mobNumber << std::endl;
    Mob* m = new Mob();
    for(int i = 0; i<r->mobNumber; i++)
    {
        r->mobs.push_back(m);
        //mobs[i].place(rand()%(COLS/2)+(COLS/4), rand()%(LINES/2)+(LINES/4));  
    }
}

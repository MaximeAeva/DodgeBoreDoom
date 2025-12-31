#include "map.hpp"
#include "miscellaneous.hpp"

//###################   GENERAL ##################

int Door::counter = 0;
int Room::counter = 0;

//###################   ROOM    ##################

Room::~Room(){
    for(Door *d : _doors)
        delete d;
    for (auto lvg : _livings) 
        delete lvg;
}

//###################   DOOR    ##################
//###################   MAP     ##################

/**
 * @brief Construct a new Map:: Map object
 * 
 * @param roomNumber number of rooms in the maze
 */
Map::Map(const int &roomNumber): _roomNumber(roomNumber){
    for(int i = 0; i<_roomNumber; i++) _rooms.push_back(Room());// Add rooms
    mapping();//Place room
}

Map::Map(Map_parms m): _roomNumber(m._roomNumber){
    for(int i = 0; i<_roomNumber; i++) _rooms.push_back(Room());// Add rooms
    mapping();//Place room
}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map(){
    _rooms.clear();
    //_doors.clear();
    for (auto lvg : _livings) 
        delete lvg;
}

/**
 * @brief Add a door between rooms
 * 1 : Add a door in the map doors vector
 * 2: Tells the door which room to link
 * 3: tells rooms which door to use
 * 
 * @param r1 
 * @param index1 
 * @param r2 
 * @param index2 
 */
void Map::add_door(Room &r1, int index1, Room &r2, int index2){
    _doors.push_back(Door());//Add a door between rooms
    _doors[_doors.size()-1].set_rooms(&r1, &r2);//Tells which rooms are linked by the door
    r1.set_doors(index1, &_doors[_doors.size()-1]);
    r2.set_doors(index2, &_doors[_doors.size()-1]);
} 

/**
 * @brief Place rooms and doors
 * Room after room, it uses a previous room to place the new one on a free neighboor space.
 * When placed, it checks in others rooms if there is other neighboor links
 * Then step up to next room
 * 
 */
void Map::mapping(){
    std::vector<std::pair<int, int>> displacement = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};//neighboor - coordinate relation
    std::vector<int> numbers = {0, 1, 2, 3};//Will be used to randomly step around neighboors
    std::vector<Room*> cpy_rooms;//Will be used to check other contiguous cells
    std::pair<int, int> cellShift;//Will be used to compute shift between cells
    auto  g = std::mt19937{std::random_device{}()};//Random generator
    int baseRoom = 0, i = 0, j = 0, k = 0;//Loop constant

    for(int currentRoom = 1; currentRoom<_roomNumber; currentRoom++){
        std::shuffle(numbers.begin(), numbers.end(), g);//Neighboor random check order
        while(true){//choice baseroom which is able to welcome a new room
            baseRoom = rand()%currentRoom;//choose among previous rooms
            if(_rooms[baseRoom].neighboors_number()<4) break;//Check if maximum neighboor's number is reached
        }
        std::vector<bool> neighboors = _rooms[baseRoom].get_neighboors();//See selected room neighboors
        while(neighboors[numbers[i]]) i++;
        _rooms[baseRoom].set_neighboors(numbers[i]);//Add a neighboor to base
        _rooms[currentRoom].set_neighboors((numbers[i]+2)%4);//Add a neighboor to current room
        _rooms[currentRoom].set_position(_rooms[baseRoom].get_position()+displacement[numbers[i]]);//Place current room
        
        add_door(_rooms[baseRoom], numbers[i], _rooms[currentRoom], (numbers[i]+2)%4);
        //Add mobs according to room number (progressiv difficulty)
        for (int mobIdx = 0; mobIdx<_rooms[currentRoom].get_mobNumber(); mobIdx++){
            _livings.push_back(new Mob(living_roll_dice("mob")));
            _rooms[currentRoom].set_livings(*_livings.back());
        }

        for(int k=0; k<currentRoom; k++) if(k!=baseRoom) cpy_rooms.push_back(&_rooms[k]);//Create a copy
        
        if(!cpy_rooms.empty()){
            i = 0;
            while(i<cpy_rooms.size()){//While it remains non checked rooms 
                if(isContiguous(cpy_rooms[i]->get_position(), _rooms[currentRoom].get_position())){//Check if rooms touch
                    cellShift = cpy_rooms[i]->get_position()-_rooms[currentRoom].get_position();//Check position difference
                    j=0;
                    while(j<3 && displacement[j]!=cellShift) j++;//Define position direction
                    _rooms[currentRoom].set_neighboors(j);//Add neighboor to current room
                    cpy_rooms[i]->set_neighboors((j+2)%4);//Add neighboor to other room
                    add_door(_rooms[currentRoom], j, *cpy_rooms[i], (j+2)%4);
                }
                i++;
            }
            cpy_rooms.clear();
        }
    }
}
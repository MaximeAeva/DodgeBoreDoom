#include "map.hpp"

//###################   GENERAL ##################

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}  

template <typename T,typename U>    
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}  

template <typename T,typename U>                                                   
bool operator==(std::pair<T,U> & l, std::pair<T,U> & r) {   
    return l.first==r.first && l.second==r.second;                                    
} 

template <typename T,typename U>                                                   
bool isContiguous(std::pair<T,U> & l, std::pair<T,U> & r) {   
    float dist = sqrt(pow(l.first-r.first, 2)+pow(l.second-r.second));
    return dist<sqrt(2);                                    
} 

//###################   ROOM    ##################

//###################   DOOR    ##################
//###################   MAP     ##################

/**
 * @brief Construct a new Map:: Map object
 * 
 * @param roomNumber number of rooms in the maze
 */
Map::Map(const int &roomNumber): _roomNumber(roomNumber){
    for(int i = 0; i<roomNumber; i++) _rooms.push_back(Room());// Add rooms
    mapping();//Place room
}

/**
 * @brief Destroy the Map:: Map object
 * 
 */
Map::~Map(){
    _rooms.clear();
    //_doors.clear();
}

/**
 * @brief Place rooms and doors
 * 
 */
void Map::mapping(){
    std::vector<std::pair<int, int>> displacement = {{1, 0}, {0, -1}, {-1, 0}, {0, 1}};//neighboor - coordinate relation
    std::vector<int> numbers = {0, 1, 2, 3};
    auto  g = std::mt19937{std::random_device{}()};
    int baseRoom = 0, i = 0;

    for(int currentRoom = 1; currentRoom<_roomNumber; currentRoom++){
        std::shuffle(numbers.begin(), numbers.end(), g);//Neighboor random check order
        while(true){//Ensure baseroom is able to welcome a new room
            baseRoom = rand()%currentRoom;//choose among previous rooms
            if(_rooms[baseRoom].neighboors_number()<4) break;//Check if maximum neighboor's number is reached
        }
        std::vector<bool> neighboors = _rooms[baseRoom].get_neighboors();//See selected room neighboors
        while(neighboors[numbers[i]]) i++;
        _rooms[baseRoom].set_neighboors(numbers[i]);//Add a neighboor to base
        _rooms[currentRoom].set_neighboors((numbers[i]+2)%4);//Add a neighboor to current room
        _rooms[currentRoom].set_position(_rooms[baseRoom].get_position()+displacement[numbers[i]]);//Place current room
        
        i = 0;
        while(i<_rooms.size()){//While it remains non checked rooms 
            if(isContiguous(_rooms[i].get_position(), _rooms[currentRoom].get_position())){
                
            }
        }
    }
}
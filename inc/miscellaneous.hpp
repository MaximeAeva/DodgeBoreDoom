#ifndef MISCELLANEOUS_H
#define MISCELLANEOUS_H

#include <ctime>
#include <cmath>
#include <fstream>
#include <sstream>
#include <map>
#include <iterator>
#include <random>

/**
 * @brief Stores Map parameters from design textfile
 * 
 */
struct Map_parms{
    Map_parms(std::map<std::string, std::string> p={}){
        for (int i = 0; i<int(std::size(_keys)); i++){ 
            if(auto it = p.find(_keys[i]); it != p.end()){
                switch (i)
                {
                case 0:
                    _roomNumber = std::stoi(it->second);
                    break;
                
                default:
                    break;
                }
            }
        }
    };
    std::string _keys[1] = {"roomNumber"};
    int _roomNumber = 5;
};

/**
 * @brief Stores Objects parameters from design textfile
 * 
 */
struct Object_parms{
    Object_parms(std::map<std::string, std::string> p={}){
        for (int i = 0; i<int(std::size(_keys)); i++){ 
            if(auto it = p.find(_keys[i]); it != p.end()){
                switch (i)
                {
                case 0:
                    _class = it->second;
                    break;
                case 1:
                    _name = it->second;
                    break;
                case 2:
                    _rare = std::stoi(it->second);
                    break;
                case 3:
                    _damage = std::stoi(it->second);
                    break;
                case 4:
                    _defense = std::stoi(it->second);
                    break;
                case 5:
                    _pushback = std::stoi(it->second);
                    break;
                case 6:
                    _power = std::stoi(it->second);
                    break;
                case 7:
                    _display.assign(it->second.begin(), it->second.end());
                    break;
                default:
                    break;
                }
            }
        }
    };
    std::string _keys[8] = {"class", "name", "rare", "damage", 
                            "defense", "pushback", "power", "display"};
    std::string _class = "object";
    std::string _name = "randomObject";
    int _rare = 0;
    int _damage = 0;
    int _defense = 0;
    int _pushback = 0;
    int _power = 0;
    std::vector<char> _display = {'a', 'a', 'a', 'a'};
};

/**
 * @brief Stores Living parameters from design textfile
 * 
 */
struct Living_parms{
    Living_parms(std::map<std::string, std::string> p={}){
        for (int i = 0; i<int(std::size(_keys)); i++){ 
            if(auto it = p.find(_keys[i]); it != p.end()){
                switch (i)
                {
                case 0:
                    _class = it->second;
                    break;
                case 1:
                    _name = it->second;
                    break;
                case 2:
                    _rare = std::stoi(it->second);
                    break;
                case 3:
                    _life = std::stoi(it->second);
                    break;
                case 4:
                    _force = std::stoi(it->second);
                    break;
                case 5:
                    _bpSize = std::stoi(it->second);
                    break;
                case 6:
                    _team = std::stoi(it->second);
                    break;
                case 7:
                    _display.assign(it->second.begin(), it->second.end());
                    break;
                default:
                    break;
                }
            }
        }
    };
    std::string _keys[8] = {"class", "name", "rare", "life", 
                            "force", "bpSize", "team", "display"};
    //Class
    std::string _class = "mob";
    //Name
    std::string _name = "randomMob";
    int _rare = 0;
    int _life = 10;
    int _force = 1;
    int _bpSize = 1;
    int _team = 2;
    std::vector<char> _display = {'e', 'e', 'a', 'a', 'T', 'T', 'T', 'T', 'X', 'X', 'X', 'X'};
};


//Map design
inline std::vector<Map_parms> MAP_P;
//Objects design
inline std::vector<Object_parms> OBJECTS_P;
//Living design
inline std::vector<Living_parms> LIVING_P;

inline float boxMuller(float mu, float sigma, unsigned int seed)
{
    srand(seed);
    float a = (rand() % 100 + 0.001)/float(100);
    float b = (rand() % 100 + 0.001)/float(100);

    return (sqrt(-2.0*log(a))*cos(2.0*3.141592*b))*sigma + mu;
};

template <typename T,typename U>                                                   
std::pair<T,U> operator+(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first+r.first,l.second+r.second};                                    
}  

template <typename T,typename U>    
std::pair<T,U> operator-(const std::pair<T,U> & l,const std::pair<T,U> & r) {   
    return {l.first-r.first,l.second-r.second};                                    
}  

/**
 * @brief Check if pairs are next to each other
 * 
 * @tparam T 
 * @tparam U 
 * @param l 
 * @param r 
 * @return true 
 * @return false 
 */
template <typename T,typename U>                                                   
bool isContiguous(const std::pair<T,U> & l, const std::pair<T,U> & r) {   
    return (l.first==r.first && abs(l.second-r.second)==1) || (l.second==r.second && abs(l.first-r.first)==1);                                  
} 

/**
 * @brief Load design.txt file and parse parameters to structures
 * 
 */
inline void loadDesign(){   
    std::ifstream designFile("res/design.txt");//Open file
    if (!designFile.is_open()) {
        std::cerr << "Error: Unable to open file!" << std::endl;
        return;
    }
    std::map<std::string, std::string> properties;
    std::string line;//string of a read line
    std::string subline;//subString
    std::string ssline;//second split
    int sepA, sepB;
    while(line!="END" && !designFile.eof()){
        properties.clear();
        std::getline(designFile, line);
        std::istringstream iss(line);
        std::string pair;
        while (std::getline(iss, pair, ',')) {
            size_t colonPos = pair.find(':');
            if (colonPos != std::string::npos) {
                std::string key = pair.substr(0, colonPos);
                std::string value = pair.substr(colonPos + 1);
                properties[key] = value;
            }
        }
        if(properties.find("main") != properties.end()){
            if(properties["main"]=="object") OBJECTS_P.push_back(Object_parms(properties));
            else if(properties["main"]=="living") LIVING_P.push_back(Living_parms(properties));
            else if(properties["main"]=="map") MAP_P.push_back(Map_parms(properties));
        }
    }
    designFile.close();
}

/**
 * @brief Roll dice to give Object of desired class
 * 
 * @param c class
 * @param seed 
 * @return Object_parms 
 */
inline Object_parms object_roll_dice(std::string c, unsigned int seed = time(NULL)){
    std::vector<Object_parms> v;
    for(Object_parms o : OBJECTS_P)
        if(o._class == c) v.push_back(o);
    if(v.size()){
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, v.size()-1);
        return v[dist(gen)];
    }
    return Object_parms();
}

/**
 * @brief Roll dice to give living of the desired class
 * 
 * @param c class
 * @param seed 
 * @return Living_parms 
 */
inline Living_parms living_roll_dice(std::string c, unsigned int seed = time(NULL)){
    std::vector<Living_parms> v;
    for(Living_parms l : LIVING_P){
        if(l._class == c) v.push_back(l);
    }
    if(v.size()){
        static std::mt19937 gen(std::random_device{}());
        std::uniform_int_distribution<int> dist(0, v.size()-1);
        return v[dist(gen)];
    }
    return Living_parms();
}

/**
 * @brief Find an Object according to name or class
 * 
 * @param c 
 * @param n 
 * @param seed 
 * @return Object_parms 
 */
inline Object_parms object_find(std::string c = "", std::string n = "", unsigned int seed = time(NULL)){
    std::vector<Object_parms> v;
    for(Object_parms o : OBJECTS_P)
        if(o._class == c  || o._name == n) return o;

    return Object_parms();
}

inline Living_parms living_find(std::string c = "", std::string n = "", unsigned int seed = time(NULL)){
    std::vector<Living_parms> v;
    for(Living_parms l : LIVING_P)
        if(l._class == c  || l._name == n) return l;

    return Living_parms();
}

#endif
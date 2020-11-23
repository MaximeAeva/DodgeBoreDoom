#include "map.hpp"

map::map(const int &room_number)
{
    std::vector<int> v;
    for(int i = 0; i<4; i++) v.push_back(0);
    room *r = new room;
    r->neighboors = v;
    this->rooms.push_back(r);
    while(this->rooms.size()<room_number)
        placeARoom(rand() %4 + 1, rand()%this->rooms.size());
    this->currentPosition = {0, 0};
}
/*
map::~map()
{
    for(int i = 0; i<this->doors.size(); i++)
        delete this->doors[i];
    this->doors.clear();
    for(int i = 0; i<this->rooms.size(); i++)
        delete this->rooms[i];
    this->rooms.clear();
}
*/
void map::placeARoom(const int &number, const int &ind)
{
    int i = 0;
    std::vector<int> freePlace;//check free space around
    std::vector<int> neighb;//neighboors
    while(i<number)
    {
        freePlace.clear();
        for(int k = 0; k<4; k++)
            if(!this->rooms[ind]->neighboors[k]) freePlace.push_back(k);
        if(freePlace.empty()) break;//If no space, check elsewhere
        int rd = rand() % freePlace.size();// else pick one of those randomly
        std::pair<int, int> p = this->rooms[ind]->position;//Parent position
        switch(freePlace[rd])
        {
            case 0 :
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
        }//New position carried by p
        room *r = new room;
        neighb.clear();
        for(int j = 0; j<4; j++) neighb.push_back(0);
        for(int n = 0; n<this->rooms.size(); n++)
        { 
            if(abs(this->rooms[n]->position.first - p.first)+
                abs(this->rooms[n]->position.second - p.second)==1)
            {
                if(this->rooms[n]->position.first > p.first)
                {
                    neighb[0]++;
                    if(!this->rooms[n]->neighboors[2]) this->rooms[n]->neighboors[2]++;
                    door *d = new door{rand()%5+1, true, r, this->rooms[n]};
                    this->doors.push_back(d);
                }
                else if(this->rooms[n]->position.second > p.second)
                {
                    neighb[3]++;
                    if(!this->rooms[n]->neighboors[1]) this->rooms[n]->neighboors[1]++;
                    door *d = new door{rand()%5+1, true, r, this->rooms[n]};
                    this->doors.push_back(d);
                }
                else if(this->rooms[n]->position.first < p.first)
                {
                    neighb[2]++;
                    if(!this->rooms[n]->neighboors[0]) this->rooms[n]->neighboors[0]++;
                    door *d = new door{rand()%5+1, true, r, this->rooms[n]};
                    this->doors.push_back(d);
                }
                else
                {
                    neighb[1]++;
                    if(!this->rooms[n]->neighboors[3]) this->rooms[n]->neighboors[3]++;
                    door *d = new door{rand()%5+1, true, r, this->rooms[n]};
                    this->doors.push_back(d);
                }
            }
        }
        
        r->neighboors = neighb;
        r->chest_number = rand()%(1+(p.first+p.second)/4);
        r->mob_number = rand()%(1+2*(abs(p.first)+abs(p.second)))+2;
        r->position = p;
        this->rooms.push_back(r);
        i++;
    }
        
}

void map::designRoom()
{
    room *r = findRoom(currentPosition);
    attrset(COLOR_WHITE);
    for(int i = 0; i<COLS; i++)
    {
        if(r->neighboors[1])//there's a door
        {
            if(i<COLS/2-1 || i>COLS/2+1)//Avoid the door
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
            if(i<COLS/2-1 || i>COLS/2+1)//Avoid the door
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
}

void map::doorDisplay(const int &position)
{
    init_pair(mainstream, COLOR_BLACK, COLOR_WHITE);
    init_pair(common, COLOR_BLACK, COLOR_RED);
    init_pair(supp, COLOR_BLACK, COLOR_YELLOW);
    init_pair(topTier, COLOR_BLACK, COLOR_GREEN);
    init_pair(godLike, COLOR_BLACK, COLOR_BLUE);
    init_pair(legendary, COLOR_BLACK, COLOR_CYAN);

    door *d = getDoorInPosition(getCurrentRoom(), position);

    attrset(d->id);

    int row = floor(LINES/2);
    int col = floor(COLS/2);
    if(position == 0)
    {
        if(d->state)
        {
            mvaddstr(row-2, COLS-5, "====");
            mvaddch(row-2, COLS-1, 0x01C1);
            mvaddch(row-1, COLS-1, 0x01C1);
            mvaddch(row, COLS-1, 0x01C1);
            mvaddch(row+1, COLS-1, 0x01C1);
            mvaddch(row+2, COLS-1, 0x01C1);
            mvaddstr(row+2, COLS-5, "====");
        }
        else
        {
            mvaddstr(row-2, COLS-5, "====");
            mvaddch(row-2, COLS-1, 0x01C1);
            mvaddch(row-1, COLS-1, 0x01C1);
            mvaddstr(row-1, COLS-5, "    ");
            mvaddch(row, COLS-1, 0x01C1);
            mvaddstr(row-1, COLS-5, "    ");
            mvaddch(row+1, COLS-1, 0x01C1);
            mvaddch(row+2, COLS-1, 0x01C1);
            mvaddstr(row+2, COLS-5, "====");
            mvaddstr(row, COLS-5, "----");
        }
    }
    if(position == 1)
    {
        if(d->state)
        {
            mvaddstr(0, col-4, "=======");
            mvaddstr(1, col-4, "]     [");
            mvaddstr(2, col-4, "]     [");
        }
        else
        {
            mvaddstr(0, col-4, "=======");
            mvaddstr(1, col-4, "|  I  |");
            mvaddstr(2, col-4, "|  I  |");
        }
    }
    if(position == 2)
    {
        if(d->state)
        {
            mvaddstr(row-2, 1, "====");
            mvaddch(row-2, 0, 0x01C1);
            mvaddch(row-1, 0, 0x01C1);
            mvaddch(row, 0, 0x01C1);
            mvaddch(row+1, 0, 0x01C1);
            mvaddch(row+2, 0, 0x01C1);
            mvaddstr(row+2, 1, "====");
        }
        else
        {
            mvaddstr(row-2, 1, "====");
            mvaddch(row-2, 0, 0x01C1);
            mvaddch(row-1, 0, 0x01C1);
            mvaddstr(row-1, 1, "    ");
            mvaddch(row, 0, 0x01C1);
            mvaddstr(row+1, 1, "    ");
            mvaddch(row+1, 0, 0x01C1);
            mvaddch(row+2, 0, 0x01C1);
            mvaddstr(row+2, 1, "====");
            mvaddstr(row, 1, "----");
        }
    }
    else
    {
        if(d->state)
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

room* map::findRoom(std::pair<int, int> position)
{
    for(int i = 0; i<this->rooms.size(); i++)
        if(this->rooms[i]->position == position) return this->rooms[i];
}

door* map::getCommonDoor(const room *r1, const room *r2)
{
    for(int i = 0; i<this->doors.size(); i++)
    {
        if(this->doors[i]->r1 == r1 && this->doors[i]->r2 == r2)
            return this->doors[i];
        else if (this->doors[i]->r1 == r1 && this->doors[i]->r2 == r2)
            return this->doors[i];
    }
    return NULL;
}

std::vector<door*> map::getRoomDoors(const room* r)
{
    std::vector<door*> v;
    for(int i = 0; i<this->doors.size(); i++)
    {
        if(this->doors[i]->r1 == r || this->doors[i]->r2 == r) 
            v.push_back(this->doors[i]);
        if(v.size()==4) break;
    }
    return v;
}

door* map::getDoorInPosition(const room* r, const int &position)
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
    }
    return getCommonDoor(r, findRoom(p));
}
#ifndef OBJECT_H
#define OBJECT_H

class weapon;

class object{
    public:
        object(){};
        virtual void display(const int &x, const int &y,
         const int &look);
};

#endif
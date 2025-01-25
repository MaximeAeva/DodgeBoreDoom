#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <PDCurses-3.9/curses.h>

#define mainstream 0
#define common 1
#define supp 2
#define topTier 3
#define godLike 4
#define legendary 5

void drawTexture(const int &x, const int &y, std::string category,
                std::string subcat = std::string(), std::string position = std::string());

void screenInit();


#endif DISPLAY_H
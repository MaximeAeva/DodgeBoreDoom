#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <cstdlib>
#include <string>
#include <PDCurses-3.9/curses.h>

void drawTexture(const int &x, const int &y, std::string category,
                std::string subcat = std::string(), std::string position = std::string());


#endif DISPLAY_H
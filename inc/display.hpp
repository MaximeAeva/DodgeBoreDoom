#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <fstream>
#include <string>

char * importTexture(){
std::fstream newfile;
   newfile.open("../res/design.txt", std::ios::in); //open a file to perform read operation using file object
   if (newfile.is_open()){   //checking whether the file is open
      std::string tp;
      while(getline(newfile, tp)){  //read data from file object and put it into string.
         std::cout << tp << "\n";   //print the data of the string
      }
      newfile.close();   //close the file object.
   }
}


#endif DISPLAY_H
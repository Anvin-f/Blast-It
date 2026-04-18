#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#include <vector>

struct Gamedata {
    int table[8][8];
    int lineid[3];
    int r, c;
    int choosen;
    
    bool gameover;
    bool outofbounds;
    
    int point;
    bool line;
    int mutiplier;
};

#endif
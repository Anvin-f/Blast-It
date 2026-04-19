#include "blocks.h"
#include "chooseblocks.h"
#include "gamedata.h"
#include "blocklist.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>

Gamedata data;

bool checkinsert() {
    // check if the block can be inserted into the grid
    bool valid = true;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            valid &= data.table[i][j] != 3;
        }
    }
    return valid;
}

void hoverblock(int id) {
    std::string s = callblock(id);
    int n = s.size();
    int nowr = data.r;
    int nowc = data.c;

    // get rid of the previous hover block
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            data.table[i][j] &= 1;
        }
    }

    // insert the new hover block
    for(int i = 0; i < n; i++) {
        if(s[i] == '#' && std::max(nowr, nowc) < 8) data.table[nowr][nowc] |= 2;
        if(s[i] == '/') nowr++, nowc = data.c;
        else nowc++;
    }
}

void insertblock() {
    // Insert the block into the game
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(data.table[i][j] == 2) data.table[i][j] = 1;
        }
    }

    int point = 0;
    // calculate how many complete lines of row or column there are after adding the new block
    std::vector<std::pair<char, int>> lines;
    for(int i = 0; i<8; i++) {
        bool ch = 1, ch2 = 1;
        for(int j = 0; j<8; j++) {
            ch &= data.table[i][j];
            ch2 &= data.table[j][i];
        }

        if(ch) lines.emplace_back('r', i);
        if(ch2) lines.emplace_back('c', i);
    }
    if(lines.size()) data.line = true;

    // remove all of the complete lines and calculate the points
    for(int i = 0; i<lines.size(); i++) {
        if(lines[i].first == 'r') {
            for(int j = 0; j<8; j++) data.table[lines[i].second][j] = 0;
        }
        else {
            for(int j = 0; j<8; j++) data.table[j][lines[i].second] = 0;
        }
    }
    
    //calculate the point
    data.point = std::max(point, (int)(30*lines.size()-20))*data.mutiplier;
}

bool checkallinsert(int id) {
    // check if the block with id can be inserted into the grid
    std::string s = callblock(id);
    int n = s.size();
    for(int r = 0; r<8; r++) {
        for(int c = 0; c<8; c++) {
            bool ch = true;
            int nowr = r, nowc = c;
            for(int i = 0; i < n; i++) {
                if(s[i] == '#') {
                    ch &= nowr < 8 && nowc < 8 && data.table[nowr][nowc] == 0;
                }
                if(s[i] == '/') nowr++, nowc = c;
                else nowc++;
            }
            if(ch) return false;
        }
    }
    return true;
}

Gamedata refresh(int difficulty) {
    if(data.line) data.mutiplier++;
    else data.mutiplier = 1;
    data.line = false;
    std::tuple<int, int, int> ids = chooseblocks(difficulty);
    data.lineid[0] = std::get<0>(ids);
    data.lineid[1] = std::get<1>(ids);
    data.lineid[2] = std::get<2>(ids);
    data.choosen = 0;
    return data;
}

Gamedata playconfirm() {
    if(!checkinsert()) return data;
    insertblock();
    data.lineid[data.choosen] = -1;

    data.r = 0;
    data.c = 0;

    if(data.lineid[0] != -1) data.choosen = 0;
    else if(data.lineid[1] != -1) data.choosen = 1;
    else data.choosen = 2;

    data.gameover = 1;
    if(data.lineid[0] != -1) data.gameover &= checkallinsert(data.lineid[0]);
    if(data.lineid[1] != -1) data.gameover &= checkallinsert(data.lineid[1]);
    if(data.lineid[2] != -1) data.gameover &= checkallinsert(data.lineid[2]);

    return data;
}

Gamedata playchoose(char s) {
    // change the block wanted to be inserted
    int x = s-'0'-1;
    if(data.lineid[x] != -1) {
        data.choosen = x - 1;
        // ensure that the hovered block is in the grid
        std::pair<int, int> dim = dimension(data.lineid[data.choosen]);
        data.r = std::min(8-dim.first, data.r);
        data.c = std::min(8-dim.second, data.c);

        // add the hover block to the grid;
        hoverblock(data.lineid[data.choosen]);
    }
    return data;
}

Gamedata playwasd(char s) {
    // the block move in the grid when the player press wasd
    std::pair<int, int> dim = dimension(data.lineid[data.choosen]);
    if(s == 'w') data.r = std::max(0, data.r-1);
    else if(s == 's') data.r = std::min(8-dim.first, data.r+1);
    else if(s == 'a') data.c = std::max(0, data.c-1);
    else if(s == 'd') data.c = std::min(8-dim.second, data.c+1);
    hoverblock(data.lineid[data.choosen]);
    return data;
}

Gamedata blockInit(int difficulty) {
    // initialize the gamedata for a new game
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            data.table[i][j] = 0;
        }
    }
    std::tuple<int, int, int> ids = chooseblocks(difficulty);
    data.lineid[0] = std::get<0>(ids);
    data.lineid[1] = std::get<1>(ids);
    data.lineid[2] = std::get<2>(ids);

    data.r = 0;
    data.c = 0;

    data.choosen = 0;

    data.point = 0;
    data.line = false;
    data.mutiplier = 1;
    
    data.gameover = false;
    return data;
}
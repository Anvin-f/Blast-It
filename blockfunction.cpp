#include "blockfunction.h"
#include "chooseblocks.h"
#include "gamedata.h"
#include "blocklist.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>

bool checkinsert(Gamedata data) {
    // check if the block can be inserted into the grid
    bool valid = true;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            valid &= data.table[i][j] != 3;
        }
    }
    return valid;
}

void hoverblock(Gamedata &data) {
    int id = data.lineid[data.choosen];
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

void insertblock(Gamedata &data) {
    // Insert the block into the game
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            if(data.table[i][j] == 2) data.table[i][j] = 1;
        }
    }

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
    data.point = std::max(0, (int)(30*lines.size()-20))*data.mutiplier;
}

std::pair<int, int> checkallinsert(Gamedata data, int x) {
    // check if the block with id can be inserted into the grid
    int id = data.lineid[x];
    std::string s = callblock(id);
    int n = s.size();
    for(int r = 0; r<8; r++) {
        for(int c = 0; c<8; c++) {
            bool ch = true;
            int nowr = r, nowc = c;
            for(int i = 0; i < n; i++) {
                if(s[i] == '#' && std::max(nowr, nowc) < 8) {
                    ch &= data.table[nowr][nowc] == 0;
                }
                if(s[i] == '/') nowr++, nowc = c;
                else nowc++;
            }
            std::pair<int, int> res = {r, c};
            if(ch) return res;
        }
    }
    std::pair<int, int> res = {-1, -1};
    return res;
}

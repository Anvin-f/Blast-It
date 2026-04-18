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
    bool valid = true;
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            valid &= data.table[i][j] != 3;
        }
    }
    return valid;
}

void hoverblock(int id) {
    data.outofbounds = false;
    std::string s = callblock(id);
    int n = s.size();
    int nowr = data.r;
    int nowc = data.c;

    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            data.table[i][j] &= 1;
        }
    }

    for(int i = 0; i < n; i++) {
        if(s[i] == '#' && std::max(nowr, nowc) < 8) data.table[nowr][nowc] |= 2;
        if(s[i] == '/') nowr++, nowc = data.c;
        else nowc++;

        if(std::max(nowr, nowc) >= 8) data.outofbounds = true;
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

    data.point = std::max(point, (int)(30*lines.size()-20))*data.mutiplier;
}

Gamedata playconfirm(int difficulty) {
    if(!checkinsert() || data.outofbounds) return data;
    insertblock();
    data.lineid[data.choosen] = -1;

    if(std::max({data.lineid[0], data.lineid[1], data.lineid[2]}) == -1) {
        if(data.line) data.mutiplier++;
        else data.mutiplier = 1;
        data.line = false;
        std::tuple<int, int, int> ids = chooseblocks(difficulty);
        data.lineid[0] = std::get<0>(ids);
        data.lineid[1] = std::get<1>(ids);
        data.lineid[2] = std::get<2>(ids);
    }

    data.r = 0;
    data.c = 0;

    if(data.lineid[0] != -1) data.choosen = 0;
    else if(data.lineid[1] != -1) data.choosen = 1;
    else data.choosen = 2;

    data.gameover = 1;
    
    return data;
}

Gamedata playchoose(char s) {
    int x = s-'0';
    if(data.lineid[x] != -1) {
        data.choosen = x;
        hoverblock(data.lineid[data.choosen]);
    }
    return data;
}

Gamedata playwasd(int id[], char s) {
    if(s == 'w') data.r = std::max(0, data.r-1);
    else if(s == 's') data.r = std::min(7, data.r+1);
    else if(s == 'a') data.c = std::max(0, data.c-1);
    else if(s == 'd') data.c = std::min(7, data.c+1);
    hoverblock(data.lineid[data.choosen]);
    return data;
}

void initialize(int difficulty) {
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

    data.line = false;
    data.mutiplier = 1;
    
    data.outofbounds = false;
    data.gameover = false;
    return;
}
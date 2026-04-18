#include "blocks.h"
#include "chooseblocks.h"
#include "blocklist.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <utility>

bool checkinsert(int id, int r, int c, int table[][8]) {
    bool valid = true;
    std::string s = callblock(id);
    int n = s.size();
    int nowr = r;  
    int nowc = c;
    for(int i = 0; i < n; i++) {
        if(s[i] == '#') {
            valid &= table[nowr][nowc] == 0;
        }
        
        if(s[i] == '/') nowr++, nowc = c;
        else nowc++;

        valid &= nowr <= 8 && nowc <= 8;
    }
    return valid;
}
int insertblock(int id, int r, int c, int table[][8]) {
    std::string s = callblock(id);
    int n = s.size();
    int nowr = r;
    int nowc = c;
    for(int i = 0; i < n; i++) {
        if(s[i] == '#') table[nowr][nowc] = 1;
        if(s[i] == '/') nowr++, nowc = c;
        else nowc++;
    }

    int point = 0;
    // calculate how many complete lines of row or 
    std::vector<std::pair<char, int>> lines;
    for(int i = 0; i<8; i++) {
        bool ch = 1, ch2 = 1;
        for(int j = 0; j<8; j++) {
            ch &= table[i][j];
            ch2 &= table[j][i];
        }

        if(ch) lines.emplace_back('r', i);
        if(ch2) lines.emplace_back('c', i);
    }

    for(int i = 0; i<lines.size(); i++) {
        if(lines[i].first == 'r') {
            for(int j = 0; j<8; j++) table[lines[i].second][j] = 0;
        }
        else {
            for(int j = 0; j<8; j++) table[j][lines[i].second] = 0;
        }
    }

    point = std::max(point, (int)(30*vec.size()-20));
    return point;
}

void play(int difficulty) {
    char s; std::cin >> s;
    int fre = 0;
    int choosen = 0;
    while(s != 'q') {
        int id[3];
        if(fre == 0) {
            std::tuple<int, int, int> ids = chooseblocks(difficulty);
            id[0] = std::get<0>(ids);
            id[1] = std::get<1>(ids);
            id[2] = std::get<2>(ids);
            fre += 3;
        }

        if(!choosen) {
            std::cin >> s;
            choosen = s-'0'-1;
        }

        int nowr = 1, nowc = 1;
        
    }
}
#include "blocks.h"
#include "chooseblocks.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <fstream>
#include <utility>

bool checkinsert(int id, int r, int c, int table[][8]) {
    std::ifstream file("block.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open block.txt" << std::endl;
        return 0;
    }
    bool valid = true;
    std::string s;
    int fre = 0;
    while(std::cin >> s) {
        if(fre == id) {
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
        }
        fre++;
    }
    file.close();
    return valid;
}
int insert(int id, int r, int c, int table[][8]) {
    std::ifstream file("block.txt");
    if (!file.is_open()) {
        std::cout << "Failed to open block.txt" << std::endl;
        return;
    }

    std::string s;
    int fre = 0;
    while(std::cin >> s) {
        if(fre == id) {
            int n = s.size();
            int nowr = r;
            int nowc = c;
            for(int i = 0; i < n; i++) {
                if(s[i] == '#') table[nowr][nowc] = 1;
                
                if(s[i] == '/') nowr++, nowc = c;
                else nowc++;
            }
        }
        fre++;
    }
    file.close();

    int point = 0;
    vector<pair<char, int>> vec;
    for(int i = 1; i<=8; i++) {
        bool ch = 1;
        for(int j = 1; j<=8; j++) {
            ch &= table[i][j];
        }

    }

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
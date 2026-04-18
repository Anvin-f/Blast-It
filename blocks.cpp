#include "blocks.h"
#include <iostream>
#include <fstream>


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
void insert(int id, int r, int c, int table[][8]) {
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
}
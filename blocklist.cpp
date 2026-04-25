#include "chooseblocks.h"
#include "blocklist.h"
#include <string>
#include <vector>

std::string callblock(int id) {
    // return the block string according to the id
    return blocklist[id];
}

std::pair<int, int> dimension(int id) {
    // calculate the dimension of the block according to the id
    std::string s = callblock(id);
    int n = s.size();
    int r = 1;
    int c = 0;
    for(int i = 0; i < n; i++) {
        if(s[i] == '/') {
            r++;
            c = 0;
        } 
        else c++;
    }
    return std::make_pair(r, c);
}
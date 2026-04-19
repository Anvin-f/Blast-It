#include "chooseblocks.h"
#include "blocks.h"
#include "gamedata.h"
#include <tuple>
#include<vector>
#include<random>
#include<ctime>

std::tuple<int, int, int> chooseblocks(Gamedata data, int difficulty) {
    std::mt19937 mt(time(nullptr)); 
    int x;
    if(difficulty == 1) x = 14;
    else if(difficulty == 2) x = 19;
    else x = 22;

    vector<int> vec;

    while(vec.size() != 3) {
        int posid = mt() % x;
        if(posid >= 19) posid -= 3;
        data.lineid[0] = posid;
        pair<int, int> x = checkallinsert(data, 0);
        if(x.first != -1) {
            vec.push_back(posid);
            data.r = x.first;
            data.c = x.second;
            data.choosen = 0;
            hoverblock(data);
            insertblock(data);
        }
    }

    if(mt()%2) swap(vec[0], vec[1]);
    if(mt()%2) swap(vec[0], vec[2]);
    if(mt()%2) swap(vec[1], vec[2]);
    return {vec[0], vec[1], vec[2]};
}
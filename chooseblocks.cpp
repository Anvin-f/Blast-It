#include "chooseblocks.h"
#include "blockfunction.h"
#include "gamedata.h"
#include <tuple>
#include<vector>
#include<random>
#include <utility>
#include<ctime>

std::tuple<int, int, int> chooseblocks(Gamedata data, int difficulty) {
    std::mt19937 mt(time(nullptr)); 
    int x;
    if(difficulty == 1) x = 14;
    else if(difficulty == 2) x = 19;
    else x = 22;

    std::vector<int> vec;

    while(vec.size() != 3) {
        int posid = mt()%x;
        if(posid >= 19) posid -= 3;
        data.lineid[0] = posid;
        std::pair<int, int> y = checkallinsert(data, 0);
        if(y.first != -1) {
            vec.push_back(posid);
            data.r = y.first;
            data.c = y.second;
            data.choosen = 0;
            hoverblock(data);
            insertblock(data);
        }
    }

    if(mt()%2) std::swap(vec[0], vec[1]);
    if(mt()%2) std::swap(vec[0], vec[2]);
    if(mt()%2) std::swap(vec[1], vec[2]);
    std::tuple<int, int, int> res = {vec[0], vec[1], vec[2]};
    return res;
}
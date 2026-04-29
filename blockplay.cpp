#include "blockplay.h"
#include "blockfunction.h"
#include "chooseblocks.h"
#include "gamedata.h"
#include "blocklist.h"
#include <utility>
#include <tuple>
#include <algorithm>

Gamedata data;

Gamedata refresh(int difficulty) {
    // when all 3 blocks are put then refresh the block and calculate the point
    data.gameover = false;
    if(data.line) data.mutiplier++;
    else data.mutiplier = 1;
    data.line = false;
    std::tuple<int, int, int> ids = chooseblocks(data, difficulty);
    data.lineid[0] = std::get<0>(ids);
    data.lineid[1] = std::get<1>(ids);
    data.lineid[2] = std::get<2>(ids);
    data.choosen = 0;
    return data;
}

Gamedata playconfirm() {
    //put the block at the current position and calculate the point
    //if the block cannot be put, ignore the input
    if(!checkinsert(data)) return data;
    insertblock(data);
    data.lineid[data.choosen] = -1;

    data.r = 0;
    data.c = 0;

    if(data.lineid[0] != -1) data.choosen = 0;
    else if(data.lineid[1] != -1) data.choosen = 1;
    else data.choosen = 2;

    // check if the game is over
    data.gameover = std::max({data.lineid[0], data.lineid[1], data.lineid[2]}) != -1;
    std::pair<int, int> compared = {-1, -1};
    if(data.lineid[0] != -1) data.gameover &= (checkallinsert(data, 0) == compared);
    if(data.lineid[1] != -1) data.gameover &= (checkallinsert(data, 1) == compared);
    if(data.lineid[2] != -1) data.gameover &= (checkallinsert(data, 2) == compared);

    return data;
}

Gamedata playchoose(char s) {
    // change the block wanted to be inserted
    int x = s-'0'-1;
    if(data.lineid[x] != -1) {
        data.choosen = x;
        // ensure that the hovered block is in the grid
        std::pair<int, int> dim = dimension(data.lineid[data.choosen]);
        data.r = std::min(8-dim.first, data.r);
        data.c = std::min(8-dim.second, data.c);

        // add the hover block to the grid;
        hoverblock(data);
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
    hoverblock(data);
    return data;
}

Gamedata blockInit(int difficulty) {
    // initialize the gamedata for a new game
    for(int i = 0; i<8; i++) {
        for(int j = 0; j<8; j++) {
            data.table[i][j] = 0;
        }
    }
    std::tuple<int, int, int> ids = chooseblocks(data, difficulty);
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
#include "chooseblocks.h"
#include <tuple>
#include<random>
#include<ctime>

std::tuple<int, int, int> chooseblocks(int difficulty) {
    std::mt19937 mt(time(nullptr)); 
    if(difficulty == 1) {
        int id1 = mt()%14;
        int id2 = mt()%14;
        int id3 = mt()%14;
        return std::make_tuple(id1, id2, id3);
    }
    else if(difficulty == 2) {
        int id1 = mt()%19;
        int id2 = mt()%19;
        int id3 = mt()%19;
        return std::make_tuple(id1, id2, id3);
    }
    else {
        int id1 = mt()%22;
        int id2 = mt()%22;
        int id3 = mt()%22;
        if(id1 >= 19) id1 -= 3;
        if(id2 >= 19) id2 -= 3;
        if(id3 >= 19) id3 -= 3;
        return std::make_tuple(id1, id2, id3);
    }
}
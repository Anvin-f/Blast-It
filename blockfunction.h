#ifndef BLOCKFUNCTION_H
#define BLOCKFUNCTION_H

#include "gamedata.h"
#include <cstddef>
#include <vector>
#include <utility>
#include <fstream>

bool checkinsert(Gamedata data);
void hoverblock(Gamedata &data);
void insertblock(Gamedata &data);
std::pair<int, int> checkallinsert(Gamedata data, int x);

#endif

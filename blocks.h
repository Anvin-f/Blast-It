#include "gamedata.h"
#include <cstddef>
#include <vector>
#include <fstream>

bool checkinsert(Gamedata data);
void hoverblock(Gamedata &data);
void insertblock(Gamedata &data);
pair<int, int> checkallinsert(Gamedata data, int c);
Gamedata refresh(int difficulty);
Gamedata playconfirm();
Gamedata playchoose(char s);
Gamedata playwasd(char s);
Gamedata blockInit(int difficulty);


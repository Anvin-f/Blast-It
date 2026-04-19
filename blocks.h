#include "gamedata.h"
#include <cstddef>
#include <vector>
#include <fstream>

bool checkinsert();
void hoverblock(int id);
void insertblock();
Gamedata refresh(int difficulty);
Gamedata playconfirm();
Gamedata playchoose(char s);
Gamedata playwasd(char s);
void blockInit(int difficulty);


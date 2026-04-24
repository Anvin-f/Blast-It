#ifndef BLOCKPLAY_H
#define BLOCKPLAY_H

#include "gamedata.h"

Gamedata refresh(int difficulty);
Gamedata playconfirm();
Gamedata playchoose(char s);
Gamedata playwasd(char s);
Gamedata blockInit(int difficulty);

#endif
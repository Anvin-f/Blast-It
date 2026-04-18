#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include <iostream>

struct Player {
    int hp;
    int max_hp;
    int base_attack;
    int defense;
    int ap_reserve;   // AP carried over from previous rounds
    int kills;        // number of monsters defeated
    int difficulty;   // 1 = Easy, 2 = Normal, 3 = Hard
};

Player initPlayer(int difficulty);

void damagePlayer(Player & p, int damage);

void healPlayer(Player & p, int amount);

bool isPlayerAlive(const Player & p);

bool canUseSpecial(const Player & p);

//save
void savePlayer(std::ostream & out, const Player & p);
//load
void loadPlayer(std::istream & in, Player & p);

#endif
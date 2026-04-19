#ifndef COMBAT_H
#define COMBAT_H
#include "player.h"
#include <string>
#include <iostream>

//current monster
struct Monster{
    std::string name;
    int hp;
    int max_hp;
    int attack;
    int bounty;    //score added to total score after a monster is killed
};

//this struct represents the player's decision for the current combat turn
struct CombatChoice{
    int attack_ap;      // AP spent on normal attack (0 = no attack)
    bool use_special;   // use special ability instead of normal attack
    int heal_ap;        // AP spent on heal (0 = no heal)
    int defend_ap;      // AP spent on defense (0 = no defense)
};

//this represents what happened during the turn. it is returned so the caller can update the UI 
struct CombatResult{
    int damage_dealt;
    int damage_taken;
    bool monster_defeated;
    bool player_defeated;
    int bounty_earned;      //scores earned to total score when monster is killed
    std::string log_message;
};
 
Monster initMonster(int difficulty, int kills);

int rollSpecialDamage(int base_attack);

CombatResult resolveCombatTurn(Player & player, Monster & monster, const CombatChoice & choice);

//saves
void saveMonster(std::ostream & out, const Monster & m);

//loads
void loadMonster(std::istream & in, Monster & m);

#endif

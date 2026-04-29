#include "player.h"

//initialises a new player for a specific difficulty
Player initPlayer(int difficulty){
    Player p;
    p.difficulty = difficulty;
    p.ap_reserve = 0;
    p.kills = 0;
    //easy
    if (difficulty == 1){
        p.hp = 150;
        p.max_hp = 150;
        p.base_attack = 15;
        p.defense = 5;
    } 
    //normal
    else if (difficulty == 2){
        p.hp = 100;
        p.max_hp = 100;
        p.base_attack = 10;
        p.defense = 3;
    } 
    //hard
    else if (difficulty == 3){
        p.hp = 70;
        p.max_hp = 70;
        p.base_attack = 8;
        p.defense = 1;
    }
    return p;
}

//implements damage onto the player, damage stops at 0, never goes negative
void damagePlayer(Player & p, int damage){
    if (damage < 0){    //damage cannot be negative
        damage = 0;
    }
    p.hp -= damage;
    if (p.hp < 0) {     //player hp cannot be negative
        p.hp = 0;
    }
}

//implements healing onto the player, healing stops at max_hp
void healPlayer(Player & p, int amount){
    if (amount < 0){
        return;     //heal value cannot be negative
    }
    p.hp += amount;
    if (p.hp > p.max_hp){   //plauyer hp cannot go above max
        p.hp = p.max_hp;
    }
}

//returns true if player is still alive
bool isPlayerAlive(const Player & p){
    return p.hp > 0;
}

//returns true if player is able to use special ability based on difficulty and kill count
bool canUseSpecial(const Player & p){
    //special ability always available for easy mode
    if (p.difficulty == 1){
        return true;
    } 
    //special ability only available after 3 kills for normal mode
    if (p.difficulty == 2){
        return p.kills >= 3;
    }
    //special ability only available after 5 kills for hard mode
    if (p.difficulty == 3){
        return p.kills >= 5;
    }
}

//saves player data to output stream
void savePlayer(std::ostream & out, const Player & p){
    out.write(reinterpret_cast<const char*>(&p.hp), sizeof(p.hp));
    out.write(reinterpret_cast<const char*>(&p.max_hp), sizeof(p.max_hp));
    out.write(reinterpret_cast<const char*>(&p.base_attack), sizeof(p.base_attack));
    out.write(reinterpret_cast<const char*>(&p.defense), sizeof(p.defense));
    out.write(reinterpret_cast<const char*>(&p.ap_reserve), sizeof(p.ap_reserve));
    out.write(reinterpret_cast<const char*>(&p.kills), sizeof(p.kills));
    out.write(reinterpret_cast<const char*>(&p.difficulty), sizeof(p.difficulty));
}

//loads player data from input stream
void loadPlayer(std::istream & in, Player & p){
    in.read(reinterpret_cast<char*>(&p.hp), sizeof(p.hp));
    in.read(reinterpret_cast<char*>(&p.max_hp), sizeof(p.max_hp));
    in.read(reinterpret_cast<char*>(&p.base_attack), sizeof(p.base_attack));
    in.read(reinterpret_cast<char*>(&p.defense), sizeof(p.defense));
    in.read(reinterpret_cast<char*>(&p.ap_reserve), sizeof(p.ap_reserve));
    in.read(reinterpret_cast<char*>(&p.kills), sizeof(p.kills));
    in.read(reinterpret_cast<char*>(&p.difficulty), sizeof(p.difficulty));
}
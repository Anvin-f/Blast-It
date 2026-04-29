#include "combat.h"
#include <random>
#include <sstream>
#include <algorithm>

//initializes seed once
static std::mt19937& rng(){
    static std::mt19937 generation(std::random_device{}());
    return generation;
}

//cost for special ability is fixed
static const int SPECIAL_AP_COST = 20;

//initializes a monster, and respawn a monster after a certain number of kills at the specific difficulty
Monster initMonster(int difficulty, int kills){
    Monster m;
    if (difficulty == 1){
        m.name = "Goblin";
        m.hp = 60 + kills * 15;
        m.attack = 10 + kills * 3;
        m.bounty = 30;
    }
    else if (difficulty == 2){
        m.name = "Orc";
        m.hp = 100 + kills * 20;
        m.attack = 14 + kills * 5;
        m.bounty = 50;
    }
    else if (difficulty == 3){
        m.name = "Dragon";
        m.hp = 140 + kills * 25;
        m.attack = 18 + kills * 8;
        m.bounty = 70;
    }
    m.max_hp = m.hp;
    return m;
}

int rollSpecialDamage(int base_attack){
    std::uniform_int_distribution<int> dist(2 * base_attack, 3 * base_attack);
    return dist(rng());
}

//resolves one combat turn and returns the outcome
CombatResult resolveCombatTurn(Player & player, Monster & monster, const CombatChoice& choice){
    CombatResult r = {}; //initializes all members to zero
    std::ostringstream log;

    //Player attacks
    if (choice.use_special) {
        int dmg = rollSpecialDamage(player.base_attack);
        monster.hp -= dmg;
        if (monster.hp < 0){
            monster.hp = 0;
        }
        r.damage_dealt = dmg;
        player.ap_reserve -= SPECIAL_AP_COST;
        log << "Special hits " << monster.name << " for " << dmg << ". ";
    }
    else if (choice.attack_ap > 0){
        int spend = choice.attack_ap;
        int dmg = player.base_attack + spend;
        monster.hp -= dmg;
        if (monster.hp < 0){
            monster.hp = 0;
        }
        r.damage_dealt = dmg;
        player.ap_reserve -= spend;
        log << "Attack hits for " << dmg << ". ";
    }

    //Player heals
    if (choice.heal_ap > 0){
        int spend = choice.heal_ap;
        healPlayer(player, spend);
        player.ap_reserve -= spend;
        log << "Healed " << spend << ". ";
    }

    //Check if Monster is still alive. Remaining AP rolls into reserve.
    if (monster.hp <= 0){
        r.monster_defeated = true;
        r.bounty_earned = monster.bounty;
        ++player.kills;
        log << monster.name << " defeated! +" << monster.bounty << " bounty.";
        r.log_message = log.str();
        return r;
    }

    //Monster attacks
    int defend_spend = choice.defend_ap;
    int incoming = monster.attack - player.defense - defend_spend;
    if (incoming < 0){
        incoming = 0;
    }
    damagePlayer(player, incoming);
    r.damage_taken = incoming;
    player.ap_reserve -= defend_spend;
    log << monster.name << " attacks for " << incoming << ".";

    if (!isPlayerAlive(player)) {
        r.player_defeated = true;
        log << " You died.";
    }
    r.log_message = log.str();
    return r;
}

//saves monster data to output stream
void saveMonster(std::ostream & out, const Monster & m){
    //save the string name
    size_t nameLen = m.name.length();
    out.write(reinterpret_cast<const char*>(&nameLen), sizeof(nameLen));
    out.write(m.name.c_str(), nameLen);
    
    //save numeric fields
    out.write(reinterpret_cast<const char*>(&m.hp), sizeof(m.hp));
    out.write(reinterpret_cast<const char*>(&m.max_hp), sizeof(m.max_hp));
    out.write(reinterpret_cast<const char*>(&m.attack), sizeof(m.attack));
    out.write(reinterpret_cast<const char*>(&m.bounty), sizeof(m.bounty));
}

//loads monster data from input stream
void loadMonster(std::istream & in, Monster & m){
    //load the string name
    size_t nameLen = 0;
    in.read(reinterpret_cast<char*>(&nameLen), sizeof(nameLen));
    char* buffer = new char[nameLen + 1];
    in.read(buffer, nameLen);
    buffer[nameLen] = '\0';
    m.name = std::string(buffer);
    delete[] buffer;
    
    //load numeric fields
    in.read(reinterpret_cast<char*>(&m.hp), sizeof(m.hp));
    in.read(reinterpret_cast<char*>(&m.max_hp), sizeof(m.max_hp));
    in.read(reinterpret_cast<char*>(&m.attack), sizeof(m.attack));
    in.read(reinterpret_cast<char*>(&m.bounty), sizeof(m.bounty));
}
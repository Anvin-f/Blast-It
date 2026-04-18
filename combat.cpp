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
        m.hp = 30 + kills * 10;
        m.attack = 8 + kills * 3;
        m.bounty = 30;
    }
    else if (difficulty == 2){
        m.name = "Orc";
        m.hp = 50 + kills * 15;
        m.attack = 12 + kills * 5;
        m.bounty = 50;
    }
    else if (difficulty == 3){
        m.name = "Dragon";
        m.hp = 70 + kills * 25;
        m.attack = 16 + kills * 8;
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
CombatResult resolveCombatTurn(Player & player, Monster & monster, int ap_available, const CombatChoice& choice){
    CombatResult r = {}; //initializes all members to zero
    std::ostringstream log;

    int total_ap = ap_available + player.ap_reserve;
    player.ap_reserve = 0;

    //Player attacks
    if (choice.use_special && canUseSpecial(player) && total_ap >= SPECIAL_AP_COST) {
        int dmg = rollSpecialDamage(player.base_attack);
        monster.hp -= dmg;
        if (monster.hp < 0){
            monster.hp = 0;
        }
        r.damage_dealt = dmg;
        total_ap -= SPECIAL_AP_COST;
        log << "Special hits " << monster.name << " for " << dmg << ". ";
    }
    else if (choice.attack_ap > 0){
        int spend = std::min(choice.attack_ap, total_ap);
        int dmg = player.base_attack + spend;
        monster.hp -= dmg;
        if (monster.hp < 0){
            monster.hp = 0;
        }
        r.damage_dealt = dmg;
        total_ap -= spend;
        log << "Attack hits for " << dmg << ". ";
    }

    //Player heals
    if (choice.heal_ap > 0){
        int spend = std::min(choice.heal_ap, total_ap);
        healPlayer(player, spend);
        total_ap -= spend;
        log << "Healed " << spend << ". ";
    }

    //Check if Monster is still alive. Remaining AP rolls into reserve.
    if (monster.hp <= 0){
        r.monster_defeated = true;
        r.bounty_earned = monster.bounty;
        ++player.kills;
        log << monster.name << " defeated! +" << monster.bounty << " bounty.";
        player.ap_reserve = total_ap;
        r.log_message = log.str();
        return r;
    }

    //Monster attacks
    int defend_spend = std::min(choice.defend_ap, total_ap);
    int incoming = monster.attack - player.defense - defend_spend;
    if (incoming < 0){
        incoming = 0;
    }
    damagePlayer(player, incoming);
    r.damage_taken = incoming;
    total_ap -= defend_spend;
    log << monster.name << " attacks for " << incoming << ".";

    if (!isPlayerAlive(player)) {
        r.player_defeated = true;
        log << " You died.";
    }
    player.ap_reserve = total_ap;
    r.log_message = log.str();
    return r;
}
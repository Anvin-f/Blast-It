#pragma once

#include <array>
#include <iostream>
#include <chrono>
#include <thread>
#include "screen.h"
#include "grid.h"
#include "gamedata.h"
#include "combat.h"
#include "player.h"

class Game {
public:
    Game();
    ~Game();

    void initialize();
    void run();
    bool isRunning() const;
    void handleInput();
    void render();
    void playerLost();
    void startBlastMode();
    void startRPGMode();
    void saveData();
    void loadData();
    
private:

    bool running;
    Screen screen;
    Grid grid;
    Gamedata data;
    int currentDifficulty = 1;
    bool isRPGMode = false;
    Player plr;
    Monster mtr;
    CombatChoice current_choice = {0, false, 0, 0};
    int rpg_state = 0;
    std::string current_status;
    int current_page = 0;
    std::string current_input;
    std::string logo = R"(
******   **           **      ******** **********       ** **********
/*////** /**          ****    **////// /////**///       /**/////**/// 
/*   /** /**         **//**  /**           /**          /**    /**    
/******  /**        **  //** /*********    /**          /**    /**    
/*//// **/**       **********////////**    /**          /**    /**    
/*    /**/**      /**//////**       /**    /**          /**    /**    
/******* /********/**     /** ********     /**          /**    /**    
///////  //////// //      // ////////      //           //     // 
)";
    std::vector<std::string> rpg_state_map = {
        "", 
        "Enter AP for Attack: ", 
        "Enable Special? (1=yes, 0=no): ", 
        "Enter AP for Heal: ", 
        "Enter AP for Defend: "
    };
};
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

private:

    bool running;
    Screen screen;
    Grid grid;
    Gamedata data;
    int currentDifficulty = 1;
    bool isRPGMode = false;
    Player plr;
    Monster mtr;
    int rpg_state = 0;
    int current_attack_ap = 0;
    bool current_use_special = false;
    int current_heal_ap = 0;
    int current_defend_ap = 0;
    std::string current_status;
    std::string current_input;
};
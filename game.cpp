#include <fstream>
#include <iostream>
#include "game.h"
#include "windows.h"
#include "chooseblocks.h"
#include "blockplay.h"
#include <sstream>
#include <string>
#include <limits>
#ifdef _WIN32
#include <conio.h>
#endif

Game::Game() : running(false), screen(85, 30), grid(8, 8, 3, 1) {
}

Game::~Game() {
}

//initialize a new game
void Game::initialize() {
    running = true;
    data = blockInit(currentDifficulty);
    // Initialize game data
    std::fill(&data.table[0][0], &data.table[0][0] + 64, 0);
    plr = initPlayer(currentDifficulty);
    mtr = initMonster(currentDifficulty, 0);
}

void Game::run() {
    while (isRunning()) {
        handleInput();
        render();
    }
}

bool Game::isRunning() const {
    return running;
}

void Game::playerLost() {
    running = false;
    return;
}


void Game::startBlastMode() {
    int total = current_choice.attack_ap + current_choice.heal_ap + current_choice.defend_ap + (current_choice.use_special ? 20 : 0);
    rpg_state = 0;

    if (total > plr.ap_reserve){current_choice = {0, false, 0, 0};return;}
    CombatResult result = resolveCombatTurn(plr, mtr, current_choice);
    if (result.monster_defeated) {
        mtr = initMonster(currentDifficulty, plr.kills);
    }
    if (result.player_defeated) {
        playerLost();
        return;
    }
    current_choice = {0, false, 0, 0};
    isRPGMode = false; //gamemode switch
    data = refresh(currentDifficulty);
    data = playchoose('1'); // '1' is the default block
}

void Game::startRPGMode() {
    isRPGMode = true; //gamemode switch
    if(plr.ap_reserve == 0){
        //skip combat if player has no AP
        startBlastMode();
    }
}

void Game::saveData() {
    // Saving game data to binary file
    std::ofstream outFile("savegame.dat", std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open savegame.dat for writing." << std::endl;
        return;
    }
    
    // Save player data
    savePlayer(outFile, plr);
    if (!outFile) {
        std::cerr << "Error: Failed to save player data." << std::endl;
        return;
    }
    
    // Save monster data
    saveMonster(outFile, mtr);
    if (!outFile) {
        std::cerr << "Error: Failed to save monster data." << std::endl;
        return;
    }
    
    // Save game data
    outFile.write(reinterpret_cast<const char*>(&data), sizeof(data));
    if (!outFile) {
        std::cerr << "Error: Failed to save game data." << std::endl;
        return;
    }
    
    outFile.close();
}

void Game::loadData() {
    // Loading game data from binary file
    std::ifstream inFile("savegame.dat", std::ios::binary);
    if (!inFile) {
        std::cerr << "Error: Could not open savegame.dat for reading." << std::endl;
        return;
    }
    
    // Load player data
    loadPlayer(inFile, plr);
    if (!inFile) {
        std::cerr << "Error: Failed to load player data." << std::endl;
        return;
    }
    
    // Load monster data
    loadMonster(inFile, mtr);
    if (!inFile) {
        std::cerr << "Error: Failed to load monster data." << std::endl;
        return;
    }
    
    // Load game data
    inFile.read(reinterpret_cast<char*>(&data), sizeof(data));
    if (!inFile) {
        std::cerr << "Error: Failed to load game data." << std::endl;
        return;
    }
    
    inFile.close();
}
void Game::handleInput() {
    bool keyPressed = false;
    char input = 0;

#ifdef _WIN32
    if (_kbhit()) {
        input = static_cast<char>(_getch());
        keyPressed = true;
    }
#else
    if (std::cin.peek() != EOF) {
        std::cin >> input;
        keyPressed = true;
    }
#endif

    if (!keyPressed) {return;}
    if (input == 'q' || input == 'Q') {
        current_page = 0;
        return;
    }
    if (current_page == 0 ){
        if (input == '3') {
            saveData();
            current_page = 1;
        } else if (input == '2') {
            loadData();
            current_page = 1;
        } else if (input == '4') {
            running = false;
            return;
        }else if (input == '1') {
            current_page = 2;
        }
    }else if (current_page == 2) {
        if (input == '1' || input == '2' || input == '3') {
            currentDifficulty = std::stoi(std::string(1, input));
        } else {
            return;
        }
        initialize();
        current_page = 1;
    }else if (current_page == 1) {

        if (isRPGMode) {
            // RPG mode input handling
            if (rpg_state == 0) {
                current_input = "";
                if (input == '1') {
                    rpg_state = 1;
                } else if (input == '2') {
                    rpg_state = 2;
                } else if (input == '3') {
                    rpg_state = 3;
                } else if (input == '4') {
                    rpg_state = 4;
                } else if (input == '\n' || input == '\r') {
                    startBlastMode();
                }
            }else{
                if (rpg_state == 1 || rpg_state == 3 || rpg_state == 4) {
                    if (isdigit(input)) {
                        current_input += input;
                    }
                } else if (rpg_state == 2) {
                    if (input == '0' || input == '1') {
                        current_input = input;
                    }
                }
                
                if (input == '\n' || input == '\r') {
                    if (rpg_state == 1) {
                        current_choice.attack_ap = std::stoi(current_input);
                    } else if (rpg_state == 2) {
                        current_choice.use_special = (current_input == "1");
                    } else if (rpg_state == 3) {
                        current_choice.heal_ap = std::stoi(current_input);
                    } else if (rpg_state == 4) {
                        current_choice.defend_ap = std::stoi(current_input);
                    }
                    rpg_state = 0;
                }
            }
            current_status = rpg_state_map[rpg_state] + (rpg_state? current_input : "");
            if (plr.hp<= 0) {playerLost();return;}
        } else {
            // Blast mode input handling
            current_status = "";
            if (input == '1' || input == '2' || input == '3') {
                data = playchoose(input);
            } else if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
                data = playwasd(input);
            } else if (input == '\n' || input == '\r') {
                data = playconfirm();
                plr.ap_reserve += data.point;
                if (data.lineid[0] == -1 && data.lineid[1] == -1 && data.lineid[2] == -1) {
                    startRPGMode();
                }
            }
            if (data.gameover) {playerLost();return;}
        }

    }
}


void Game::render() {
    screen.clear(' ');

    const std::size_t headerHeight = 3;
    const std::size_t leftPanelWidth = 50;
    const std::size_t availableHeight = screen.height() - headerHeight;
    const std::size_t topPanelHeight = availableHeight * 2 / 3;
    const std::size_t bottomPanelHeight = availableHeight - topPanelHeight;
    
    if (current_page == 0) {
        screen.drawAsciiArt(3, 3,logo + R"(

                            1. New Game
                           2.  Load Game
                           3.  Save Game
                             4.  Quit)");
    }else if (current_page == 1) {
        screen.drawText(0, 0, "Blast-It!");
        screen.drawText(0, 1, "Press 'q' to quit");

        drawEnemyWindow(screen, 0, headerHeight, leftPanelWidth, topPanelHeight, mtr, plr);
        drawPlayerWindow(screen, 0, headerHeight + topPanelHeight, leftPanelWidth, bottomPanelHeight, plr, current_choice, current_status);

        const std::size_t gridOffsetX = leftPanelWidth + 2;
        drawGridWindow(screen, grid, gridOffsetX, headerHeight, screen.width() - gridOffsetX, availableHeight, data.table);
        drawBlocksWindow(screen, gridOffsetX, headerHeight + topPanelHeight, screen.width() - gridOffsetX, bottomPanelHeight, data.lineid);

    } else if (current_page == 2) {
        screen.drawAsciiArt(3, 3, logo + R"(

                       Choose Difficulty
                            1. Easy
                           2. Medium
                            3. Hard)");
    }
    screen.present();
}
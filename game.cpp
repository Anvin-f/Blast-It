#include "game.h"
#include "windows.h"
#include "chooseblocks.h"
#include "blocks.h"
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

void Game::initialize() {
    running = true;
    data = blockInit(currentDifficulty);
    // Initialize game data
    std::fill(&data.table[0][0], &data.table[0][0] + 64, 0);
    plr = initPlayer(currentDifficulty);
    mtr = initMonster(currentDifficulty, 0);
    std::cout << "Welcome to Blast-It!" << std::endl;
}

void Game::run() {
    while (isRunning()) {
        handleInput();
        render();

        // Simple frame rate control
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Game::isRunning() const {
    return running;
}

void Game::playerLost() {
    std::cout << "Game Over! You have been defeated." << std::endl;
    running = false;
    return;
}


void Game::startBlastMode() {
    int total = current_attack_ap + current_heal_ap + current_defend_ap;
    CombatChoice choice = {current_attack_ap, current_use_special, current_heal_ap, current_defend_ap};
    rpg_state = 0;
    current_attack_ap = 0;
    current_use_special = false;
    current_heal_ap = 0;
    current_defend_ap = 0;

    if (total > plr.ap_reserve){return;}
    CombatResult result = resolveCombatTurn(plr, mtr, choice);
    if (result.monster_defeated) {
        mtr = initMonster(currentDifficulty, plr.kills);
    }
    if (result.player_defeated) {
        playerLost();
        return;
    }
    isRPGMode = false;
    data = refresh(currentDifficulty);
    data = playchoose('1');
}

void Game::startRPGMode() {
    isRPGMode = true;
    if(plr.ap_reserve == 0){
        startBlastMode();
    }
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
        running = false;
    }

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
                    current_attack_ap = std::stoi(current_input);
                } else if (rpg_state == 2) {
                    current_use_special = (current_input == "1");
                } else if (rpg_state == 3) {
                    current_heal_ap = std::stoi(current_input);
                } else if (rpg_state == 4) {
                    current_defend_ap = std::stoi(current_input);
                }
                rpg_state = 0;
            }
        }
        if (rpg_state == 0) {
            current_status = "";
        } else if (rpg_state == 1) {
            current_status = "Enter AP for Attack: " + current_input;
        } else if (rpg_state == 2) {
            current_status = "Enable Special? (1=yes, 0=no): " + current_input;
        } else if (rpg_state == 3) {
            current_status = "Enter AP for Heal: " + current_input;
        } else if (rpg_state == 4) {
            current_status = "Enter AP for Defend: " + current_input;
        }
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
            if (data.gameover) {
                startRPGMode();
            }
        }
        //if (lostinblockblast) {playerLost();return;}
    }
}


void Game::render() {
    screen.clear(' ');

    const std::size_t headerHeight = 3;
    const std::size_t leftPanelWidth = 50;
    const std::size_t availableHeight = screen.height() - headerHeight;
    const std::size_t topPanelHeight = availableHeight * 2 / 3;
    const std::size_t bottomPanelHeight = availableHeight - topPanelHeight;

    screen.drawText(0, 0, "Blast-It Game");
    screen.drawText(0, 1, "Press 'q' to quit");

    drawEnemyWindow(screen, 0, headerHeight, leftPanelWidth, topPanelHeight, mtr, plr.difficulty);
    drawPlayerWindow(screen, 0, headerHeight + topPanelHeight, leftPanelWidth, bottomPanelHeight, plr, current_attack_ap, current_use_special, current_heal_ap, current_defend_ap, current_status);

    const std::size_t gridOffsetX = leftPanelWidth + 2;
    const std::size_t gridOffsetY = headerHeight;
    drawGridWindow(screen, grid, gridOffsetX, gridOffsetY, screen.width() - gridOffsetX, availableHeight, data.table);

    drawBlocksWindow(screen, gridOffsetX, headerHeight + topPanelHeight, screen.width() - gridOffsetX, bottomPanelHeight, data.lineid);

    screen.present();
}
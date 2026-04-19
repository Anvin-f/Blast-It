#include "game.h"
#include "windows.h"
#include "chooseblocks.h"
#include "blocks.h"
#ifdef _WIN32
#include <conio.h>
#endif

Game::Game() : running(false), screen(80, 25), grid(8, 8, 3, 1) {
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
    ap = 0;
    std::cout << "Welcome to Blast-It!" << std::endl;
}

void Game::run() {
    while (isRunning()) {
        handleInput();
        update(0.0f);
        render();

        // Simple frame rate control
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Game::isRunning() const {
    return running;
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

    if (!isRPGMode && data.lineid[0] == -1 && data.lineid[1] == -1 && data.lineid[2] == -1) {
        isRPGMode = true;
    }

    if (input == 'q' || input == 'Q') {
        running = false;
    }
    if (isRPGMode) {
        // RPG mode input handling
        if (input == '1' || input == '2' || input == '3' || input == '4') {
            CombatChoice choice = {};
            if (input == '1') choice.attack_ap = 5;
            else if (input == '2') choice.use_special = true;
            else if (input == '3') choice.heal_ap = 5;
            else if (input == '4') choice.defend_ap = 5;
            CombatResult result = resolveCombatTurn(plr, mtr, ap, choice);
            std::cout << result.log_message << std::endl;
            if (result.monster_defeated) {
                mtr = initMonster(currentDifficulty, plr.kills);
            }
            isRPGMode = false;
            data = refresh(currentDifficulty);
            data = playchoose('1');
        }
    } else {
        // Blockblast mode input handling
        if (input == '1' || input == '2' || input == '3') {
            data = playchoose(input);
        } else if (input == 'w' || input == 'a' || input == 's' || input == 'd') {
            data = playwasd(input);
        } else if (input == 'c') {
            data = playconfirm();
            ap += data.point;
        }
    }
}

void Game::update(float deltaTime) {
    (void)deltaTime;
    // Update game logic here
    // For now, just print delta time
    // std::cout << "Delta time: " << deltaTime << std::endl;
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

    drawEnemyWindow(screen, 0, headerHeight, leftPanelWidth, topPanelHeight);
    drawPlayerWindow(screen, 0, headerHeight + topPanelHeight, leftPanelWidth, bottomPanelHeight);

    const std::size_t gridOffsetX = leftPanelWidth + 2;
    const std::size_t gridOffsetY = headerHeight;
    drawGridWindow(screen, grid, gridOffsetX, gridOffsetY, screen.width() - gridOffsetX, availableHeight, data.table);

    drawBlocksWindow(screen, gridOffsetX, headerHeight + topPanelHeight, screen.width() - gridOffsetX, bottomPanelHeight, data.lineid);

    screen.present();
}
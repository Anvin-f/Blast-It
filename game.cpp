#include "game.h"
#include "windows.h"

Game::Game() : running(false), screen(80, 25), grid(8, 8, 3, 1) {
}

Game::~Game() {
}

void Game::initialize() {
    running = true;
    std::cout << "Welcome to Blast-It!" << std::endl;
}

void Game::run() {
    auto lastTime = std::chrono::high_resolution_clock::now();

    while (isRunning()) {
        auto currentTime = std::chrono::high_resolution_clock::now();
        float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
        lastTime = currentTime;

        handleInput();
        update(deltaTime);
        render();

        // Simple frame rate control
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

bool Game::isRunning() const {
    return running;
}

void Game::handleInput() {
    // For simplicity, check for 'q' to quit
    if (std::cin.peek() != EOF) {
        char input;
        std::cin >> input;
        if (input == 'q' || input == 'Q') {
            running = false;
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
    system("cls"); // Windows
    screen.clear(' ');

    const std::size_t headerHeight = 3;
    const std::size_t leftPanelWidth = 22;
    const std::size_t availableHeight = screen.height() - headerHeight;
    const std::size_t topPanelHeight = availableHeight * 2 / 3;
    const std::size_t bottomPanelHeight = availableHeight - topPanelHeight;

    screen.drawText(0, 0, "Blast-It Game");
    screen.drawText(0, 1, "Press 'q' to quit");

    drawInfoWindow(screen, 0, headerHeight, leftPanelWidth, topPanelHeight);
    drawLogWindow(screen, 0, headerHeight + topPanelHeight, leftPanelWidth, bottomPanelHeight);

    const std::size_t gridOffsetX = leftPanelWidth + 2;
    const std::size_t gridOffsetY = headerHeight;
    drawGridWindow(screen, grid, gridOffsetX, gridOffsetY, screen.width() - gridOffsetX, availableHeight);

    screen.present();
}
#include "game.h"

Game::Game() : running(false) {
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
    // Update game logic here
    // For now, just print delta time
    // std::cout << "Delta time: " << deltaTime << std::endl;
}

void Game::render() {
    // Clear screen (simple way)
    system("cls"); // Windows
    std::cout << "Blast-It Game" << std::endl;
    std::cout << "Press 'q' to quit" << std::endl;
    // Render game state here
}
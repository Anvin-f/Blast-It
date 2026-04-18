#pragma once

#include <iostream>
#include <chrono>
#include <thread>

class Game {
public:
    Game();
    ~Game();

    void initialize();
    void run();
    bool isRunning() const;
    void handleInput();
    void update(float deltaTime);
    void render();

private:
    bool running;
    // Add game-specific members here
};
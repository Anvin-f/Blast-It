#pragma once

#include <iostream>
#include <chrono>
#include <thread>
#include "screen.h"
#include "grid.h"

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
    Screen screen;
    Grid grid;
};
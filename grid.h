#pragma once

#include <cstddef>

class Screen;

class Grid {
public:
    Grid(std::size_t cols = 8, std::size_t rows = 8, std::size_t cellWidth = 4, std::size_t cellHeight = 2);

    void draw(Screen& screen, std::size_t offsetX = 0, std::size_t offsetY = 0) const;

    std::size_t cols() const;
    std::size_t rows() const;
    std::size_t cellWidth() const;
    std::size_t cellHeight() const;

private:
    std::size_t cols_;
    std::size_t rows_;
    std::size_t cellWidth_;
    std::size_t cellHeight_;
};

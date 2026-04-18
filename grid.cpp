#include "grid.h"
#include "screen.h"
#include <string>
#include <algorithm>

Grid::Grid(std::size_t cols, std::size_t rows, std::size_t cellWidth, std::size_t cellHeight)
    : cols_(cols)
    , rows_(rows)
    , cellWidth_(cellWidth)
    , cellHeight_(cellHeight) {
}

std::size_t Grid::cols() const {
    return cols_;
}

std::size_t Grid::rows() const {
    return rows_;
}

std::size_t Grid::cellWidth() const {
    return cellWidth_;
}

std::size_t Grid::cellHeight() const {
    return cellHeight_;
}

void Grid::draw(Screen& screen, std::size_t offsetX, std::size_t offsetY, const int table[8][8]) const {
    for (std::size_t row = 0; row <= rows_; ++row) {
        std::size_t y = offsetY + row * (cellHeight_ + 1);
        for (std::size_t col = 0; col <= cols_; ++col) {
            std::size_t x = offsetX + col * (cellWidth_ + 1);
            screen.setPixel(x, y, '+');
            if (col < cols_) {
                for (std::size_t tx = 1; tx <= cellWidth_; ++tx) {
                    screen.setPixel(x + tx, y, '-');
                }
            }
        }
    }

    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t line = 1; line <= cellHeight_; ++line) {
            std::size_t y = offsetY + row * (cellHeight_ + 1) + line;
            for (std::size_t col = 0; col <= cols_; ++col) {
                std::size_t x = offsetX + col * (cellWidth_ + 1);
                screen.setPixel(x, y, '|');
            }
        }
    }

    // Fill the cells based on table
    for (std::size_t row = 0; row < rows_; ++row) {
        for (std::size_t col = 0; col < cols_; ++col) {
            std::size_t cellX = offsetX + col * (cellWidth_ + 1) + 1;
            std::size_t cellY = offsetY + row * (cellHeight_ + 1) + 1;
            char fillChar = ' ';
            int value = table[row][col];
            if (value == 1) {
                fillChar = '#';
            } else if (value == 2) {
                fillChar = '+';
            } else if (value == 3) {
                fillChar = '*';
            }
            // Since cellWidth_ = 3, fill the middle
            screen.setPixel(cellX + 1, cellY, fillChar);
        }
    }
}

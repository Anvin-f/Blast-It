#include "screen.h"
#include <algorithm>
#include <iostream>
#include <sstream> 

Screen::Screen(std::size_t width, std::size_t height)
    : width_(width)
    , height_(height)
    , buffer_(width * height, ' ') {
}

void Screen::resize(std::size_t width, std::size_t height) {
    width_ = width;
    height_ = height;
    buffer_.assign(width_ * height_, ' ');
}

void Screen::clear(char fill) {
    std::fill(buffer_.begin(), buffer_.end(), fill);
}

void Screen::setPixel(std::size_t x, std::size_t y, char c) {
    if (x >= width_ || y >= height_) {
        return;
    }
    buffer_[y * width_ + x] = c;
}

void Screen::drawText(std::size_t x, std::size_t y, const std::string& text) {
    if (y >= height_ || x >= width_) {
        return;
    }

    std::size_t maxLength = std::min(width_ - x, text.size());
    for (std::size_t i = 0; i < maxLength; ++i) {
        setPixel(x + i, y, text[i]);
    }
}

void Screen::drawBox(std::size_t x, std::size_t y, std::size_t width, std::size_t height, const std::string& title) {
    if (width < 2 || height < 2) {
        return;
    }

    std::size_t right = x + width - 1;
    std::size_t bottom = y + height - 1;

    setPixel(x, y, '+');
    setPixel(right, y, '+');
    setPixel(x, bottom, '+');
    setPixel(right, bottom, '+');

    for (std::size_t col = x + 1; col < right; ++col) {
        setPixel(col, y, '-');
        setPixel(col, bottom, '-');
    }

    for (std::size_t row = y + 1; row < bottom; ++row) {
        setPixel(x, row, '|');
        setPixel(right, row, '|');
    }

    if (!title.empty() && y < height_ && x + 2 < width_) {
        std::size_t titleLength = std::min(title.size(), width - 4);
        drawText(x + 2, y, title.substr(0, titleLength));
    }
}

void Screen::present() const {
    std::cout << "\x1b[H"; // move cursor to home position
    for (std::size_t row = 0; row < height_; ++row) {
        const char* rowStart = &buffer_[row * width_];
        std::cout.write(rowStart, width_);
        std::cout << '\n';
    }
    std::cout.flush();
}

std::size_t Screen::width() const {
    return width_;
}

std::size_t Screen::height() const {
    return height_;
}

void Screen::drawAsciiArt(std::size_t x, std::size_t y, const std::string& art) {
    std::stringstream ss(art);
    std::string line;
    std::size_t row = 0;

    while (std::getline(ss, line)) {
        drawText(x, y + row, line);
        row++;
    }
}

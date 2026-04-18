#include "screen.h"
#include <algorithm>
#include <iostream>

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
    if (y >= height_) {
        return;
    }

    std::size_t maxLength = std::min(width_ - x, text.size());
    for (std::size_t i = 0; i < maxLength; ++i) {
        setPixel(x + i, y, text[i]);
    }
}

void Screen::present() const {
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

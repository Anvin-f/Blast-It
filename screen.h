#pragma once

#include <cstddef>
#include <string>
#include <vector>

class Screen {
public:
    Screen(std::size_t width = 80, std::size_t height = 25);

    void resize(std::size_t width, std::size_t height);
    void clear(char fill = ' ');
    void setPixel(std::size_t x, std::size_t y, char c);
    void drawText(std::size_t x, std::size_t y, const std::string& text);
    void present() const;

    std::size_t width() const;
    std::size_t height() const;

private:
    std::size_t width_;
    std::size_t height_;
    std::vector<char> buffer_;
};

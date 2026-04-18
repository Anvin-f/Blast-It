#include "windows.h"
#include "screen.h"
#include <fstream>
#include <string>

void drawLinesWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Lines ");
    if (width < 3 || height < 3) {
        return;
    }

    std::ifstream file("line.txt");
    std::string line;
    std::size_t maxTextWidth = width > 2 ? width - 2 : 0;
    std::size_t row = 0;

    while (row < 3 && std::getline(file, line)) {
        if (row + 1 >= height) {
            break;
        }

        if (line.size() > maxTextWidth) {
            line = line.substr(0, maxTextWidth);
        }

        screen.drawText(x + 1, y + 1 + row, line);
        ++row;
    }

    for (; row < 3 && row + 1 < height; ++row) {
        screen.drawText(x + 1, y + 1 + row, std::string("", 0));
    }
}

#include "windows.h"
#include "screen.h"
#include <array>
#include <fstream>
#include <string>

void drawLinesWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const std::array<int, 3>& blocks) {
    screen.drawBox(x, y, width, height, " Lines ");
    if (width < 3 || height < 3) {
        return;
    }

    std::size_t maxTextWidth = width > 2 ? width - 2 : 0;

    if (blocks[0] >= 0) {
        std::string blockLine = "Blocks: ";
        for (std::size_t i = 0; i < blocks.size(); ++i) {
            blockLine += std::to_string(blocks[i]);
            if (i + 1 < blocks.size()) {
                blockLine += " ";
            }
        }
        if (blockLine.size() > maxTextWidth) {
            blockLine = blockLine.substr(0, maxTextWidth);
        }
        screen.drawText(x + 1, y + 1, blockLine);
        screen.drawText(x + 1, y + 2, "Press 'r' to refresh");
    } else {
        std::ifstream file("line.txt");
        std::string line;
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
            screen.drawText(x + 1, y + 1 + row, std::string());
        }
    }
}

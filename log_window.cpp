#include "windows.h"
#include "screen.h"

void drawLogWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Log ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Event Log");
        screen.drawText(x + 2, y + 2, "- Ready");
        screen.drawText(x + 2, y + 3, "- Waiting...");
    }
}

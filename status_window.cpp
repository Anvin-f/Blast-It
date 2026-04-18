#include "windows.h"
#include "screen.h"

void drawInfoWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height) {
    screen.drawBox(x, y, width, height, " Info ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Status Window");
        screen.drawText(x + 2, y + 2, "Health: 100%");
        screen.drawText(x + 2, y + 3, "Score: 0");
    }
}

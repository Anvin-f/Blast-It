#include "windows.h"
#include "screen.h"
#include <array>
#include <fstream>
#include <string>
#include "blocklist.h"
#include "grid.h"
#include "enemyArt.h"

void drawGridWindow(Screen& screen, const Grid& grid, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int table[8][8]) {
    (void)width;
    (void)height;
    grid.draw(screen, x, y, table);
}

void drawEnemyWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const Monster& monster, const Player& player) {
    screen.drawBox(x, y, width, height, " Enemy ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "Name: " + monster.name);
        screen.drawText(x + 2, y + 2, "HP: " + std::to_string(monster.hp) + "/" + std::to_string(monster.max_hp));
        screen.drawText(x + 2, y + 3, "ATK: " + std::to_string(monster.attack));
        screen.drawText(x + 2, y + 4, "Diff: " + std::to_string(player.difficulty));
    }
    const std::string& art = getEnemyArt(monster.name, player.kills);
    if (art.empty()) {
        screen.drawText(x + 2, y + 6, "No art available");
    } else {
        screen.drawAsciiArt(x + 15, y + 3, art);
    }

}

void drawPlayerWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const Player& player, const CombatChoice& choice, const std::string& status) {
    screen.drawBox(x, y, width, height, " Player Actions ");
    if (width > 4 && height > 2) {
        screen.drawText(x + 2, y + 1, "HP: " + std::to_string(player.hp) + "/" + std::to_string(player.max_hp));
        screen.drawText(x + 22, y + 1, "DEF: " + std::to_string(player.defense));
        screen.drawText(x + 2, y + 2, "AP: " + std::to_string(player.ap_reserve));
        screen.drawText(x + 22, y + 2, "KILLS: " + std::to_string(player.kills));
        if (status.size() == 0) {
            screen.drawText(x + 2, y + 4, "1. Attack: " + std::to_string(choice.attack_ap) + " AP");
            screen.drawText(x + 2, y + 6, "2. Special: " + std::string(choice.use_special ? "Yes" : "No"));
            screen.drawText(x + 22, y + 4, "3. Heal: " + std::to_string(choice.heal_ap) + " AP");
            screen.drawText(x + 22, y + 6, "4. Defend: " + std::to_string(choice.defend_ap) + " AP");
            return;
        }     
        screen.drawText(x + 2, y + 3, status.substr(0, width - 4));
    }
}


void drawBlocksWindow(Screen& screen, std::size_t x, std::size_t y, std::size_t width, std::size_t height, const int blocks[3]) {
    screen.drawBox(x, y, width, height, " Blocks ");

    for (std::size_t i = 0; i < 3; ++i) {
        if (blocks[i] < 0 ){
            continue;
        }
        std::string encodedRef = callblock(blocks[i]);
        int column = 2;
        std::string rowStr = "";
        for (int j = 0; j < encodedRef.length(); j++) {
            char c = encodedRef[j];
            if (c == '#') {
                rowStr += "#";
            } else if (c == '/') {
                screen.drawText(x + 3 + i * 10, y + column, rowStr);
                column++;
                rowStr = "";
            } else if (c == '.') {
                rowStr += " ";
            }
        }
        screen.drawText(x + 3 + i * 10, y + column, rowStr);
        screen.drawText(x + 5 + i * 10, y + 7, std::to_string(i+1));
    }
}

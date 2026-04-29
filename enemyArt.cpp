#include "enemyArt.h"

const std::string goblin_t0 =
"     ,      ,\n"
"    /(.-\"\"-.)\\\n"
"|\\  \\/      \\/  /|\n"
"| \\ / =.  .= \\ / |\n"
"\\( \\   o\\/o   / )/\n"
" \\_, '-/  \\-' ,_/\n"
"   /   \\__/   \\\n"
"   \\,___/\\___,/\n"
"     ~~    ~~";

const std::string goblin_t1 =
"        ,/|_.-^^-._|\\,\n"
"       /  /        \\  \\\n"
"      /  ( =.    .= )  \\\n"
"     /   |  \\o//\\o/  |   \\\n"
"    (    \\   ./\\.   /    )\n"
"     \\    \\  '--'  /    /\n"
"      \\    \\______/    /\n"
"       \\___/      \\___/\n"
"       /  /        \\  \\\n"
"      (__/          \\__)";

const std::string goblin_t2 =
"          .-\"\"\"\"-.\n"
"         /  ,--,  \\\n"
"        |  ((  ))  |\n"
"     ,--|   '--'   |--,\n"
"    / o |  .-==-.  | o \\\n"
"   |  /  \\ |/\\/\\| /  \\  |\n"
"   | |    `\\\\__//`    | |\n"
"    \\ \\    /,||,\\    / /\n"
"     \\ '--/ `||` \\--' /\n"
"      `---/--||--\\---'\n"
"         /   ||   \\\n"
"        (___/  \\___)";

// --- Orc tiers (Normal difficulty) ---

const std::string orc_t0 =
"      _,---,_\n"
"     /  o o  \\\n"
"    |  '. .'  |\n"
"    |   `^`   |\n"
"     \\  \\_/  /\n"
"   .--`-----`--.\n"
"   |  |     |  |\n"
"   |  |_____|  |\n"
"    \\_/     \\_/";

const std::string orc_t1 =
"          .-\"\"\"-.\n"
"        ,'  o o  ',\n"
"       /  ._.-._.  \\\n"
"      |   '_____'   |\n"
"      |  /\\/\\/\\/\\  |\n"
"     ,'   '-----'   ',\n"
"   ,/  ___       ___  \\,\n"
"  / \\ |   |     |   | / \\\n"
" |   ||   |_____|   ||   |\n"
"  \\_/ |___|     |___| \\_/\n"
"      [___]     [___]";

const std::string orc_t2 =
"             ,---.\n"
"          ,-/  o  \\-,\n"
"        ,-|   ___   |-,\n"
"       /  | ./   \\. |  \\\n"
"      /   | \\,---,/ |   \\\n"
"     /    \\  '---'  /    \\\n"
"    / __,--`-------'--,__ \\\n"
"   /,'   /\\           /\\   ',\\\n"
"  //    /  \\         /  \\    \\\\\n"
"  ||   |    |       |    |   ||\n"
"  ||   |____|       |____|   ||\n"
"  ||   /====\\       /====\\   ||\n"
"   \\\\_/      \\_____/      \\_//\n"
"    `=========================`";

// --- Dragon tiers (Hard difficulty) ---

const std::string dragon_t0 =
"            __\n"
"           / _)\n"
"    .-^^^-/ /\n"
" __/       /\n"
"<__.|_|-|_|\n"
"   ~~     ~~";

const std::string dragon_t1 =
"               __----~~~~~~~~~~~------___\n"
"            .  .   ~~//====......          __--~ ~~\n"
"   -.            \\_|//     |||\\\\  ~~~~~~::::... /~\n"
"___-==_       _-~o~  \\/    |||  \\\\            _/~~-\n"
"        `-~~     `---:::::::|||/__/      ~~==-\n"
"             _-~       `.-/_\n"
"           _-~          /  \\\n"
"         _-~            |    \\\n"
"        _-~            (      )\n"
"     _-~                \\____/";

const std::string dragon_t2 =
"                       ___====-_  _-====___\n"
"                 _--^^^#####//      \\\\#####^^^--_\n"
"              _-^##########// (    ) \\\\##########^-_\n"
"             -############//  |\\^^/|  \\\\############-\n"
"           _/############//   (@::@)   \\\\############\\_\n"
"          /#############((     \\\\//     ))#############\\\n"
"         -###############\\\\    (oo)    //###############-\n"
"        -#################\\\\  / VV \\  //#################-\n"
"       -###################\\\\/      \\//###################-\n"
"      _#/|##########/\\######(   /\\   )######/\\##########|\\#_\n"
"      |/ |#/\\#/\\#/\\/  \\#/\\##\\  |  |  /##/\\#/  \\/\\#/\\#/\\#| \\|\n"
"      `  |/  V  V  `   V  \\#\\| |  | |/#/  V   '  V  V  \\|  '\n"
"         `   `  `      `   / | |  | | \\   '      '  '   '\n"
"                          (  | |  | |  )\n"
"                         __\\ | |  | | /__\n"
"                        (vvv(VVV)(VVV)vvv)";

const std::string empty_string = "";

// returns the appropriate art depending on the current number of kills, more kills mean bigger monsters
const std::string& pickTier(const std::string& t0, const std::string& t1, const std::string& t2, int kills) {
    if (kills < 3) return t0;
    if (kills < 7) return t1;
    return t2;
}

//calls and returns pickTier based on the type of monster the user is fighting
const std::string& getEnemyArt(const std::string& name, int kills) {
    if (name == "Goblin")
      return pickTier(goblin_t0, goblin_t1, goblin_t2, kills);
    if (name == "Orc")
      return pickTier(orc_t0,    orc_t1,    orc_t2,    kills);
    if (name == "Dragon")
      return pickTier(dragon_t0, dragon_t1, dragon_t2, kills);
    return empty_string;
}
#include "chooseblocks.h"
#include "blocklist.h"
#include <string>
#include <vector>

std::string callblock(int id) {
    return blocklist[id];
}

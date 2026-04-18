#include <string>
#include <vector>

const std::string blocklist[] = {
    "#",
    "##",
    "#/#",
    "###",
    "#/#/#",
    "#./##",
    ".#/##",
    "####",
    "#/#/#/#",
    "##/##",
    "###/.#.",
    ".#/##/.#",
    ".##/##.",
    "##./.##",
    "#./#./##",
    ".#/.#/##",
    "#####",
    "#/#/#/#/#",
    "###/###/###"
};

std::string callblock(int id) {
    return blocklist[id];
}

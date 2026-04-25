#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <string>
#include <utility>
#include <vector>

// list of block available, '#' means the block is occupied, '/' means the end of a row
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

std::string callblock(int id);
std::pair<int, int> dimension(int id);

#endif
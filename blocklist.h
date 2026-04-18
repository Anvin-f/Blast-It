#ifndef BLOCKLIST_H
#define BLOCKLIST_H

#include <string>
#include <utility>
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

std::string callblock(int id);
std::pair<int, int> dimension(int id);

#endif
#ifndef BLOCKLIST_H
#define BLOCKLIST_H

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

std::string callblock(int id);

#endif
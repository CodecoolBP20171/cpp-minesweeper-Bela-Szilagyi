//
// Created by en on 2017.10.02..
//

#include "Area.h"


Area::Area() {}

void Area::setMine() { mined = true; }
bool Area::isMined() { return mined; }
void Area::setNeighbours(int n) { nrOfNeighbours = n; };
int Area::getNeighbours() { return nrOfNeighbours; };
void Area::setRevealed() {revealed = true; };
bool Area::isRevealed() { return revealed; };
void Area::setFlag() { flagged = true; };
void Area::removeFlag() { flagged = false; };
bool Area::isFlagged() { return flagged; };
std::string Area::charRepresentationOf() {
    int neighbours = this->getNeighbours();
    switch (neighbours) {
        case 0: return "\u0002"; //
        case 1: return "\033[34m1\033[1;0m"; //blue 1
        case 2: return "\033[32m2\033[1;0m"; //green2
        case 3: return "\033[31m3\033[1;0m"; //red3
        case 4: return "\033[33m4\033[1;0m"; //yellow4
        case 5: return "\033[36m5\033[1;0m"; //cyan5
        case 6: return "\033[35m6\033[1;0m"; //magenta6
        case 7: return "7"; //black7
        case 8: return "\033[1m\033[30m8\033[1;0m"; //bold black8
    }
}


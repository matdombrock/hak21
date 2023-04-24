#pragma once
#include <iostream>
#include <vector>
#include "Dice.h"

std::vector<std::string> names = {
    "Xenex",
    "Alpha",
    "Beta",
    "KRX"
};
Dice dice;

class RandomName{
public:
    static std::string generate(){
        std::string first = names[dice.roll(names.size())-1];
        std::string last = std::to_string(dice.roll(999));
        return first + "-" + last;
    }
private:
};
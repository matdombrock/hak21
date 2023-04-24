#pragma once
#include <iostream>
#include "RandomName.h"

class Entity{
public:
    Entity(){};
    void setName(std::string newName){
        name = newName;
    }
    void randomizeName(){
        name = RandomName::generate();
    }
    void initMatch(){
        sum = 0;
        holding = false;
    }
    int defend(int attackSum){
        int dmg = attackSum - sum;
        ep -= dmg;
        return dmg;
    }
    std::string name = "Unknown Entity";
    int ep = 10;
    int sum = 0;
    int burst = 21;
    bool holding = false;
};
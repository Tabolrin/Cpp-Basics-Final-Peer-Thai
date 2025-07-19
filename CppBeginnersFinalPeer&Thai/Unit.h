#pragma once
#include <string>

using namespace std;

class Unit abstract
{
protected:
    int maxHp;
    int hp;
    int normalDmg;
    int elementalDmg;
    string element;

public:
    Unit(int maxHp, int normalDmg, int elementalDmg, string element);
};


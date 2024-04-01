#pragma once
#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
class AlienSoldier :
    public Unit
{

public:
    AlienSoldier(Game* game,int id, double health, UnitType type, int joinTime, double attackPower, int attackCapacity) :
        Unit(game, id, health, type, joinTime, attackPower, attackCapacity) {}

    void Attack();
};

#endif // !ALIEN_SOLDIER_H

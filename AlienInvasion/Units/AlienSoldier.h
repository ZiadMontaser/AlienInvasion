#pragma once
#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
class AlienSoldier :
    public Unit
{

public:
    AlienSoldier(Game* game,int id, double health, int joinTime, double attackPower, int attackCapacity) :
        Unit(game, id, health, ALIEN_SOLDIER, joinTime, attackPower, attackCapacity) {}

    void Attack();
};

#endif 

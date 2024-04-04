#pragma once
#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"
class EarthSoldier :
    public Unit
{

public:
    EarthSoldier(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity):
        Unit(game, id, health, EARTH_SOLDIER, joinTime, attackPower, attackCapacity) {}

    void Attack();
};

#endif
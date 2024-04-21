#pragma once
#ifndef EARTH_SOLDIER_H
#define EARTH_SOLDIER_H

#include "Unit.h"
class EarthSoldier :
    public Unit
{

    int TimeSpentUML=0;
public:
    EarthSoldier(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity):
        Unit(game, id, health, EARTH_SOLDIER, joinTime, attackPower, attackCapacity) {}

    void Attack();
    void ResetHealTime() { TimeSpentUML = 0; }
    int GetTimeHeal() { return TimeSpentUML; }
    void SetTimeHeal(int T) { TimeSpentUML = T; }
};

#endif
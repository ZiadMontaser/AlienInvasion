#pragma once
#include "Unit.h"
class HealUnit :
    public Unit

{
public:
    HealUnit(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity) :
      Unit(game, id, health, HEALUNIT, joinTime, attackPower, attackCapacity) {}
    void Attack();
    void KILL();
};


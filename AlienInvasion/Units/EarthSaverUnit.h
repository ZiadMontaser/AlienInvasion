#pragma once
#include "Unit.h"
class Game;

class EarthSaverUnit :
    public Unit
{

public:
    EarthSaverUnit(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity) :
        Unit(game, id, health, SAVERUNIT, joinTime, attackPower, attackCapacity) {}

    void Attack();
    void KILL();
};
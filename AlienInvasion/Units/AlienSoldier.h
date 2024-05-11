#pragma once
#ifndef ALIEN_SOLDIER_H
#define ALIEN_SOLDIER_H

#include "Unit.h"
class AlienSoldier :
    public Unit
{
    int infectionProb;
public:
    AlienSoldier(Game* game,int id, double health, int joinTime, double attackPower, int attackCapacity, int infectionProb) :
        Unit(game, id, health, ALIEN_SOLDIER, joinTime, attackPower, attackCapacity), infectionProb(infectionProb) {}

    void Attack();
};

#endif 

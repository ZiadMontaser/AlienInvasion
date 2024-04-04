#pragma once

#include "Unit.h"

class Monester : public Unit {
public:
	Monester(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, MONSTER, joinTime, attackPower, attackCapacity) {}

	void Attack() {} /// to do 
};
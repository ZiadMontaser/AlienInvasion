#pragma once

#include "Unit.h"

class Monester : public Unit {
	int infectionProb;
public:
	Monester(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity, int infectionProb) :
		Unit(game, id, health, MONSTER, joinTime, attackPower, attackCapacity), infectionProb(infectionProb) {}

	void Attack(); /// to do 
};
#pragma once

#include "Unit.h"

class EarthGunnery : public Unit {
public:
	EarthGunnery(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, GUNNERY, joinTime, attackPower, attackCapacity) {}


	void Attack() {} /// to do 
};
#pragma once

#include "Unit.h"

class Drone : public Unit {
public:
	Drone(Game* game, int id, double health, int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, DRONE, joinTime, attackPower, attackCapacity) {}


	void Attack() {} /// to do 
};


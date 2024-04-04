#pragma once
#include"Unit.h"

class EarthTank : public Unit {

public :
	EarthTank(Game* game, int id, double health , int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, TANK , joinTime, attackPower, attackCapacity) {}

	void Attack();
};
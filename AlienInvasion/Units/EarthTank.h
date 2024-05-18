#pragma once
#include"Unit.h"

class EarthTank : public Unit {

	int TimestartUML = 0;
public :
	EarthTank(Game* game, int id, double health , int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, TANK , joinTime, attackPower, attackCapacity) {}

	void Attack();
	void ResetHealTime() { TimestartUML = 0; }
	int GetTimeStartHeal() { return TimestartUML; }
	void SetTimeHeal(int T) { TimestartUML = T; }
};
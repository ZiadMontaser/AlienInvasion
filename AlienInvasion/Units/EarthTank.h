#pragma once
#include"Unit.h"

class EarthTank : public Unit {

	int TimeSpentUML = 0;
public :
	EarthTank(Game* game, int id, double health , int joinTime, double attackPower, int attackCapacity) :
		Unit(game, id, health, TANK , joinTime, attackPower, attackCapacity) {}

	void Attack();
	void ResetHealTime() { TimeSpentUML = 0; }
	int GetTimeHeal() { return TimeSpentUML; }
	void SetTimeHeal(int T) { TimeSpentUML = T; }
};
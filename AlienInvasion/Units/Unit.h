#pragma once
#ifndef UNIT_H
#define UNIT_H

//#include "../Game.h"
class Game;

enum class UnitType
{
	EARTH_SOLDIER,
	TANK,
	GUNNERY,
	ALIEN_SOLDIER,
	MONSTER,
	DRONE,
};

class Unit {
protected:
	Game* pGame;

	UnitType type;
	int id;
	double health;
	int joinTime;
	int attackPower;
	int attackCapacity;


public:
	Unit(Game* game ,int id, double health, UnitType type, int joinTime, double attackPower, int attackCapacity);

	virtual void Attack() = 0;

	void Damage(double attackPower) {
		health -= attackPower;

		if (health <= 0) {
			//TODO: Game->ReportDeadPlayer();
		}
	}

	UnitType GetType() { return type; };
	double GetHealth() { return health; };
	double GetPower() { return attackPower; };
	int GetCapacity() { return attackCapacity; };
};

#endif // !UNIT_H

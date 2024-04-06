#pragma once
#ifndef UNIT_H
#define UNIT_H
#include <cmath>
//#include "../Game.h"
class Game;

enum UnitType
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
	Unit(Game* game, int id, double health, UnitType type, int joinTime, double attackPower, int attackCapacity) {

		pGame = game;
		this->id = id;
		this->health = health;
		this->type = type;
		this->joinTime = joinTime;
		this->attackPower = attackPower;
		this->attackCapacity = attackCapacity;

	}

	virtual void Attack() = 0;

	void Damage(double attackerHealth , double attackerPower) {
		double Thedamage = (attackerPower * (attackerHealth / 100)) / sqrt(health);

		health -= Thedamage;

		if (health <= 0) {

			/// error here 
			//pGame->ReportDeadPlayer(this);
		}
	}

	UnitType GetType() { return type; };
	double GetHealth() { return health; };
	double GetPower() { return attackPower; };
	int GetCapacity() { return attackCapacity; };
};

#endif // !UNIT_H

#pragma once
#ifndef UNIT_H
#define UNIT_H
#include <cmath>
#include <iostream>
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

	void Damage(double attackerHealth, double attackerPower);
	void Heal(double HUpower, double Huhealth);
	UnitType GetType() { return type; };
	int GetID() { return id; };
	double GetHealth() { return health; };
	double GetPower() { return attackPower; };
	int GetCapacity() { return attackCapacity; };

	bool IsDead() { return health <= 0; }
};

std::ostream& operator<<(std::ostream& out, Unit* unit);

#endif // !UNIT_H

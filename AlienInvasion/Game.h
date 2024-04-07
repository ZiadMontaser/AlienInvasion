#pragma once

#ifndef GAME_H
#define GAME_H


#include "Armys/AlienArmy.h"
#include "Armys/EarthArmy.h"

class Game
{
	AlienArmy alienArmy;
	EarthArmy earthArmy;
	LinkedQueue<Unit* > KilledList;

	int currentTimeStep = 0;

public:

	void StartSimulation();
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	void ReportDeadUnit(Unit*);

	void Print() const;
};

#endif // !GAME_H=
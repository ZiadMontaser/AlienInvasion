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

public:

	void StartSimulation();
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	void ReportDeadPlayer(Unit*);
};

#endif // !GAME_H=
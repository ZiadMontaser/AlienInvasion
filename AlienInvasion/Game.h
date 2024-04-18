#pragma once

#ifndef GAME_H
#define GAME_H

#include "UnitGenerator.h"
#include "Armys/AlienArmy.h"
#include "Armys/EarthArmy.h"
#include <string>

enum class UIMode {
	Interactive = 0,
	Silent = 1
};

class Game
{
	AlienArmy* alienArmy;
	EarthArmy* earthArmy;
	LinkedQueue<Unit* > KilledList;

	string inputFileDir;
	UIMode uiMode = UIMode::Interactive;

	int currentTimeStep = 0;

public:
	Game();

	void StartSimulation();
	void ReadinputFile(UnitGenerator&);
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	void ReportDeadUnit(Unit*);
	void HandleUI();
	void Print() const;
	void PrintSilentMessages() const;
	UIMode GetUIMode() const;
};

#endif // !GAME_H=
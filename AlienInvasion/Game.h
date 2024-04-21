#pragma once

#ifndef GAME_H
#define GAME_H

#include "UnitGenerator.h"
#include "Armys/AlienArmy.h"
#include "Armys/EarthArmy.h"
#include <string>
#include <Windows.h>

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN

enum class UIMode {
	Interactive = 0,
	Silent = 1
};
enum EndBattle {
	DRAW,
	ALIENWON,
	EARTHWON
};
class Game
{
	AlienArmy* alienArmy;
	EarthArmy* earthArmy;
	LinkedQueue<Unit* > KilledList;
	EndBattle endbattle = DRAW;
	string inputFileDir;
	string outputFileDir;
	UIMode uiMode = UIMode::Interactive;

	int currentTimeStep = 0;

public:
	Game();

	void StartSimulation();
	void ReadinputFile(UnitGenerator&);
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	void ReportDeadUnit(Unit*);
	int GetTimeStamp();
	void ReportHealedUnit(Unit*);
	void HandleUI();
	void outfile();
	void Print() const;
	void PrintSilentMessages() const;
	UIMode GetUIMode() const;
};

#endif // !GAME_H=
#pragma once

#ifndef GAME_H
#define GAME_H

#include "UnitGenerator.h"
#include "Armys/AlienArmy.h"
#include "Armys/EarthArmy.h"
#include <string>
#include <Windows.h>

#define ESC "\x1b"
#define CSI "\x1b["

#define FOREGROUND_WHITE FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_GREEN
#define FOREGROUND_YELLOW FOREGROUND_RED | FOREGROUND_GREEN
enum class FocusMode {
	InFileInput,
	OutFileInput,
	ModeSelection
};
enum class UIMode {
	Interactive = 0,
	Silent = 1
};
enum EndBattle {
	DRAW,
	ALIENWON,
	EARTHWON,
	CONTINUE
};
class Game
{
	AlienArmy* alienArmy;
	EarthArmy* earthArmy;
	LinkedQueue<Unit* > KilledList;
	EndBattle endbattle = CONTINUE;
	string inputFileDir;
	string outputFileDir;
	UIMode uiMode = UIMode::Interactive;

	int InfectionThreshold;
	int currentTimeStep = 0;


	bool playsound = false;
public:
	Game();

	//Getters
	AlienArmy* GetAlienArmy();
	EarthArmy* GetEarthArmy();
	UIMode GetUIMode() const;

	//Game Functions
	void StartSimulation();
	void ReportDeadUnit(Unit*);
	int GetTimeStamp();
	void ReportHealedUnit(Unit*);
	bool CanAttack();
	EndBattle CheckForEndSimulation();

	// UI functions
	void HandleUI();
	void AnimateLogo();
	void PrintMainMenue(string file, string ofile, UIMode mode, FocusMode focusMode);

	void Print() const;
	void PrintSilentMessages() const;


	// Read / Write functions
	void ReadinputFile(UnitGenerator&);
	void outfile();
};

#endif // !GAME_H=
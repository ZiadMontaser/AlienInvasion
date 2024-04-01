#pragma once
#include "Game.h"
#include <string>

class UnitGenerator
{
	Game* pGame;
	int numberOfUnits;
	int ES, ET, EG, AS, AM, AD;
	int Prob;

	int EarthPowerUpper,    EarthPowerLower;
	int EarthHealthUpper,   EarthHealthLower;
	int EarthCapacityUpper, EarthCapacityLower;


	int AlienPowerUpper,    AlienPowerLower;
	int AlienHealthUpper,   AlienHealthLower;
	int AlienCapacityUpper, AlienCapacityLower;

public:
	UnitGenerator(Game* game);
	void ReadParameters(std::string input);
	void GenerateUnits();
};


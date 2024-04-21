#pragma once
//#include "Game.h"
#include <string>
class Game;
class UnitGenerator
{
	Game* pGame;
	int numberOfUnits;
	int ES, ET, EG, EHU, AS, AM, AD;
	int Prob;

	int EarthPowerUpper,    EarthPowerLower;
	int EarthHealthUpper,   EarthHealthLower;
	int EarthCapacityUpper, EarthCapacityLower;

	int AlienPowerUpper,    AlienPowerLower;
	int AlienHealthUpper,   AlienHealthLower;
	int AlienCapacityUpper, AlienCapacityLower;

	int LastIDearth = 0;
	int LastIDaliens = 2000;

	int numberGEN(int min, int max);
public:
	UnitGenerator(Game* game);
	void ReadParameters(int ,int , int , int ,int,int ,  int , int ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int ,int,int);
	void GenerateEarth();
	void GenerateAlien();

};


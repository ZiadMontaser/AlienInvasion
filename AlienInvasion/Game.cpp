#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
AlienArmy* Game::GetAlienArmy() { return &alienArmy; }
EarthArmy* Game::GetEarthArmy() { return &earthArmy; }



void Game::StartSimulation() {

	UnitGenerator generator(this);
	generator.ReadParameters("./input.txt");

	while (true)
	{
		earthArmy.Attack();
		alienArmy.Attack();
		generator.GenerateUnits();

		Sleep(1000 * 3); // 3 seconds

	}
}
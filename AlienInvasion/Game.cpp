#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
AlienArmy* Game::GetAlienArmy() { return &alienArmy; }
EarthArmy* Game::GetEarthArmy() { return &earthArmy; }

void Game::ReportDeadPlayer(Unit* dead)
{
	KilledList.enqueue(dead);
}



void Game::StartSimulation() {

	UnitGenerator generator(this);
	generator.ReadParameters();

	while (true)
	{
		earthArmy.Attack();
		alienArmy.Attack();
		generator.GenerateEarth();
		generator.GenerateAlien();

		Sleep(1000 * 3); // 3 seconds

	}
}
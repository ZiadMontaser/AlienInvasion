#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>

Game::Game() {
	alienArmy = new AlienArmy;
	earthArmy = new EarthArmy(this);
}

AlienArmy* Game::GetAlienArmy() { return alienArmy; }
EarthArmy* Game::GetEarthArmy() { return earthArmy; }

void Game::ReportDeadUnit(Unit* dead)
{
	KilledList.enqueue(dead);
}



void Game::StartSimulation() {

	UnitGenerator generator(this);
	generator.ReadParameters();

	while (true)
	{
		system("CLS");

		generator.GenerateEarth();
		generator.GenerateAlien();

		Print();

		cout << endl;
		cout << "===========" << " Units Fighting at Current Timestep " << "===========" << endl;

		earthArmy->Attack();
		alienArmy->Attack();

		do
		{
			cout << '\n' << "Press enter to continue...";
		} while (cin.get() != '\n');

		currentTimeStep++;
	}

}

void Game::Print() const {
	cout << "Current Timestep " << currentTimeStep << endl;
	earthArmy->Print();
	alienArmy->Print();

	cout << "===========" << " Killed Units " << "===========" << endl;

	cout << KilledList.getCount() << " units ";
	KilledList.print();

	cout.clear();
}
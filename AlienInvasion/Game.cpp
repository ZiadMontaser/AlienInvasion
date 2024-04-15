#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
#include <cmath>
#include <conio.h>

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

#define ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define ESCAPE 8

void Game::HandleUI() {
	cout << "Input File Name: (testfile.txt)";
	string file;

	char c = 0;
	do {
		c = _getch();
		if (c == ENTER)
			break;
		
		if (c == ESCAPE)
			file.erase(file.length() - 1);
		else
			file += c;

		system("CLS");
		cout << "Input File Name: " << file << endl;

	} while (true);
	file = file.empty() ? "testfile.txt" : file + ".txt";
	inputFileDir = file;

	int modeIndex = 0;
	do{
		if (c == KEY_UP) {
			modeIndex--;
			modeIndex = max(modeIndex, 0);
		}
		else if (c == KEY_DOWN) {
			modeIndex++;
			modeIndex = min(modeIndex, 1);
		}

		system("CLS");

		cout << "Input File Name: " << file << endl;
		cout << "Simulation mode:" << endl;
		cout << (modeIndex == (int) UIMode::Interactive ? ">" : " ") << " Interactive" << endl;
		cout << (modeIndex == (int) UIMode::Silent     ? ">" : " ")  << " Silent"      << endl;
	} while ((c = _getch()) != ENTER);
	uiMode = (UIMode) modeIndex;
}

UIMode Game::GetUIMode() const {
	return uiMode;
}


void Game::StartSimulation() {


	UnitGenerator generator(this);
	generator.ReadParameters(inputFileDir);

	if (uiMode == UIMode::Silent) PrintSilentMessages();

	while (true)
	{

		generator.GenerateEarth();
		generator.GenerateAlien();

		
		if (uiMode == UIMode::Interactive) {
			system("CLS");

			Print();

			cout << endl;
			cout << "===========" << " Units Fighting at Current Timestep " << "===========" << endl;
		}

		earthArmy->Attack();
		alienArmy->Attack();

		if (uiMode == UIMode::Interactive) {
			do
			{
				cout << '\n' << "Press enter to continue...";
			} while (cin.get() != '\n');
		}

		currentTimeStep++;
	}

}

void Game::PrintSilentMessages() const {
	system("CLS");
	cout << "Silent Mode" << endl;
	cout << "Simulation starts...";
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
#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <fstream>

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
	ReadinputFile(generator);

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

void Game::ReadinputFile(UnitGenerator& generator)
{

	string Filename = "testfile.txt";

#ifndef _DEBUG
	cout << "Please enter the file name you would like to use for unit Generation: ";
	cin >> Filename;
#endif // DEBUG

	fstream inputfile;

	inputfile.open(Filename.c_str(), ios::in);
	if (inputfile.is_open()) {

		int temp;
		int numberOfUnits;
		int ES, ET, EG;
		int AS, AM, AD;
		int Prob;

		inputfile >> numberOfUnits;
		inputfile >> ES >> ET >> EG;
		inputfile >> AS >> AM >> AD;
		inputfile >> Prob;

		inputfile >> temp;
		int EarthPowerLower = abs(temp);
		inputfile >> temp;
		int EarthPowerUpper = abs(temp);


		inputfile >> temp;
		int EarthHealthLower = abs(temp);
		inputfile >> temp;
		int EarthHealthUpper = abs(temp);


		inputfile >> temp;
		int EarthCapacityLower = abs(temp);
		inputfile >> temp;
		int EarthCapacityUpper = abs(temp);



		inputfile >> temp;
		int AlienPowerLower = abs(temp);
		inputfile >> temp;
		int AlienPowerUpper = abs(temp);

		inputfile >> temp;
		int AlienHealthLower = abs(temp);
		inputfile >> temp;
		int AlienHealthUpper = abs(temp);

		inputfile >> temp;
		int AlienCapacityLower = abs(temp);
		inputfile >> temp;
		int AlienCapacityUpper = abs(temp);


		generator.ReadParameters(numberOfUnits,
			ES, ET, EG,
			AS, AM, AD,
			Prob,
			EarthPowerLower,
			EarthPowerUpper,
			EarthHealthLower,
			EarthHealthUpper,
			EarthCapacityLower,
			EarthCapacityUpper,
			AlienPowerLower,
			AlienPowerUpper,
			AlienHealthLower,
			AlienHealthUpper,
			AlienCapacityLower,
			AlienCapacityUpper);

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
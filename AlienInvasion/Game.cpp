#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <fstream>


Game::Game() {
	alienArmy = new AlienArmy(this);
	earthArmy = new EarthArmy(this);
}

AlienArmy* Game::GetAlienArmy() { return alienArmy; }
EarthArmy* Game::GetEarthArmy() { return earthArmy; }

void Game::ReportDeadUnit(Unit* dead)
{
	dead->SetDeathTime(GetTimeStamp());
	KilledList.enqueue(dead);
}

int Game::GetTimeStamp()
{
	return currentTimeStep;
}

void Game::ReportHealedUnit(Unit* healed)
{
	EarthSoldier* es = dynamic_cast<EarthSoldier*>(healed);
	EarthTank* et = dynamic_cast<EarthTank*>(healed);
	if (es)
		earthArmy->AddSoldier(es);
	else if (et)
		earthArmy->AddTank(et);
}

#define ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define ESCAPE 8

void PrintMainMenue(string file, string ofile, UIMode mode, bool isInputOne, bool isInputTwo, bool isSelectionMenu) {

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW);
	system("CLS");
	cout << R"(
  ____  _      ____    ___  ____       ____  ____   __ __   ____  _____ ____  ___   ____  
 /    || |    |    |  /  _]|    \     |    ||    \ |  |  | /    |/ ___/|    |/   \ |    \ 
|  o  || |     |  |  /  [_ |  _  |     |  | |  _  ||  |  ||  o  (   \_  |  ||     ||  _  |
|     || |___  |  | |    _]|  |  |     |  | |  |  ||  |  ||     |\__  | |  ||  O  ||  |  |
|  _  ||     | |  | |   [_ |  |  |     |  | |  |  ||  :  ||  _  |/  \ | |  ||     ||  |  |
|  |  ||     | |  | |     ||  |  |     |  | |  |  | \   / |  |  |\    | |  ||     ||  |  |
|__|__||_____||____||_____||__|__|    |____||__|__|  \_/  |__|__| \___||____|\___/ |__|__|                                                                  
)";

	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "Input File Name: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	cout << (file.empty() ? "(testfile.txt)" : file) << endl;
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
	cout << "Output File Name: ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	cout << (ofile.empty() ? "(output.txt)" : ofile) << endl;

	if (isInputOne) {
		COORD pos = { 17 + file.length(), 9 };
		SetConsoleCursorPosition(hConsole, pos);
	}
	else if (isInputTwo) {
		COORD pos = { 17 + file.length(), 10 };
		SetConsoleCursorPosition(hConsole, pos);
	}

	if (isSelectionMenu) {
		SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
		cout << "Simulation mode:" << endl;
		SetConsoleTextAttribute(hConsole, mode == UIMode::Interactive ? FOREGROUND_YELLOW : FOREGROUND_WHITE);
		cout << (mode == UIMode::Interactive ? ">" : " ") << " Interactive" << endl;
		SetConsoleTextAttribute(hConsole, mode == UIMode::Silent ? FOREGROUND_YELLOW : FOREGROUND_WHITE);
		cout << (mode == UIMode::Silent ? ">" : " ") << " Silent" << endl;
	}
}

void Game::HandleUI() {

	PrintMainMenue(inputFileDir, outputFileDir, uiMode, true, false, false);

	string file;
	string ofile;
	char c = 0;
	char co = 0;
	do {
		c = _getch();
		if (c == ENTER)
			break;

		if (c == ESCAPE) {
			if (!file.empty()) {
				file.erase(file.length() - 1);
			}
		}
		else
			file += c;

		PrintMainMenue(file, ofile, uiMode, true, false, false);

	} while (true);

	PrintMainMenue(file, ofile, uiMode, false, true, false);
	do {
		co = _getch();
		if (co == ENTER)
			break;

		if (co == ESCAPE) {
			if (!ofile.empty()) {
				ofile.erase(ofile.length() - 1);
			}
		}
		else
			ofile += co;

		PrintMainMenue(file, ofile, uiMode, false, true, false);

	} while (true);
	file = file.empty() ? "testfile.txt" : file + ".txt";
	inputFileDir = file;
	ofile = ofile.empty() ? "output.txt" : ofile + ".txt";
	outputFileDir = ofile;
	int modeIndex = 0;
	do {
		if (c == KEY_UP) {
			modeIndex--;
			modeIndex = max(modeIndex, 0);
		}
		else if (c == KEY_DOWN) {
			modeIndex++;
			modeIndex = min(modeIndex, 1);
		}

		PrintMainMenue(file, ofile, (UIMode)modeIndex, false, false, true);
	} while ((c = _getch()) != ENTER);
	uiMode = (UIMode)modeIndex;
}

void Game::outfile()
{
	fstream outfile;
	int EsDestrCount = 0, EtDestrCount = 0, EgDestrCount = 0;
	int AsDestrCount = 0, AmDestrCount = 0, AdDestrCount = 0;
	int EDf = 0, EDb = 0, EDd = 0;
	int ADf = 0, ADb = 0, ADd = 0;

	outfile.open(outputFileDir.c_str(), ios::out);
	if (outfile.is_open())
	{
		string table = "Td\tID\tTj\tDf\tDd\tDb\n";
		outfile << table;
		Unit *temp;
		while (KilledList.dequeue(temp))
		{
			if (dynamic_cast<EarthSoldier*>(temp) || dynamic_cast<EarthTank*>(temp) || dynamic_cast<EarthGunnery*>(temp))
			{
				EDf += temp->getAttackDelay();
				EDb += temp->getBattleTime();
				EDd += temp->getDestructDelay();
			}
			else if (dynamic_cast<AlienSoldier*>(temp) || dynamic_cast<Drone*>(temp) || dynamic_cast<Monester*>(temp))
			{
				ADf += temp->getAttackDelay();
				ADb += temp->getBattleTime();
				ADd += temp->getDestructDelay();
			}
			if (dynamic_cast<EarthSoldier*>(temp))
				EsDestrCount++;
			else if (dynamic_cast<EarthTank*>(temp))
				EtDestrCount++;
			else if (dynamic_cast<EarthGunnery*>(temp))
				EgDestrCount++;
			else if (dynamic_cast<AlienSoldier*>(temp))
				AsDestrCount++;
			else if (dynamic_cast<Drone*>(temp))
				AdDestrCount++;
			else if (dynamic_cast<Monester*>(temp))
				AmDestrCount++;
			outfile << temp->GetDeathTime() << "\t" << temp->GetID() << "\t" << temp->getJoinTime() << "\t" << temp->getAttackedTime()
				<< "\t" << temp->getDestructDelay() << "\t" << temp->getBattleTime() << "\n";
		}
		outfile << "\n=============================================================\n";
		int Es_total = EsDestrCount + earthArmy->GetSoldiersCount();
		int Et_total = EtDestrCount + earthArmy->GetTankCount();
		int Eg_total = EgDestrCount + earthArmy->GetGunneryCount();
		int total_earth = Es_total + Et_total + Eg_total;
		int total_desEarth = EsDestrCount + EtDestrCount + EgDestrCount;

		int As_total = AsDestrCount + alienArmy->GetSoldiersCount();
		int Ad_total = AdDestrCount + alienArmy->GetDroneCount();
		int Am_total = AmDestrCount + alienArmy->GetMonstersCount();
		int total_alien = As_total + Ad_total + Am_total;
		int total_desAlien = AsDestrCount + AdDestrCount + AmDestrCount;
		string str;

		if (endbattle == EARTHWON)
			outfile << "\nEarth Army Won The Battle\n";
		else if (endbattle == ALIENWON)
			outfile << "\nAlien Army Won The Battle\n";
		else if (endbattle == DRAW)
			outfile << "\nThe Battle Ended With Draw\n";
		outfile << "\n=============================================================\n";
		
		int EsAvg = 0, EgAvg = 0, EtAvg = 0, AsAvg = 0, AmAvg = 0, AdAvg = 0;
		if (Es_total) EsAvg = (double)(EsDestrCount / Es_total) * 100.0;
		if (Et_total) EtAvg = (double)(EtDestrCount / Et_total) * 100.0;
		if (Eg_total) EgAvg = (double)(EgDestrCount / Eg_total) * 100.0;
		if (As_total) AsAvg = (double)(AsDestrCount / As_total) * 100.0;
		if (Am_total) AmAvg = (double)(AmDestrCount / Am_total) * 100.0;
		if (Ad_total) AdAvg = (double)(AdDestrCount / Ad_total) * 100.0;
		
		outfile << "\nEarth Statistics:\nES Count-> " << Es_total << "\nET Count-> " << Et_total << "\nEG Count-> "	<< Eg_total << "\n";
		if (Es_total)
			outfile << "\nES_destructed:ES_total-> " << EsAvg << "%\n";
		else
			outfile << "\nThere is no Earth Soldiers\n";
		if (Eg_total)
			outfile << "EG_destructed:EG_total-> " << EgAvg << "%\n";
		else
			outfile << "There is no Earth Gunnerys\n";
		if (Et_total)
			outfile << "ET_destructed:ET_total-> " << EtAvg << "%\n";
		else
			outfile << "There is no Earth Tanks\n";
		if (total_desEarth)
		{
			outfile << "\nTotal Earth Units : Total Destructed Earth Units-> " << (double)(total_earth / total_desEarth) * 100.0 << "%\n";
			outfile << "\nAverage of Df-> " << (double)(EDf / total_desEarth) << "\nAverage of Db-> " << (double)(EDb / total_desEarth)
				<< "\nAverage of Dd-> " << (double)(EDd / total_desEarth) << "\n";
		}
		else
			outfile << "\nThere is no Destructed Earth Army\n";

		if (EDb)
		{
			outfile << "\nDf / Db = " << (double)(EDf / EDb) * 100.0 << "%\nDd / Db = "
				<< (double)(EDd / EDb) * 100.0 << "%\n";
		}
		else
			outfile << "total Db = 0";

		outfile << "\n=============================================================\n";
		outfile << "\nAlien Statistics:\nAS Count-> " << As_total << "\nAD Count-> " << Ad_total << "\nAM Count-> " << Am_total << "\n";
		if (As_total)
			outfile << "\nAS_destructed:AS_total-> " << AsAvg << "%\n";
		else
			outfile << "\nThere is no Alien Soldiers\n";
		if (Ad_total)
			outfile << "AD_destructed:AD_total-> " << AdAvg << "%\n";
		else
			outfile << "There is no Alien Drone\n";
		if (Am_total)
			outfile << "AM_destructed:AM_total-> " << AmAvg << "%\n";
		else
			outfile << "There is no Alien Monsters\n";
		if (total_desAlien)
		{
			outfile << "\nTotal Alien Units : Total Destructed Alien Units-> " << (double)(total_alien / total_desAlien) * 100.0 << "%\n";
			outfile << "\nAverage of Df-> " << (double)(ADf / total_desAlien) << "\nAverage of Db-> " << (double)(ADb / total_desAlien)
				<< "\nAverage of Dd-> " << (double)(ADd / total_desAlien) << "\n";
		}
		else
			outfile << "\nThere is no Destructed Alien Army\n";
		if (ADb)
		{
			outfile << "\nDf / Db = " << (double)(ADf / ADb) * 100.0 << "%\nDd / Db = "
				<< (double)(ADd / ADb) * 100.0 << "%\n";
		}
		else
			outfile << "total Db = 0";
		outfile.close();
	}
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
		if (currentTimeStep >= 40 && (earthArmy->GetEarthCount() == 0 || alienArmy->GetAlienCount() == 0))
		{
			if (uiMode == UIMode::Interactive)
			{
				if (earthArmy->GetEarthCount() == 0 && alienArmy->GetAlienCount() == 0)
				{
					endbattle = DRAW;
					cout << "Battle ended in draw";
				}
				else if (earthArmy->GetEarthCount() != 0 && alienArmy->GetAlienCount() == 0)
				{
					endbattle = EARTHWON;
					cout << "Earth Army Won";
				}
				else
				{
					endbattle = ALIENWON;
					cout << "ALien Army Won";
				}
			}
			break;
		}
		if (uiMode == UIMode::Interactive) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

			SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
			cout << '\n' << "Press enter to continue...";
			while (_getch() != ENTER);
		}

		currentTimeStep++;
	}
	outfile();

}

void Game::ReadinputFile(UnitGenerator& generator)
{

	fstream inputfile;

	inputfile.open(inputFileDir.c_str(), ios::in);
	if (inputfile.is_open()) {

		int temp;
		int numberOfUnits;
		int ES, ET, EG,EHU;
		int AS, AM, AD;
		int Prob;

		inputfile >> numberOfUnits;
		inputfile >> ES >> ET >> EG>>EHU;
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
			ES, ET, EG,EHU,
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
	cout << "Simulation ends, output file is created: " << outputFileDir << endl;
}

void Game::Print() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW);
	cout << "Current Timestep " << currentTimeStep << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	earthArmy->Print();
	alienArmy->Print();

	cout << "===========" << " Killed Units " << "===========" << endl;

	cout << KilledList.getCount() << " units ";
	KilledList.print();

	cout.clear();
}
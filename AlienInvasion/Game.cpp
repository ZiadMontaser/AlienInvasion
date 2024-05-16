#include "Game.h"

#include <Windows.h>
#include <cmath>
#include <conio.h>
#include <fstream>
#include <mmsystem.h>

#include "UnitGenerator.h"
#include "UI_helpers.h"
#include <filesystem>

#pragma comment(lib,"winmm.lib")

#define ENTER 13
#define KEY_UP 72
#define KEY_DOWN 80
#define ESCAPE 8


Game::Game() {
	alienArmy = new AlienArmy(this);
	earthArmy = new EarthArmy(this);
}

  ////////////////
 //   Getters  //
////////////////
AlienArmy* Game::GetAlienArmy() { return alienArmy; }
EarthArmy* Game::GetEarthArmy() { return earthArmy; }
UIMode Game::GetUIMode() const {
	return uiMode;
}


  ////////////////////////
 //   Game Functions   //
////////////////////////

void Game::StartSimulation() {


	UnitGenerator generator(this);
	ReadinputFile(generator);

	if (uiMode == UIMode::Silent) PrintSilentMessages();
	bool wasInEmergency = false;
	while (true)
	{
		generator.GenerateEarth();
		generator.GenerateAlien();

		/// Emergency check
		if (earthArmy->GetInfectionPercentage() >= InfectionThreshold) {

			earthArmy->SetEmergency(true);
		}
		else if (earthArmy->GetInfectedCount() == 0) {
			earthArmy->SetEmergency(false);
			earthArmy->RemoveReinforcement();
			
			wasInEmergency = false;
		}

		if (earthArmy->EmergencyState() == true) {
			generator.GenerateSaverUnits();

			if (wasInEmergency) {
				PlaySound(nullptr, nullptr, 0);
			}

			if (uiMode == UIMode::Interactive && !wasInEmergency ) {
				PlaySound(TEXT("Saver_units_entry.wav") , NULL , SND_FILENAME|SND_ASYNC);
			}

			wasInEmergency = true;
		}

		if (uiMode == UIMode::Interactive) {
			//system("CLS");

			Print();

			cout << endl;
			cout << "===========" << " Units Fighting at Current Timestep " << "===========" << endl;
		}
		else if (uiMode == UIMode::Silent) {
			gotoXY(0, 1); 
			setcursor(false);
			cout << CSI"32m" << "Current Time Step : " << currentTimeStep << CSI"0m" << endl;
		}

		endbattle = CheckForEndSimulation();
		if (endbattle != CONTINUE)
		{
			switch (endbattle)
			{
			case EARTHWON:
				cout << CSI"34m" << WIN_MSG;
				break;
			case ALIENWON:
				cout << CSI"31m" << LOSE_MSG;
				break;
			case DRAW:
				cout << CSI"31m" << "Battle Ended with Draw\n";
				break;
			}
			break;
		}





		earthArmy->Attack();
		alienArmy->Attack();
		earthArmy->infectionspread();
		if (uiMode == UIMode::Interactive) {
			setcolor(FOREGROUND_RED);
			cout << '\n' << "Press enter to continue..." << endl << endl;

			int delay = 0;
			while (_getch() != ENTER)
				delay++;
		}

		currentTimeStep++;
	}
	outfile();
	if(uiMode == UIMode::Silent)
		cout << "Simulation ends, output file is created: " << outputFileDir << endl;
}

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
	if (es) {
		if (es->IsInfected()) es->TreatInfection();
		earthArmy->AddSoldier(es);
	}
	else if (et)
		earthArmy->AddTank(et);
}

EndBattle Game::CheckForEndSimulation()
{
	if (currentTimeStep < 40) return CONTINUE;
	if ((!CanAttack() || (earthArmy->GetTotalUnitsCount() == 0 && alienArmy->GetAlienCount() == 0)))
		return DRAW;
	if (earthArmy->GetTotalUnitsCount() == 0 && alienArmy->GetAlienCount() > 0)
		return ALIENWON;
	if (earthArmy->GetTotalUnitsCount() > 0 && alienArmy->GetAlienCount() == 0)
		return EARTHWON;
	return CONTINUE;
}

bool Game::CanAttack()
{
	int EScount = earthArmy->GetSoldiersCount(), AScount = alienArmy->GetSoldiersCount();
	int EGcount = earthArmy->GetGunneryCount(), ADcount = alienArmy->GetDroneCount();
	int ETcount = earthArmy->GetTankCount(), AMcount = alienArmy->GetMonstersCount();
	if (!earthArmy->GetTotalUnitsCount() || !alienArmy->GetAlienCount())
		return true;
	if (EScount && AScount)
		return true;
	if (ETcount && AMcount)
		return true;
	if (ETcount && earthArmy->IsLowSoldiersMode() && AScount)
		return true;
	if (EGcount && (AMcount || ADcount))
		return true;
	if (AMcount && (ETcount || EScount))
		return true;
	if (ADcount && (ETcount || EGcount))
		return true;
	return false;
}

  /////////////////////
 //   UI functions  //
/////////////////////
void Game::AnimateLogo() {
	PlaySound(TEXT("Resources/Audio/background.wav"), NULL, SND_FILENAME | SND_ASYNC);

	ifstream logoFile("Resources/Animations/logo.txt");
	string imported[15];
	string line;

	int index = 0;
	while (getline(logoFile, line))
	{
		if (line.empty()) index++;
		else imported[index] += (line + '\n');
	}

	for (size_t i = 0; i < 14; i++)
	{
		gotoXY(0, 0);
		setcursor(false);

		cout << endl << CSI"36m" << imported[i];
		Sleep(1000 * 0.05);
	}
}

void Game::PrintMainMenue(string file, string ofile, UIMode mode, FocusMode focusMode) {
	if (focusMode != FocusMode::ModeSelection) setcursor(true);

	setcolor(FOREGROUND_YELLOW);
	gotoXY(0, 0);
	cout << R"(
  ____  _      ____    ___  ____       ____  ____   __ __   ____  _____ ____  ___   ____  
 /    || |    |    |  /  _]|    \     |    ||    \ |  |  | /    |/ ___/|    |/   \ |    \ 
|  o  || |     |  |  /  [_ |  _  |     |  | |  _  ||  |  ||  o  (   \_  |  ||     ||  _  |
|     || |___  |  | |    _]|  |  |     |  | |  |  ||  |  ||     |\__  | |  ||  O  ||  |  |
|  _  ||     | |  | |   [_ |  |  |     |  | |  |  ||  :  ||  _  |/  \ | |  ||     ||  |  |
|  |  ||     | |  | |     ||  |  |     |  | |  |  | \   / |  |  |\    | |  ||     ||  |  |
|__|__||_____||____||_____||__|__|    |____||__|__|  \_/  |__|__| \___||____|\___/ |__|__|                                                                  
)";

	setcolor(FOREGROUND_BLUE);
	cout << "Input File Name: ";
	setcolor(FOREGROUND_WHITE);
	cout << file + "                        " << endl;
	setcolor(FOREGROUND_BLUE);
	cout << "Output File Name: ";
	setcolor(FOREGROUND_WHITE);
	cout << ofile + "                        " << endl;


	if (focusMode == FocusMode::InFileInput) {
		gotoXY(17, 9);
	}
	else if (focusMode == FocusMode::OutFileInput) {
		gotoXY(18, 10);
	}

	if (focusMode == FocusMode::ModeSelection) {
		setcursor(false);
		setcolor(FOREGROUND_BLUE);
		cout << "Simulation mode:" << endl;
		setcolor(mode == UIMode::Interactive ? FOREGROUND_YELLOW : FOREGROUND_WHITE);
		cout << (mode == UIMode::Interactive ? ">" : " ") << " Interactive" << endl;
		setcolor(mode == UIMode::Silent ? FOREGROUND_YELLOW : FOREGROUND_WHITE);
		cout << (mode == UIMode::Silent ? ">" : " ") << " Silent" << endl;
	}
}

void Game::HandleUI() {
	AnimateLogo();
	SetConsoleOutputCP(CP_UTF8);

	string file  = "(testfile.txt)";
	string ofile = "(output.txt)";
	PrintMainMenue(file, ofile, uiMode, FocusMode::InFileInput);


	PrintMainMenue(file, ofile, uiMode, FocusMode::InFileInput);
	cin >> file;

	PrintMainMenue(file, ofile, uiMode, FocusMode::OutFileInput);
	cin >> ofile;



	file = file.empty() ? "testfile.txt" : file + ".txt";
	inputFileDir = file;
	ofile = ofile.empty() ? "output.txt" : ofile + ".txt";
	outputFileDir = ofile;

	char val = 0;
	int modeIndex = 0;
	do {
		if (val == KEY_UP) {
			modeIndex--;
			modeIndex = max(modeIndex, 0);
		}
		else if (val == KEY_DOWN) {
			modeIndex++;
			modeIndex = min(modeIndex, 1);
		}

		PrintMainMenue(file, ofile, (UIMode)modeIndex, FocusMode::ModeSelection);
	} while ((val = _getch()) != ENTER);
	uiMode = (UIMode)modeIndex;
}

void Game::PrintSilentMessages() const {
	system("CLS");
	cout << "Silent Mode" << endl;
	cout << "Simulation starts...";
	
}

void Game::Print() const {
	string half_tab = "\t\b\b\b\b\b";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(hConsole, FOREGROUND_YELLOW);
	cout << "////////////////////////////////////////// Current Timestep : " << currentTimeStep <<" ////////////////////////////////////////// " << endl;

	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	earthArmy->Print();
	alienArmy->Print();

	cout << "===========" << " Killed Units " << "===========" << endl;

	cout << KilledList.getCount() << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " Units ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	KilledList.print();

	cout.clear();
}

  ///////////////////////////////
 //   Read / Write Functions  //
///////////////////////////////
void Game::ReadinputFile(UnitGenerator& generator)
{

	fstream inputfile;

	inputfile.open(("examples\\" + inputFileDir).c_str(), ios::in);
	if (inputfile.is_open()) {

		int temp;
		int numberOfUnits;
		int ES, ET, EG, EHU;
		int AS, AM, AD;
		int Prob;
		int InfectionProb;


		inputfile >> numberOfUnits;
		inputfile >> ES >> ET >> EG >> EHU;
		inputfile >> AS >> AM >> AD;
		inputfile >> Prob;
		inputfile >> InfectionProb;
		inputfile >> InfectionThreshold;        /// parameter in the game class 

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
			ES, ET, EG, EHU,
			AS, AM, AD,
			Prob,
			InfectionProb,
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

/*
N.of.Units
ES ET EG HU
AS AM AD
Prob
InfectionProb
InfectionThreshold
3-4 3-9 2-5
100-100 80-80 20-20
*/
void Game::outfile()
{
	fstream outfile;
	double EsDestrCount = 0, EtDestrCount = 0, EgDestrCount = 0;
	double AsDestrCount = 0, AmDestrCount = 0, AdDestrCount = 0;
	double EDf = 0, EDb = 0, EDd = 0;
	double ADf = 0, ADb = 0, ADd = 0;

	outfile.open(("examples\\" + outputFileDir).c_str(), ios::out);
	if (outfile.is_open())
	{
		outfile << "Total Simulation steps: " << currentTimeStep << endl;
		string table = "Td\tID\tTj\tDf\tDd\tDb\n";
		outfile << table;
		Unit* temp;
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
			outfile << temp->GetDeathTime() << "\t"
					<< temp->GetID() << "\t"
					<< temp->getJoinTime() << "\t"
					<< (dynamic_cast<HealUnit*>(temp)? "NaN" : to_string(temp->getAttackDelay())) << "\t"
					<< (dynamic_cast<HealUnit*>(temp)? "NaN" : to_string(temp->getDestructDelay())) << "\t"
					<< (dynamic_cast<HealUnit*>(temp)? "NaN" : to_string(temp->getBattleTime())) << "\n";
		}
		outfile << "\n=============================================================\n";
		double Es_total = EsDestrCount + earthArmy->GetSoldiersCount() + earthArmy->GetSoldierCountinUML();
		double Et_total = EtDestrCount + earthArmy->GetTankCount() + earthArmy->GetTankCountinUML();
		double Eg_total = EgDestrCount + earthArmy->GetGunneryCount();
		double EHU_total = earthArmy->GetHealUnitsCount();
		double total_earth = Es_total + Et_total + Eg_total;
		double total_desEarth = EsDestrCount + EtDestrCount + EgDestrCount;
		double InfectedCount = earthArmy->GetLifeTimeInfectedUnits();

		double As_total = AsDestrCount + alienArmy->GetSoldiersCount();
		double Ad_total = AdDestrCount + alienArmy->GetDroneCount();
		double Am_total = AmDestrCount + alienArmy->GetMonstersCount();
		double total_alien = As_total + Ad_total + Am_total;
		double total_desAlien = AsDestrCount + AdDestrCount + AmDestrCount;
		double umlcount = earthArmy->GetSoldierCountinUML() + earthArmy->GetTankCountinUML();
		string str;

		if (endbattle == EARTHWON)
			outfile << "\nEarth Army Won The Battle\n";
		else if (endbattle == ALIENWON)
			outfile << "\nAlien Army Won The Battle\n";
		else if (endbattle == DRAW)
			outfile << "\nThe Battle Ended With Draw\n";
		outfile << "\n=============================================================\n";

		double EsAvg = 0, EgAvg = 0, EtAvg = 0, AsAvg = 0, AmAvg = 0, AdAvg = 0;
		if (Es_total) EsAvg = (double)(EsDestrCount / Es_total) * 100.0;
		if (Et_total) EtAvg = (double)(EtDestrCount / Et_total) * 100.0;
		if (Eg_total) EgAvg = (double)(EgDestrCount / Eg_total) * 100.0;
		if (As_total) AsAvg = (double)(AsDestrCount / As_total) * 100.0;
		if (Am_total) AmAvg = (double)(AmDestrCount / Am_total) * 100.0;
		if (Ad_total) AdAvg = (double)(AdDestrCount / Ad_total) * 100.0;

		outfile << "\nEarth Statistics:\nES Count-> " << Es_total << "\nET Count-> " << Et_total << "\nEG Count-> " << Eg_total << "\n" << "Heal Units -> " << EHU_total << '\n';
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

		outfile << endl;
		outfile << "Infection states: " << endl;
		outfile << "Total Infected Units : " << InfectedCount << endl;
		outfile << "Infection Percentage : " << GetEarthArmy()->GetInfectionPercentage() << "%" << endl;
		outfile << endl;

		if (total_earth)
		{
			outfile << "\nTotal Destructed Earth Units : Total Earth Units-> " << (double)(total_desEarth / total_earth) * 100.0 << "%\n";
			outfile << "Total Units in UML : Total Earth Units->" << (double)(umlcount / total_earth) * 100.0 << "%\n";
			double healed = earthArmy->GetHealedCount();
			outfile << "\nHealed Units : Total Earth Units-> " << (double)(healed / total_earth) * 100.0 << "%\n";
		}
		else
			outfile << "\nThere is no Earth Army\n";
		if (total_desEarth)
			outfile << "\nAverage of Df-> " << (double)(EDf / total_desEarth) << "\nAverage of Db-> " << (double)(EDb / total_desEarth)
			<< "\nAverage of Dd-> " << (double)(EDd / total_desEarth) << "\n";
		else
			outfile << "\nthere no destructed earth army\n";


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
		if (total_alien)
		{
			outfile << "\nTotal Destructed Alien Units : Total Alien Units-> " << (double)(total_desAlien / total_alien) * 100.0 << "%\n";
		}
		else
			outfile << "\nThere is no Alien Army\n";
		if (total_desAlien)
			outfile << "\nAverage of Df-> " << (double)(ADf / total_desAlien) << "\nAverage of Db-> " << (double)(ADb / total_desAlien)
			<< "\nAverage of Dd-> " << (double)(ADd / total_desAlien) << "\n";
		else
			outfile << "\nThere is no destructed Alien Army\n";



		//outfile << "\nThere is Alien Army\n";
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
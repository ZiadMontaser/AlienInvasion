#include "UnitGenerator.h"
#include <iostream>
//#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

int UnitGenerator::numberGEN(int min, int max)
{
	int num = (rand() % (max - min + 1)) + min;

	return  num ;
}

UnitGenerator::UnitGenerator(Game* game) {
	pGame = game;

	int random = time(0);
	srand(random);
}

void UnitGenerator::ReadParameters() 
{
	string Filename = "testfile.txt";

#ifndef _DEBUG
	cout << "Please enter the file name you would like to use for unit Generation: ";
	cin >> Filename;
#endif // DEBUG

	fstream inputfile ;
	
	inputfile.open(Filename.c_str(), ios::in);
	if (inputfile.is_open()) {

		int temp;

		inputfile >> numberOfUnits;
		inputfile >> ES >> ET >> EG;
		inputfile >> AS >> AM >> AD;
		inputfile >> Prob;

		inputfile >> temp;
		EarthPowerLower = abs(temp);
		inputfile >> temp;
		EarthPowerUpper = abs(temp);


		inputfile >> temp;
		EarthHealthLower = abs(temp);
		inputfile >> temp;
		EarthHealthUpper = abs(temp);


		inputfile >> temp;
		EarthCapacityLower = abs(temp);
		inputfile >> temp;
		EarthCapacityUpper = abs(temp);


		
		inputfile >> temp;
		AlienPowerLower = abs(temp);
		inputfile >> temp;
		AlienPowerUpper = abs(temp);

		inputfile >> temp;
		AlienHealthLower = abs(temp);
		inputfile >> temp;
		AlienHealthUpper = abs(temp);

		inputfile >> temp;
		AlienCapacityLower = abs(temp);
		inputfile >> temp;
		AlienCapacityUpper = abs(temp);


		//cout << AlienCapacityLower << endl << AlienHealthUpper;

	}

}

void UnitGenerator::GenerateEarth()
{
	
	int canadd = numberGEN(1, 100);

	if (canadd <= Prob) {
		int added = 0;
		

		while (added < numberOfUnits) {
			int unittoadd = numberGEN(1, 100);

			if (unittoadd <= ES) {

				/// add solider


				pGame->GetEarthArmy()->AddSoldier(new EarthSoldier(
					pGame, LastIDearth, numberGEN(EarthHealthLower, EarthHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(EarthPowerLower, EarthPowerUpper),
					numberGEN(EarthCapacityLower, EarthCapacityUpper))
				);

			}
			else if (unittoadd <= (ES + ET)) {

				/// add tank

				pGame->GetEarthArmy()->AddTank(new EarthTank(
					pGame, LastIDearth, numberGEN(EarthHealthLower, EarthHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(EarthPowerLower, EarthPowerUpper),
					numberGEN(EarthCapacityLower, EarthCapacityUpper))
				);
			}
			else {

				/// add gunnery

				pGame->GetEarthArmy()->AddGunnery(new EarthGunnery(
					pGame, LastIDearth, numberGEN(EarthHealthLower, EarthHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(EarthPowerLower, EarthPowerUpper),
					numberGEN(EarthCapacityLower, EarthCapacityUpper))
				);
			}
			LastIDearth++;
			added++;
		}
	}
	else
		return;
}

void UnitGenerator::GenerateAlien()
{
	
	int canadd = numberGEN(1, 100);

	if (canadd <= Prob) {
		int added = 0;
		

		while (added < numberOfUnits) {

			int unittoadd = numberGEN(1, 100);

			if (unittoadd <= AS) {

				/// add solider
				pGame->GetAlienArmy()->AddSoldier(new AlienSoldier(
					pGame, LastIDaliens, numberGEN(AlienHealthLower, AlienHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(AlienPowerLower, AlienPowerUpper),
					numberGEN(AlienCapacityLower, AlienCapacityUpper))
				);

			}
			else if (unittoadd <= AS + AM) {
				/// add monester

				pGame->GetAlienArmy()->AddMonester(new Monester(
					pGame, LastIDaliens, numberGEN(AlienHealthLower, AlienHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(AlienPowerLower, AlienPowerUpper),
					numberGEN(AlienCapacityLower, AlienCapacityUpper))
				);
			}
			else {

				pGame->GetAlienArmy()->AddDrone(new Drone(
					pGame, LastIDaliens, numberGEN(AlienHealthLower, AlienHealthUpper),
					0, /// this is the jointime for now 
					numberGEN(AlienPowerLower, AlienPowerUpper),
					numberGEN(AlienCapacityLower, AlienCapacityUpper))
				);
			}
			LastIDaliens++;
			added++;
		}
	}
	else
		return;
}


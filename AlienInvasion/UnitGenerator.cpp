#include "UnitGenerator.h"
#include <iostream>
//#include <algorithm>
#include <fstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Game.h"

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

void UnitGenerator::ReadParameters(int NumberOfUnits,
	int es, int et, int eg,
	int as, int am, int ad,
	int prob,
	int earthPowerLower,
	int earthPowerUpper,
	int earthHealthLower,
	int earthHealthUpper,
	int earthCapacityLower,
	int earthCapacityUpper,
	int alienPowerLower,
	int alienPowerUpper,
	int alienHealthLower,
	int alienHealthUpper,
	int alienCapacityLower,
	int alienCapacityUpper)
{
	this->numberOfUnits = NumberOfUnits;
	this->ES = es;
	this->ET = et;
	this->EG = eg;
	this->AS = as;
	this->AM = am;
	this->AD = ad;
	this->Prob = prob;
	this->EarthPowerLower = earthPowerLower;
	this->EarthPowerUpper = earthPowerUpper;
	this->EarthHealthLower = earthHealthLower;
	this->EarthHealthUpper = earthHealthUpper;
	this->EarthCapacityLower = earthCapacityLower;
	this->EarthCapacityUpper = earthCapacityUpper;
	this->AlienPowerLower = alienPowerLower;
	this->AlienPowerUpper = alienPowerUpper;
	this->AlienHealthLower = alienHealthLower;
	this->AlienHealthUpper = alienHealthUpper;
	this->AlienCapacityLower = alienCapacityLower;
	this->AlienCapacityUpper = alienCapacityUpper;
	
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


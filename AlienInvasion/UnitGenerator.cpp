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

	int random = time(0);
	srand(random);
	return min +(rand()% (max - min +1) );
}

UnitGenerator::UnitGenerator(Game* game) {
	pGame = game;
}

void UnitGenerator::ReadParameters() 
{
	string Filename;
	cout << "Please enter the file name you would like to use for unit Generation: ";
	cin >> Filename;

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
		int numtoadd = numberGEN(1, 1000000);

		while (added < numtoadd) {
			int unittoadd = numberGEN(1, 100);

			if (unittoadd <= ES) {

				/// add solider

			}
			else if (unittoadd <= ES + ET) {

				/// add tank
			}
			else {

				/// add gunnery
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
		int numtoadd = numberGEN(1, 100000);

		while (added < numtoadd) {

			int unittoadd = numberGEN(1, 100);

			if (unittoadd <= AS) {

				/// add solider

			}
			else if (unittoadd <= AS + AM) {

				/// add monester
			}
			else {

				/// add drone
			}
			LastIDaliens++;
			added++;
		}
	}
	else
		return;
}


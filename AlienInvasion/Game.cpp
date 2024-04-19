#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
#include <conio.h>
AlienArmy* Game::GetAlienArmy() { return &alienArmy; }
EarthArmy* Game::GetEarthArmy() { return &earthArmy; }

void Game::ReportDeadUnit(Unit* dead)
{
	KilledList.enqueue(dead);
}



void Game::StartSimulation() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	UnitGenerator generator(this);
	generator.ReadParameters();

	while (currentTimeStep < 50)
	{
		generator.GenerateEarth();
		generator.GenerateAlien();

		system("CLS");
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED);

		int x = (rand() % 101);

		if (x < 10) {
			EarthSoldier* unit;
			if (earthArmy.Soldiers.dequeue(unit)) {
				earthArmy.Soldiers.enqueue(unit);
				cout << "Dequeued and Enqueued an earth soldeir" << endl;
			}
			else {
				cout << "No earth soldiers found" << endl;
			}
		}
		else if (x < 20) {
			EarthTank* tank = nullptr;

			if (earthArmy.Tanks.pop(tank)) {
				KilledList.enqueue(tank);
				cout << "Moved Tank " << tank->GetID() << " to killed list" << endl;
			}
			else {
				cout << "No tank found" << endl;
			}
		}
		else if (x < 30) {
			EarthGunnery* gunnary = nullptr; int pri;
			if (earthArmy.Gunnery.dequeue(gunnary, pri)) {
				gunnary->Damage(3.0 / 2.0 * sqrt(gunnary->GetHealth()), 100);
				earthArmy.Gunnery.enqueue(gunnary, pri);
				cout << "Damaged a Gunnary " << gunnary->GetID() << " and put it back in its list" << endl;

			}else
				cout << "No tank found" << endl;

		}
		else if (x < 40) {
			for (int i = 0; i < 5; i++) {
				AlienSoldier* soldier = nullptr;
				if (alienArmy.Soldiers.dequeue(soldier)) {
					soldier->Damage(100, 50);
					alienArmy.ArenaList.push(soldier);

				}

				Unit* value = nullptr;
				if (alienArmy.ArenaList.pop(value)) {
					alienArmy.Soldiers.enqueue((AlienSoldier*)value);
					cout << "Damaged a soldier " << soldier->GetID() << ", Moved to arena list, Put back in its list" << endl;
				}

			}
		}
		else if (x < 50) {
			if (alienArmy.Count_Monesters == 0) cout << "No monesters was found" << endl;
			Monester* list[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
			for (int i = 0; i < 5; i++) {
				if (alienArmy.Count_Monesters == 0) break;
				int random = rand() % alienArmy.Count_Monesters ;
				list[i] = alienArmy.Monesters[i];
				alienArmy.Monesters[i] = alienArmy.Monesters[alienArmy.Count_Monesters - 1];
				alienArmy.Count_Monesters--;
			}
			for (int i = 0; i < 5; i++) {
				if (list[i]) {
					alienArmy.Monesters[alienArmy.Count_Monesters++] = list[i];
					cout << "Pick and restored a monester with id: " << list[i]->GetID() << endl;
				}
			}
		}
		else if (x < 60) {
			for (int i = 0; i < 6; i++) {
				Drone* front = nullptr, *back = nullptr;

				if (alienArmy.Drones.dequeue(front)) {
					KilledList.enqueue(front);
					cout << "Moved Drone {" << front->GetID() << "} to killed list" << endl;
				}
				else {
					cout << "No drone found" << endl;
				}
				if (alienArmy.Drones.dequeueback(back)) {
					KilledList.enqueue(back);
					cout << "Moved Drone {" << back->GetID() << "} to killed list" << endl;
				}
				else {
					cout << "No drone found" << endl;

				}
			}
			
		}
		else {
			cout << "No action was taken." << endl;
		}
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);

		Print();

		while (_getch() != 13);
		//Sleep(1000 * 1); // 3 seconds
		currentTimeStep++;
	}

}

void Game::Print() const {
	cout << "Current Timestep " << currentTimeStep << endl;
	earthArmy.Print();
	alienArmy.Print();

	cout << "===========" << " Killed Units " << "===========" << endl;

	cout << KilledList.getCount() << " units ";
	KilledList.print();

	cout.clear();
}
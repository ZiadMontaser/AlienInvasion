#include "Game.h"
#include "UnitGenerator.h"
#include <Windows.h>
AlienArmy* Game::GetAlienArmy() { return &alienArmy; }
EarthArmy* Game::GetEarthArmy() { return &earthArmy; }

void Game::ReportDeadUnit(Unit* dead)
{
	KilledList.enqueue(dead);
}



void Game::StartSimulation() {

	UnitGenerator generator(this);
	generator.ReadParameters();

	while (currentTimeStep < 50)
	{
		generator.GenerateEarth();
		generator.GenerateAlien();

		//earthArmy.Attack();
		//alienArmy.Attack();
		int x = (rand() % 101);
		
		if (x < 10) {
			EarthSoldier* unit;
			if(earthArmy.Soldiers.dequeue(unit))
			earthArmy.Soldiers.enqueue(unit);
		}
		else if (x < 20) {
			EarthTank* tank = nullptr;
			earthArmy.Tanks.pop(tank);
			if(tank)
				KilledList.enqueue(tank);
		}
		else if (x < 30) {
			EarthGunnery* gunnary = nullptr; int pri;
			earthArmy.Gunnery.dequeue(gunnary, pri);
			if(gunnary)
				gunnary->Damage(3.0 / 2.0 * sqrt(gunnary->GetHealth()), 100);
			if(gunnary)
				earthArmy.Gunnery.enqueue(gunnary, pri);
		}
		else if (x < 40) {
			AlienSoldier* soldier = nullptr;
			alienArmy.Soldiers.dequeue(soldier);

			if(soldier)
				soldier->Damage(1, 1);
			if(soldier)
				alienArmy.ArenaList.push(soldier);
			
			Unit* value = nullptr;
			alienArmy.ArenaList.pop(value);
			if(value)
				alienArmy.Soldiers.enqueue((AlienSoldier*) value);
		}
		else if (x < 50) {
	
			Monester* list[5] = { nullptr, nullptr, nullptr, nullptr, nullptr };
			for (int i = 0; i < 5; i++) {
				if (alienArmy.Count_Monesters == 0) break;
				int random = rand() % alienArmy.Count_Monesters ;
				list[i] = alienArmy.Monesters[i];
				alienArmy.Monesters[i] = alienArmy.Monesters[alienArmy.Count_Monesters - 1];
				alienArmy.Count_Monesters--;
			}
			for (int i = 0; i < 5; i++) {
				if(list[i])
				alienArmy.Monesters[alienArmy.Count_Monesters++] = list[i];
			}
		}
		else if (x < 60) {
			for (int i = 0; i < 6; i++) {
				Drone* front = nullptr, *back = nullptr;
				alienArmy.Drones.dequeue(front);
				alienArmy.Drones.dequeueback(back);
				if(front) KilledList.enqueue(front);
				if(back) KilledList.enqueue(back);
			}
		}


		system("CLS");
		Print();


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
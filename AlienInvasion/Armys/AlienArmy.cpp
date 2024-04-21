#include "AlienArmy.h"
#include "../DataStructures/LinkedQueue.h"
#include <cstdlib>
#include <time.h>
#include <string>
#include "../Game.h"

AlienSoldier* AlienArmy::GetSoldier() {
	AlienSoldier* value = nullptr;
	if (Soldiers.dequeue(value)) {
		if (value)
		value->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(value);
		return value;
	}
	return NULL;
}

Monester* AlienArmy::GetMonester()
{
	if (Count_Monesters == 0)
		return nullptr;

	srand(time(NULL));
	int index = (rand() % (Count_Monesters + 1));
	
	Monester* Chosen = Monesters[index];
	if (Chosen)
		Chosen->SetAttackedTime(pGame->GetTimeStamp());
	Monesters[index] = Monesters[Count_Monesters - 1];
	Monesters[Count_Monesters] = nullptr;
	if(Chosen) ArenaList.push(Chosen);

	Count_Monesters--;


	return Chosen;
}

Monester* AlienArmy::GetMonesterTofight()
{
	if (Count_Monesters == 0)
		return nullptr;

	srand(time(NULL));
	int index = (rand() % (Count_Monesters + 1));
	Monester* Chosen = Monesters[index];

	return Chosen;
}

Drone* AlienArmy::GetdroneFront()
{
	Drone* Chosen = nullptr;
	if (Drones.dequeue(Chosen)) {
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(Chosen);
		return Chosen;
	}
	return NULL;

	
}

Drone* AlienArmy::GetdroneBack()
{
	Drone* Chosen = nullptr;
	if (Drones.dequeueback(Chosen)) {
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(Chosen);
		return Chosen;
	}

	return NULL;
}

void AlienArmy::AddSoldier(AlienSoldier* soldiers) {
	if (!soldiers) return;

	Soldiers.enqueue(soldiers);
	//Cap_Soliders++;
}

void AlienArmy::AddMonester(Monester* M){
	if (!M) return;

	Monesters[Count_Monesters++] = M;

}
#include "../Game.h"

void AlienArmy::AddDrone(Drone* D)
{
	if (!D) return;
	Drones.enqueue(D);

	//Cap_Drones++;
}

void AlienArmy::Attack() {
	
	// Soldier Attack
	AlienSoldier* soldier = nullptr;
	Soldiers.peek(soldier);
	if (soldier) {
		soldier->Attack();
	}

	// Drone Attack
	Drone* frontDrone = nullptr;
	Drone* backDrone = nullptr;
	Drones.peek(frontDrone);
	Drones.Rear(backDrone);
	if (frontDrone)
		frontDrone->Attack();
	if (backDrone)
		backDrone->Attack();
	
	// Monster Attack
	Monester* M = nullptr;
	M = GetMonesterTofight();
	if (M)
		M->Attack();
}

int AlienArmy::GetSoldiersCount() const { return Soldiers.getCount(); }
int AlienArmy::GetMonstersCount() const { return Count_Monesters; }
int AlienArmy::GetDroneCount()	  const { return Drones.getCount(); }

int AlienArmy::GetAlienCount()
{
	return GetSoldiersCount() + GetDroneCount() + GetMonstersCount();
}

void AlienArmy::RestoreAliveUnits() {
	while (!ArenaList.isEmpty()) {
		Unit* unit = nullptr;
		ArenaList.pop(unit);
		if (unit->IsDead()) continue;
		
		AlienSoldier* soldier;
		Monester* monester;
		Drone* drone;

		if (soldier = dynamic_cast<AlienSoldier*>(unit)) {
			AddSoldier(soldier);

		}else if (monester = dynamic_cast<Monester*>(unit)) {
			AddMonester(monester);

		}else if (drone = dynamic_cast<Drone*>(unit)) {
			AddDrone(drone);
		}
	}
}

void AlienArmy::Print() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	cout << "===========" << "Alien Army Alive Units" << "===========" << endl;

	cout << Soldiers.getCount();
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " AS ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);

	Soldiers.print();

	cout << Count_Monesters;
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " AM ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	cout << "[";
	for (int i = 0; i < Count_Monesters; i++) {
		cout << Monesters[i];
		if (i != Count_Monesters - 1)
			cout << ", ";
	}
	cout << "]" << endl;

	cout << Drones.getCount();
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " AD ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	Drones.print();

	cout << endl;
}

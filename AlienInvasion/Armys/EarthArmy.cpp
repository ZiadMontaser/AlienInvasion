#include "EarthArmy.h"
#include <iostream>
#include <Windows.h>

#include "../Game.h"


void EarthArmy::Attack()
{
	if (isLowSoldiersMode) { //Mode enabled
		if ((float(GetSoldiersCount()) / pGame->GetAlienArmy()->GetSoldiersCount()) >= 0.8) {
			isLowSoldiersMode = false;
		}
	}
	else {
		if ((float(GetSoldiersCount()) / pGame->GetAlienArmy()->GetSoldiersCount()) <= 0.3) {
			isLowSoldiersMode = true;
		}
	}

	EarthSoldier* soldier = nullptr;
	Soldiers.peek(soldier);
	if (soldier) {
		soldier->Attack();
	}

	EarthTank* tank = nullptr;
	Tanks.peek(tank);
	if (tank) {
		tank->Attack();
	}

	EarthGunnery* gunnery = nullptr; int pri;
	Gunnery.peek(gunnery, pri);
	if (gunnery) {
		gunnery->Attack();
	}

	HealUnit* Healunit = nullptr;
	healUnits.peek(Healunit);
	if (Healunit) {

		Healunit->Attack();
	}

}


void EarthArmy::AddSoldier(EarthSoldier* Him)
{
	if (!Him) return;
	Soldiers.enqueue(Him);

}

void EarthArmy::AddTank(EarthTank* T){
	if (!T) return;
Tanks.push(T);
}

void EarthArmy::AddGunnery(EarthGunnery* G)
{
	if (!G) return;
	Gunnery.enqueue(G, G->GetPower() + G->GetHealth());
}

void EarthArmy::AddHealUnit(HealUnit* G) {
	if (!G) return;
	healUnits.push(G);
}

void EarthArmy::MoveUnitToUML(Unit* unit) {
	if (!unit) return;

	EarthTank* tank;
	EarthSoldier* soldier;
	if (tank = dynamic_cast<EarthTank*>(unit)) {
		tankUnitMaintenanceList.enqueue(tank);
	}
	else if (soldier = dynamic_cast<EarthSoldier*>(unit)) {
		soldierUnitMaintenanceList.enqueue(soldier, INT_MAX - soldier->GetHealth());
	}
}

EarthSoldier* EarthArmy::GetSoldier()
{
	EarthSoldier* Chosen = nullptr;
	if (Soldiers.dequeue(Chosen))
	{
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(Chosen);
		return Chosen;
	}

	return NULL;
}

EarthTank* EarthArmy::GetTank()
{
	EarthTank* Chosen = nullptr;
	if (Tanks.pop(Chosen))
	{
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(Chosen);
		return Chosen;
	}

	return NULL;
}

EarthGunnery* EarthArmy::GetGunnery()
{
	EarthGunnery* Chosen = nullptr;
	int dummy;    /// may need it ?
	if (Gunnery.dequeue(Chosen , dummy))
	{
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(Chosen);
		return Chosen;
	}

	return NULL;
}

void EarthArmy::RemoveHealUnit() 
{
	HealUnit* Chosen = nullptr;
	healUnits.pop(Chosen);

}

Unit* EarthArmy::SelectUnitFromUML() {

	EarthSoldier* soldier; int pri;
	if(soldierUnitMaintenanceList.dequeue(soldier, pri))
		return soldier;

	EarthTank* tank;
	if (tankUnitMaintenanceList.dequeue(tank))
		return tank;

	return NULL;
}


int EarthArmy::GetSoldiersCount() const {
	return Soldiers.getCount();
}

int EarthArmy::IsLowSoldiersMode() const {
	return isLowSoldiersMode;
}

void EarthArmy::RestoreAliveUnits() {
	while (!ArenaList.isEmpty()) {
		Unit* unit;
		ArenaList.pop(unit);
		if (unit->IsDead()) continue;
		EarthSoldier* soldier;
		EarthTank* tank;
		EarthGunnery* gunnery;

		if (soldier = dynamic_cast<EarthSoldier*>(unit)) {
			if (unit->GetHealth() < 0.2 * unit->GetMaxHealth()) { MoveUnitToUML(unit); }
			else 
			AddSoldier(soldier);
		}
		else if (tank = dynamic_cast<EarthTank*>(unit)) {
			if (unit->GetHealth() < 0.2 * unit->GetMaxHealth()) { MoveUnitToUML(unit); }
			else
			AddTank(tank);

		}
		else if (gunnery = dynamic_cast<EarthGunnery*>(unit)) {
			AddGunnery(gunnery);
		}
	}
}


void EarthArmy::Print() const {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "===========" << "Earth Army Alive Units" << "===========" << endl;

	cout << Soldiers.getCount();
	CONSOLE_SCREEN_BUFFER_INFO cbsi;
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " ES ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); 
	Soldiers.print();

	cout << Tanks.getCount();
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " ET ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	Tanks.print();

	cout << Gunnery.getCount();
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " EG ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	Gunnery.print();

	cout << healUnits.getCount();
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " EHU ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	healUnits.print();

	cout << endl;
	cout << (soldierUnitMaintenanceList.getCount() + tankUnitMaintenanceList.getCount());
	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " UML ES ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	soldierUnitMaintenanceList.print();

	if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
	{
		COORD pos = { 3, cbsi.dwCursorPosition.Y };
		SetConsoleCursorPosition(hConsole, pos);
	}
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "     ET ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	tankUnitMaintenanceList.print();

	cout << endl;
}

int EarthArmy::GetEarthCount() const
{
	return GetTankCount() + GetSoldiersCount() + GetGunneryCount();
}

int EarthArmy::GetTankCount() const
{
	int count = Tanks.getCount();
	return count;
}

int EarthArmy::GetGunneryCount() const
{
	int count = Gunnery.getCount();
	return count;
}



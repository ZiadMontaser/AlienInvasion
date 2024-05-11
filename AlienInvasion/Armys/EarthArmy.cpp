#include "EarthArmy.h"
#include <iostream>
#include <Windows.h>
#include <iomanip>

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
	Soldiers.dequeue(soldier);
	if (soldier) {
		soldier->Attack();
		Soldiers.enqueue(soldier);
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
	EarthSaverUnit* Sv = NULL;
	AlliedArmy.peek(Sv);
	if (Sv) {

		Sv->Attack();
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
	if (Him->IsInfected()) InfectedSoldiersCount++;
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

void EarthArmy::AddSaverUnit(EarthSaverUnit* Sv)
{
	if (!Sv) return;
	AlliedArmy.enqueue(Sv);
}

void EarthArmy::MoveUnitToUML(Unit* unit) {
	if (!unit) return;

	EarthTank* tank;
	EarthSoldier* soldier;
	if (tank = dynamic_cast<EarthTank*>(unit)) {
		tank->SetTimeHeal(pGame->GetTimeStamp());
		tankUnitMaintenanceList.enqueue(tank);
	}
	else if (soldier = dynamic_cast<EarthSoldier*>(unit)) {
		soldier->SetTimeHeal(pGame->GetTimeStamp());
		soldierUnitMaintenanceList.enqueue(soldier, INT_MAX - soldier->GetHealth());
	}
}

int EarthArmy::GetInfectedCount()
{
	return InfectedSoldiersCount;
}

void EarthArmy::SetEmergency(bool state) {

	Emergency = state;
}

bool EarthArmy::EmergencyState()
{
	return Emergency;
}



EarthSoldier* EarthArmy::GetSoldier()
{
	EarthSoldier* Chosen = nullptr;
	if (Soldiers.dequeue(Chosen))
	{
		if (Chosen)
			Chosen->SetAttackedTime(pGame->GetTimeStamp());
		if (Chosen->IsInfected()) InfectedSoldiersCount--;
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

EarthSaverUnit* EarthArmy::GetSaverUnit() {
	EarthSaverUnit* chosen;
	if (AlliedArmy.dequeue(chosen)) {
		chosen->SetAttackedTime(pGame->GetTimeStamp());
		ArenaList.push(chosen);
		return chosen;
	}
	return NULL;
}

void EarthArmy::RemoveReinforcement()
{
	EarthSaverUnit* chosen;

	while (!AlliedArmy.isEmpty()) {
		AlliedArmy.dequeue(chosen);
		chosen->KILL();
	}
}


void EarthArmy::RemoveHealUnit() 
{
	HealUnit* Chosen = nullptr;
	healUnits.pop(Chosen);
	healedcount++;

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
		EarthSaverUnit* Saver;

		if (soldier = dynamic_cast<EarthSoldier*>(unit)) {
			if (unit->GetHealth() < 0.2 * unit->GetMaxHealth()) { MoveUnitToUML(unit); }
			else AddSoldier(soldier);
		}
		else if (tank = dynamic_cast<EarthTank*>(unit)) {
			if (unit->GetHealth() < 0.2 * unit->GetMaxHealth()) { MoveUnitToUML(unit); }
			else
			AddTank(tank);

		}
		else if (gunnery = dynamic_cast<EarthGunnery*>(unit)) {
			AddGunnery(gunnery);
		}
		else if (Saver = dynamic_cast<EarthSaverUnit*> (unit)) {
			AddSaverUnit(Saver);
		}
	}
}


void EarthArmy::Print() const {
	string half_tab = "\t\b\b\b\b\b";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "===========" << "Earth Army Alive Units" << "===========" << endl;
	std::setprecision(std::numeric_limits<float> ::digits10 + 1);
	cout << "Infection Status: " <<( Soldiers.getCount() ? (InfectedSoldiersCount * 100 / Soldiers.getCount()) : 0 )<< "%" << endl;
	cout << Soldiers.getCount() << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " ES  ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE); 
	Soldiers.print();

	cout << Tanks.getCount() << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " ET  ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	Tanks.print();

	cout << Gunnery.getCount() << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " EG  ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	Gunnery.print();

	cout << healUnits.getCount() << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " EHU ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	healUnits.print();

	if (Emergency) {

		cout << AlliedArmy.getCount() << half_tab;
		SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << " ESV ";
		SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
		AlliedArmy.print();
	}

	cout << endl;
	cout << (soldierUnitMaintenanceList.getCount() + tankUnitMaintenanceList.getCount()) << half_tab;
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << " UML ES ";
	SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	soldierUnitMaintenanceList.print();

	cout << "\t";
	SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
	cout << "ET ";
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

int EarthArmy::GetSoldierCountinUML() const
{
	return soldierUnitMaintenanceList.getCount();
}

int EarthArmy::GetTankCountinUML() const
{
	return tankUnitMaintenanceList.getCount();
}

int EarthArmy::GetHealedCount() const
{
	return healedcount;
}



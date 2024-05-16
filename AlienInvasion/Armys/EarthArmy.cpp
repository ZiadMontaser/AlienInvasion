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
		if (soldier->IsInfected()) {
			InjuredInfectedSoldiersCount++;
		}
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

void EarthArmy::infectionspread()
{
	const int INFECTION_PROB = 2;
	LinkedQueue<EarthSoldier*> temp, infected, notinfected, temp4;

	EarthSoldier* deq;
	while (Soldiers.dequeue(deq))
	{
		if (deq->IsInfected())
			infected.enqueue(deq);
		else
			notinfected.enqueue(deq);
		temp.enqueue(deq);
	}

	EarthSoldier* inf;
	while (infected.dequeue(inf))
	{
		int infectprob = rand() % 100;
		if (infectprob <= INFECTION_PROB)
		{
			int num_of_not_infected = GetSoldiersCount() - GetInfectedCount();
			if (!num_of_not_infected) break;
			int toinfectran = rand() % (GetSoldiersCount() - GetInfectedCount());
			EarthSoldier* toinf;
			bool isPreyFound = false;
			for (int i = 0; i < toinfectran; i++)
			{
				if(isPreyFound = notinfected.dequeue(toinf))
					temp4.enqueue(toinf);
			}
			if (notinfected.peek(toinf) && isPreyFound) {
				inf->infectSoldier(toinf);
				if(pGame->GetUIMode() == UIMode::Interactive)
					std::cout << CSI"33m" << u8"🤒 ES " << toinf << CSI"33m" << "caught infection from ES " << inf << CSI"0m" << endl;
			}
			while (temp4.dequeue(toinf))
				notinfected.enqueue(toinf);

		}
	}
	EarthSoldier* sols;
	while (temp.dequeue(sols))
		Soldiers.enqueue(sols);	
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
	if (soldierUnitMaintenanceList.dequeue(soldier, pri)) {
		if (soldier->IsInfected()) InjuredInfectedSoldiersCount--;
		return soldier;
	}

	EarthTank* tank;
	if (tankUnitMaintenanceList.dequeue(tank))
		return tank;

	return NULL;
}


int EarthArmy::GetSoldiersCount() const {
	return Soldiers.getCount();
}

void EarthArmy::ReportInfectedUnit(Unit* unit) {
	if (unit && unit->IsInfected()) totalInfectedLifeTime++;
}

void EarthArmy::ReportTreatedUnit(Unit* unit)
{
	if (unit && unit->IsImmune()) InjuredInfectedSoldiersCount--;
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

#define DISPLAY_COLOR 36;
void EarthArmy::Print() const {
	string half_tab = "\t\b\b\b\b\b";
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	cout << "===========" << "Earth Army Alive Units" << "===========" << endl;
	std::setprecision(std::numeric_limits<float> ::digits10 + 1);
	int totalInfectedCount = InjuredInfectedSoldiersCount + InfectedSoldiersCount;
	int totalSoldierCount = Soldiers.getCount() + soldierUnitMaintenanceList.getCount();
	cout << "Infection Status: " << (totalSoldierCount ? (totalInfectedCount * 100 / totalSoldierCount) : 0 )<< "%" << endl;
	cout << Soldiers.getCount() << half_tab;
	cout << CSI"36m" << " ES  " << CSI"0m";
	Soldiers.print();

	cout << Tanks.getCount() << half_tab;
	cout << CSI"36m ET  " << CSI"0m";
	Tanks.print();

	cout << Gunnery.getCount() << half_tab;
	cout << CSI"36m" << " EG  " << CSI"0m";
	Gunnery.print();

	cout << healUnits.getCount() << half_tab;
	cout << CSI"36m" << " EHU " << CSI"0m";
	healUnits.print();



	cout << endl;
	cout << (soldierUnitMaintenanceList.getCount() + tankUnitMaintenanceList.getCount()) << half_tab;
	cout << CSI"36m" << " UML ES " << CSI"0m";
	soldierUnitMaintenanceList.print();

	cout << "\t";
	cout << CSI"36m" << "ET " << CSI"0m";
	tankUnitMaintenanceList.print();
	cout << endl;


	
	if (Emergency) {
		cout << "===========" << "Allied Army Alive Units" << "===========" << endl;

		cout << AlliedArmy.getCount() << half_tab;
		cout << CSI"36m" << " SU " << CSI"0m";
		AlliedArmy.print();
	}cout << endl;
}

int EarthArmy::GetTotalUnitsCount() const
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

int EarthArmy::GetHealUnitsCount() const
{
	return healUnits.getCount();
}

int EarthArmy::GetSoldierCountinUML() const
{
	return soldierUnitMaintenanceList.getCount();
}

int EarthArmy::GetTankCountinUML() const
{
	return tankUnitMaintenanceList.getCount();
}

double EarthArmy::GetInfectionPercentage() const {
	double totalInfectedCount = InjuredInfectedSoldiersCount + InfectedSoldiersCount;
	int totalSoldierCount = Soldiers.getCount() + soldierUnitMaintenanceList.getCount();

	return (totalSoldierCount ? (totalInfectedCount * 100 / totalSoldierCount) : 0);
}

int EarthArmy::GetLifeTimeInfectedUnits() const {
	return totalInfectedLifeTime;
}

int EarthArmy::GetHealedCount() const
{
	return healedcount;
}



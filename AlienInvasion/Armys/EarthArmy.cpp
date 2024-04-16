#include "EarthArmy.h"
#include <iostream>

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
	unitMaintenanceList.enqueue(unit, unit->GetType());
}

EarthSoldier* EarthArmy::GetSoldier()
{
	EarthSoldier* Chosen = nullptr;
	if (Soldiers.dequeue(Chosen))
	return Chosen;

	return NULL;
}

EarthTank* EarthArmy::GetTank()
{
	EarthTank* Chosen = nullptr;
	if (Tanks.pop(Chosen))
	return Chosen;

	return NULL;
}

EarthGunnery* EarthArmy::GetGunnery()
{
	EarthGunnery* Chosen = nullptr;
	int dummy;    /// may need it ?
	if (Gunnery.dequeue(Chosen , dummy))
		return Chosen;

	return NULL;
}

Unit* EarthArmy::SelectUnitFromUML() {
	Unit* Chosen = nullptr;
	int dummy;    /// may need it ?
	if (unitMaintenanceList.dequeue(Chosen, dummy))
		return Chosen;

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

		switch (unit->GetType())
		{
		case UnitType::EARTH_SOLDIER: {
			LinkedQueue<EarthSoldier*> temp;
			while (!Soldiers.isEmpty()) {
				EarthSoldier* value;
				Soldiers.dequeue(value);
				temp.enqueue(value);
			}

			Soldiers.enqueue((EarthSoldier*)unit);

			while (!temp.isEmpty()) {
				EarthSoldier* value;
				temp.dequeue(value);
				Soldiers.enqueue(value);
			}

			break;
		}
		default:
			break;
		}
	}
}


void EarthArmy::Print() const {
	cout << "===========" << "Earth Army Alive Units" << "===========" << endl;

	cout << Soldiers.getCount() << " ES ";
	Soldiers.print();

	cout << Tanks.getCount() << " ET ";
	Tanks.print();

	cout << Gunnery.getCount() << " EG ";
	Gunnery.print();

	cout << endl;
}



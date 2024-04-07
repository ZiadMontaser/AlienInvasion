#include "EarthArmy.h"
#include <iostream>


void EarthArmy::Attack()
{

}


void EarthArmy::AddSoldier(EarthSoldier* Him)
{
	if (!Him) return;
	Soldiers.enqueue(Him);
	Cap_Soliders++;
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



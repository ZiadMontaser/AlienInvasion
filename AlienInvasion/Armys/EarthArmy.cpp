#include "EarthArmy.h"
//#include "../DataStructures/LinkedQueue.h"


void EarthArmy::Attack()
{

}


void EarthArmy::AddSoldier(EarthSoldier* Him)
{
	Soldiers.enqueue(Him);
	Cap_Soliders++;
}

void EarthArmy::AddTank(EarthTank* T){

Tanks.push(T);
}

void EarthArmy::AddGunnery(EarthGunnery* G)
{
	Gunnery.enqueue(G, G->GetPower() + G->GetHealth());
}


EarthSoldier* EarthArmy::GetSoldier() {
	EarthSoldier* value;
	Soldiers.dequeue(value);
	ArenaList.push(value);
	return value;
}

void EarthArmy::RestoreAliveUnitsFromArena() {
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



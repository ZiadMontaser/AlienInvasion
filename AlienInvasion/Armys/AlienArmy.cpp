#include "AlienArmy.h"
#include "../DataStructures/LinkedQueue.h"

AlienSoldier* AlienArmy::GetSoldier() {
	AlienSoldier* value;
	Soldiers.dequeue(value);
	ArenaList.push(value);
	return value;
}

void AlienArmy::AddSoldier(AlienSoldier* soldiers) {
	Soldiers.enqueue(soldiers);
	//Cap_Soliders++;
}

void AlienArmy::AddMonester(Monester* M){
	Monesters[Cap_Monesters++] = M;

}

void AlienArmy::AddDrone(Drone* D)
{
	Drones.enqueue(D);
	//Cap_Drones++;
}

void AlienArmy::Attack() {

}

void AlienArmy::RestoreAliveUnitsFromArena() {
	while (!ArenaList.isEmpty()) {
		Unit* unit;
		ArenaList.pop(unit);

		if (unit->GetHealth() <= 0) continue;

		switch (unit->GetType())
		{
		case UnitType::ALIEN_SOLDIER:{ //O(n)
				LinkedQueue<AlienSoldier*> temp;
				while (!Soldiers.isEmpty()) {
					AlienSoldier* value;
					Soldiers.dequeue(value);
					temp.enqueue(value);
				}

				Soldiers.enqueue((AlienSoldier*)unit);

				while (!temp.isEmpty()) {
					AlienSoldier* value;
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
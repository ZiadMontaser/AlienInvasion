#include "AlienArmy.h"
#include "../DataStructures/LinkedQueue.h"
#include <cstdlib>
#include <time.h>

AlienSoldier* AlienArmy::GetSoldier() {
	AlienSoldier* value;
	if (Soldiers.dequeue(value)) {
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
	Count_Monesters--;


	return Chosen;
}

Drone* AlienArmy::GetdroneFront()
{
	Drone* Chosen;
	if (Drones.dequeue(Chosen))
	return Chosen;
	return NULL;

	
}

Drone* AlienArmy::GetdroneBack()
{
	Drone* Chosen;
	if (Drones.dequeueback(Chosen))
	return Chosen;
	return NULL;
}

void AlienArmy::AddSoldier(AlienSoldier* soldiers) {
	Soldiers.enqueue(soldiers);
	//Cap_Soliders++;
}

void AlienArmy::AddMonester(Monester* M){
	Monesters[Count_Monesters++] = M;

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
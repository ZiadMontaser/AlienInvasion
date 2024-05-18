#include "EarthGunnery.h"
#include <cmath>

#include "../Game.h"
#include "Monester.h"
#include "Drones.h"

void EarthGunnery::Attack() {
	AlienArmy* alienArmy = pGame->GetAlienArmy();

	int remainingCapacity = attackCapacity;

	int droneCapacity = floor(attackCapacity / 2.0);
	droneCapacity = min(droneCapacity, alienArmy->GetDroneCount());
	remainingCapacity -= droneCapacity;

	for (int i = 0; i < remainingCapacity; i++) {
		Monester* unit = pGame->GetAlienArmy()->GetMonester();
		if(unit)
			unit->Damage(health, attackPower);
	}

	for (int i = 0; i < floor(droneCapacity / 2.0); i++) {
		Drone* unit = pGame->GetAlienArmy()->GetdroneFront();
		if (unit)
			unit->Damage(health, attackPower);
	}

	for (int i = 0; i < ceil(droneCapacity / 2.0); i++) {
		Drone* unit = pGame->GetAlienArmy()->GetdroneBack();
		if (unit)
			unit->Damage(health, attackPower);
	}

	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "EG " << GetID() << " Shoots ";
		pGame->GetAlienArmy()->PrintArenaList();
	}
	pGame->GetAlienArmy()->RestoreAliveUnits();
}
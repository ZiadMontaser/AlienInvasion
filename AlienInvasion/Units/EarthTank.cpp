#include "EarthTank.h"

#include <cmath>
#include <cmath>

#include "../Game.h"
#include "Monester.h"
#include "AlienSoldier.h"

void EarthTank::Attack()
{
	AlienArmy* alienArmy= pGame->GetAlienArmy();

	int remainingCapacity = attackCapacity;

	int soldierCapacity = 0;
	if (pGame->GetEarthArmy()->IsLowSoldiersMode()) {
		soldierCapacity = floor(remainingCapacity / 2.0);
		soldierCapacity = min(soldierCapacity, alienArmy->GetMonstersCount());
	}
	remainingCapacity -= soldierCapacity;


	for (int i = 0; i < remainingCapacity; i++) {
		Monester* unit = pGame->GetAlienArmy()->GetMonester();
		if (unit)
			unit->Damage(health, attackPower);
	}

	if (pGame->GetEarthArmy()->IsLowSoldiersMode()) {
		for (int i = 0; i < soldierCapacity; i++) {
			AlienSoldier* unit = pGame->GetAlienArmy()->GetSoldier();
			if (unit)
				unit->Damage(health, attackPower);
		}
	}

	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "ET " << GetID() << " ";
		pGame->GetAlienArmy()->PrintArenaList();
	}
	pGame->GetAlienArmy()->RestoreAliveUnits();
}

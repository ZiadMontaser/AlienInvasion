#include "EarthTank.h"

#include <cmath>
#include "../Game.h"
#include "Monester.h"
#include "AlienSoldier.h"

void EarthTank::Attack()
{
	double capacity = attackCapacity;
	if (pGame->GetEarthArmy()->IsLowSoldiersMode()) capacity /= 2;

	for (int i = 0; i < floor(capacity); i++) {
		Monester* unit = pGame->GetAlienArmy()->GetMonester();
		if (unit)
			unit->Damage(health, attackPower);
	}

	if (pGame->GetEarthArmy()->IsLowSoldiersMode()) {
		for (int i = 0; i < ceil(capacity); i++) {
			AlienSoldier* unit = pGame->GetAlienArmy()->GetSoldier();
			if (unit)
				unit->Damage(health, attackPower);
		}
	}

	cout << "ET " << GetID();
	pGame->GetAlienArmy()->PrintArenaList();
	pGame->GetAlienArmy()->RestoreAliveUnits();
}

#include "EarthGunnery.h"
#include <cmath>

#include "../Game.h"
#include "Monester.h"
#include "Drones.h"

void EarthGunnery::Attack() {

	double capacity = attackCapacity / 2;

	for (int i = 0; i < floor(capacity); i++) {
		Monester* unit = pGame->GetAlienArmy()->GetMonester();
		if(unit)
			unit->Damage(health, attackPower);
	}

	capacity = ceil(capacity) / 2;

	for (int i = 0; i < floor(capacity); i++) {
		Drone* unit = pGame->GetAlienArmy()->GetdroneFront();
		if (unit)
			unit->Damage(health, attackPower);
	}

	//for (int i = 0; i < ceil(capacity); i++) {
	//	Drone* unit = pGame->GetAlienArmy()->GetdroneBack();
	//	if (unit)
	//		unit->Damage(health, attackPower);
	//}

	cout << "ES " << GetID();
	pGame->GetAlienArmy()->PrintArenaList();
	pGame->GetAlienArmy()->RestoreAliveUnits();

}
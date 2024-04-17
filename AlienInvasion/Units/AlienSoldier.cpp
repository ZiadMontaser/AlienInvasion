#include "AlienSoldier.h"
#include "EarthSoldier.h"
#include "../Game.h"


void AlienSoldier::Attack() {

	for (int i = 0; i < attackCapacity; i++) {

		EarthSoldier* soldier = pGame->GetEarthArmy()->GetSoldier();
		if (soldier) soldier->Damage(health , attackPower);
	}
	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "AS " << GetID() << " Shots ";
		pGame->GetEarthArmy()->PrintArenaList();
		pGame->GetEarthArmy()->RestoreAliveUnits();
	}
}
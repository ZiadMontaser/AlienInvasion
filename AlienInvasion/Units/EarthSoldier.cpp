#include "EarthSoldier.h"
#include "AlienSoldier.h"
#include "../Game.h"



void EarthSoldier::Attack() {

	for (int i = 0; i < attackCapacity; i++) {

		AlienSoldier* soldier = pGame->GetAlienArmy()->GetSoldier();
		if (soldier) soldier->Damage(health , attackPower);
	}
	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "ES " << GetID() << " ";
		pGame->GetAlienArmy()->PrintArenaList();
		pGame->GetAlienArmy()->RestoreAliveUnits();
	}
}
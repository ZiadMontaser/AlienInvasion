#include "EarthSoldier.h"
#include "AlienSoldier.h"
#include "../Game.h"



void EarthSoldier::Attack() {

	for (int i = 0; i < attackCapacity; i++) {

		AlienSoldier* soldier = pGame->GetAlienArmy()->GetSoldier();
		if (soldier) soldier->Damage(attackPower);
	}

}
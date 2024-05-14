#include "EarthSoldier.h"
#include "AlienSoldier.h"
#include "../Game.h"



void EarthSoldier::Attack() {

	for (int i = 0; i < attackCapacity; i++) {
		if (IsInfected()) {
			EarthSoldier* soldier = pGame->GetEarthArmy()->GetSoldier();
			if (soldier) soldier->Damage(health, attackPower);
		}
		else {
			AlienSoldier* soldier = pGame->GetAlienArmy()->GetSoldier();
			if (soldier) soldier->Damage(health, attackPower);
		}
	}
	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "ES " << GetID() << " ";
		if (IsInfected()) {
			pGame->GetEarthArmy()->PrintArenaList();
			pGame->GetEarthArmy()->RestoreAliveUnits();
		}
		else {
			
			pGame->GetAlienArmy()->PrintArenaList();
			pGame->GetAlienArmy()->RestoreAliveUnits();
		}
	}
}

void EarthSoldier::infectSoldier(EarthSoldier* sol)
{
	if (IsInfected())
	{
		if (sol && !sol->IsInfected())
		{
			sol->Infect();
		}
	}
}

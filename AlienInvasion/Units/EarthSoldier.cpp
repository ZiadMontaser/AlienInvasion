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
		cout << "ES " << this << " Shoots ";
		if (IsInfected()) {
			pGame->GetEarthArmy()->PrintArenaList();
		}
		else {
			
			pGame->GetAlienArmy()->PrintArenaList();
		}
	}

	if (IsInfected()) {
		pGame->GetEarthArmy()->RestoreAliveUnits();
	}
	else {
		pGame->GetAlienArmy()->RestoreAliveUnits();
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

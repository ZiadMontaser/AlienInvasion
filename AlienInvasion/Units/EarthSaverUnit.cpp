
#include "EarthSaverunit.h"
#include "AlienSoldier.h"
#include "../Game.h"



void EarthSaverUnit::Attack() {

	for (int i = 0; i < attackCapacity; i++) {
		AlienSoldier* soldier = pGame->GetAlienArmy()->GetSoldier();
		if (soldier) soldier->Damage(health, attackPower);
	}
	if (pGame->GetUIMode() == UIMode::Interactive) {
		cout << "ESV " << GetID() << " ";

		pGame->GetAlienArmy()->PrintArenaList();
		pGame->GetAlienArmy()->RestoreAliveUnits();
	}
}

void EarthSaverUnit::KILL()
{
	pGame->ReportDeadUnit(this);
}

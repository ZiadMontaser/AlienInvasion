#include "EarthTank.h"
#include "../Game.h"
#include "Monester.h"
void EarthTank::Attack()
{
	for (int i = 0; i < attackCapacity; i++) {
		//TODO
		//Monester* unit = pGame->GetAlienArmy()->GetMonsters();
		//unit->Damage(health, attackPower);
	}

	if (pGame->GetEarthArmy()->IsLowSoldiersMode()) {
		for (int i = 0; i < attackCapacity; i++) {
			//TODO
			//EarthSoldier* unit = pGame->GetAlienArmy()->GetSoldier();
			//unit->Damage(health, attackPower);
		}
	}
}

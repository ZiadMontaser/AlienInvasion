#include "Monester.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "../Game.h"
void Monester::Attack()
{
	for (int i = 0; i < attackCapacity; i++)
	{
		EarthSoldier* Sunit = pGame->GetEarthArmy()->GetSoldier();
		EarthTank* Tunit = pGame->GetEarthArmy()->GetTank();
		if (Sunit)
			Sunit->Damage(health, attackPower);
		if (Tunit)
			Tunit->Damage(health, attackPower);
	}
	cout << "AM " << GetID() << " shots: ";
	pGame->GetEarthArmy()->PrintArenaList();
	pGame->GetEarthArmy()->RestoreAliveUnits();
}

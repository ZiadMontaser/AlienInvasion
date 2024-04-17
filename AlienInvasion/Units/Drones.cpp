#include "Drones.h"
#include "EarthGunnery.h"
#include "Monester.h"
#include "../Game.h"
void Drone::Attack()
{
		for (int i = 0; i < attackCapacity; i++)
		{
			EarthGunnery* Gunit = pGame->GetEarthArmy()->GetGunnery();
			EarthTank* Tunit = pGame->GetEarthArmy()->GetTank();
			if (Gunit)
				Gunit->Damage(health, attackPower);
			if (Tunit)
				Tunit->Damage(health, attackPower);
		}
		cout << "AD " << GetID() << " shots: ";
		pGame->GetEarthArmy()->PrintArenaList();
		pGame->GetEarthArmy()->RestoreAliveUnits();
}

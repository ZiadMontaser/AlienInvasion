#include "Drones.h"
#include "EarthGunnery.h"
#include "Monester.h"
#include "../Game.h"
void Drone::Attack()
{
		EarthTank* Tunit = nullptr;
		EarthGunnery* Gunit = nullptr;
		int remaincap = attackCapacity % 2;
		for (int i = 0; i < attackCapacity / 2; i++)
		{
			Gunit = pGame->GetEarthArmy()->GetGunnery();
			if (Gunit)
				Gunit->Damage(health, attackPower);
			else
			{
				Tunit = pGame->GetEarthArmy()->GetTank();
				if (Tunit)
					Tunit->Damage(health, attackPower);
			}
		}
		for (int i = 0; i < attackCapacity / 2; i++)
		{
			Tunit = pGame->GetEarthArmy()->GetTank();
			if (Tunit)
				Tunit->Damage(health, attackPower);
			else
			{
				Gunit = pGame->GetEarthArmy()->GetGunnery();
				if (Gunit)
					Gunit->Damage(health, attackPower);
			}
		}
		if (remaincap)
		{
			int ran = rand() % 2;
			Tunit = pGame->GetEarthArmy()->GetTank();
			Gunit = pGame->GetEarthArmy()->GetGunnery();
			if (ran)
			{
				if (Tunit)
					Tunit->Damage(health, attackPower);
				else if (Gunit)
					Gunit->Damage(health, attackPower);
			}
			else
			{
				if (Gunit)
					Gunit->Damage(health, attackPower);
				else if (Tunit)
					Tunit->Damage(health, attackPower);
			}
		}
		if (pGame->GetUIMode() == UIMode::Interactive)
		{
			cout << "AD " << GetID() << " Shots: ";
			pGame->GetEarthArmy()->PrintArenaList();
			pGame->GetEarthArmy()->RestoreAliveUnits();
		}
}

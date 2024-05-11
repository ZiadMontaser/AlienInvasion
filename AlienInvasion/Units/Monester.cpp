#include "Monester.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "../Game.h"
void Monester::Attack()
{
	EarthSoldier* Sunit = nullptr;
	EarthTank* Tunit = nullptr;
	EarthSaverUnit* Sv = NULL;
	int remaincap = attackCapacity % 2;
	for (int i = 0; i < attackCapacity / 2; i++)
	{
		Sunit = pGame->GetEarthArmy()->GetSoldier();
		Sv = pGame->GetEarthArmy()->GetSaverUnit();
		if (Sunit)
			Sunit->Damage(health, attackPower);
		else if (Sv) {
			Sv->Damage(health, attackPower);
		}
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
			Sv = pGame->GetEarthArmy()->GetSaverUnit();
			Sunit = pGame->GetEarthArmy()->GetSoldier();
			if (Sunit)
				Sunit->Damage(health, attackPower);
			else if (Sv) {
				Sv->Damage(health, attackPower);
			}
		}
	}
	if (remaincap)
	{
		int ran = rand() % 2;
		Tunit = pGame->GetEarthArmy()->GetTank();
		Sunit = pGame->GetEarthArmy()->GetSoldier();
		Sv = pGame->GetEarthArmy()->GetSaverUnit();
		if (ran)
		{
			if (Tunit)
				Tunit->Damage(health, attackPower);
			else if (Sunit)
				Sunit->Damage(health, attackPower);
			else if (Sv) {
				Sv->Damage(health, attackPower);
			}
		}
		else
		{
			if (Sunit)
				Sunit->Damage(health, attackPower);
			else if (Sv) {
				Sv->Damage(health, attackPower);
			}
			else if (Tunit)
				Tunit->Damage(health, attackPower);
		}
	}
	if (pGame->GetUIMode() == UIMode::Interactive)
	{
		cout << "AM " << GetID() << " Shots: ";
		pGame->GetEarthArmy()->PrintArenaList();
		pGame->GetEarthArmy()->RestoreAliveUnits();
	}
}

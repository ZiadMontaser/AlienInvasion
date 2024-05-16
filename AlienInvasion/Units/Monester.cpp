#include "Monester.h"
#include "EarthSoldier.h"
#include "EarthTank.h"
#include "../Game.h"
void Monester::Attack()
{
	EarthSoldier* Sunit = nullptr;
	EarthTank* Tunit = nullptr;
	EarthSaverUnit* Sv = NULL;
	LinkedQueue<EarthSoldier*> infectedList;

	int remaincap = attackCapacity % 2;
	for (int i = 0; i < attackCapacity / 2; i++)
	{
		Sunit = pGame->GetEarthArmy()->GetSoldier();
		Sv = pGame->GetEarthArmy()->GetSaverUnit();
		if (Sunit) {
			int prob = rand() % 100;
			if (prob <= infectionProb) {
				if(!Sunit->IsInfected()) infectedList.enqueue(Sunit);
				Sunit->Infect();
			}
			else
				Sunit->Damage(health, attackPower);
		}
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
		cout << "AM " << GetID() << " Shoots: ";
		pGame->GetEarthArmy()->PrintArenaList();

		if (!infectedList.isEmpty()) {
			cout << u8"❗ " << CSI"33m" << "AM " << this << CSI"33m" << " tryed to infect " << CSI"0m";
			infectedList.print();
		}
	}
	pGame->GetEarthArmy()->RestoreAliveUnits();
}

#include <iostream>
#include "Unit.h"
#include "../Game.h"

void Unit::Damage(double attackerHealth, double attackerPower)

{
	double Thedamage = (attackerPower * (attackerHealth / 100)) / sqrt(health);

	health -= Thedamage;

	EarthSoldier* S = dynamic_cast<EarthSoldier*>(this);
	EarthTank* T = dynamic_cast<EarthTank*>(this);

	if (health <= 0) {

		pGame->ReportDeadUnit(this);
	}
}

void Unit::Heal(double HUpower, double HUhealth)
{
	double theheal = (HUpower * (HUhealth / 100)) / sqrt(health);
	health += theheal;
	if (health > 0.2 * MaxHealth)
	{
		pGame->ReportHealedUnit(this);
	}
}
std::ostream& operator<<(std::ostream& out, Unit* unit) {
	if(unit)
		cout << unit->GetID();
	return out;
}
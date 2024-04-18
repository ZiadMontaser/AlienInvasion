#include <iostream>
#include "Unit.h"
#include "../Game.h"

void Unit::Damage(double attackerHealth, double attackerPower)

{
	double Thedamage = (attackerPower * (attackerHealth / 100)) / sqrt(health);

	health -= Thedamage;

	if (health <= 0) {

		pGame->ReportDeadUnit(this);
	}
}

void Unit::Heal(double HUpower, double HUhealth)
{
	double theheal = (HUpower * (HUhealth / 100)) / sqrt(health);
	health += theheal;
}
std::ostream& operator<<(std::ostream& out, Unit* unit) {
	if(unit)
		cout << unit->GetID();
	return out;
}
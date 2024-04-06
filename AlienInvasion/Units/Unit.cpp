#include "Unit.h"
#include "../Game.h"
void Unit::Damage(double attackerHealth, double attackerPower)

{
	double Thedamage = (attackerPower * (attackerHealth / 100)) / sqrt(health);

	health -= Thedamage;

	if (health <= 0) {

		pGame->ReportDeadPlayer(this);
	}
}


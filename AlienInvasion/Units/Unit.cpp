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
	health += theheal * (isInfected ? 0.5 : 1);
	if (health > 0.2 * MaxHealth)
	{
		pGame->ReportHealedUnit(this);
	}
}

void Unit::Infect() { 
	isInfected = !isImune;
}
void Unit::TreatInfection() { 
	isImune = true;
	isInfected = false;
}

std::ostream& operator<<(std::ostream& out, Unit* unit) {
	if (unit) {
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		if(unit->IsInfected())
			SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
		cout << unit->GetID(); 
		cout <<(unit->IsInfected() ? u8"🦠" : "");
		SetConsoleTextAttribute(hConsole, FOREGROUND_WHITE);
	}
	return out;
}
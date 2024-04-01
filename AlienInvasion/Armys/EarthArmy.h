#pragma once
#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"

#include "../Units/EarthSoldier.h"

class EarthArmy
{
private:
	LinkedQueue<EarthSoldier*> Soldiers;

	ArrayStack<Unit*> ArenaList;

public:
	void Attack();

	void AddSoldier();
	EarthSoldier* GetSoldier();


	void RestoreAliveUnitsFromArena();
};
#endif // !EARTH_ARMY_H
#pragma once
#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"

#include "../Units/AlienSoldier.h"

class AlienArmy
{
	LinkedQueue<AlienSoldier*> Soldiers;

	ArrayStack<Unit*> ArenaList;
	

public:
	AlienSoldier* GetSoldier();
	void AddSoldier(AlienSoldier* soldiers);

	void Attack();

	void RestoreAliveUnitsFromArena();
};

#endif // !ALIEN_ARMY_H
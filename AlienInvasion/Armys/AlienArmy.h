#pragma once
#ifndef ALIEN_ARMY_H
#define ALIEN_ARMY_H

#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"
#include "../DataStructures/DoublyEndedQueue.h"


#include "../Units/AlienSoldier.h"
#include "../Units/Monester.h"
#include "../Units/Drones.h"

class AlienArmy
{
	LinkedQueue<AlienSoldier*> Soldiers;
	Monester* Monesters[10000];
	DoublyEndedQueue<Drone*> Drones;

	ArrayStack<Unit*> ArenaList;

	int Cap_Monesters = 0;
	/// if needed
	//int Cap_Soliders = 0;
	//int Cap_Drones = 0;
	

public:
	AlienSoldier* GetSoldier();
	void AddSoldier(AlienSoldier* soldiers);
	void AddMonester(Monester* M);
	void AddDrone(Drone* D);

	void Attack();

	void RestoreAliveUnitsFromArena();
};

#endif // !ALIEN_ARMY_H
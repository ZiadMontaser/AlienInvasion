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
public:
	LinkedQueue<AlienSoldier*> Soldiers;
	Monester* Monesters[1000];
	DoublyEndedQueue<Drone*> Drones;

	ArrayStack<Unit*> ArenaList;

	int Count_Monesters = 0;
	/// if needed
	//int Count_Soliders = 0;
	//int Count_Drones = 0;
	

public:
	AlienArmy() {
		for (int i = 0; i < 1000; i++)
			Monesters[i] = NULL;
	}
	AlienSoldier* GetSoldier();
	Monester* GetMonester();
	Drone* GetdroneFront();
	Drone* GetdroneBack();

	void AddSoldier(AlienSoldier* soldiers);
	void AddMonester(Monester* M);
	void AddDrone(Drone* D);

	int GetSoldiersCount() const;

	void Attack();

	void RestoreAliveUnits();

	void Print() const;
};

#endif // !ALIEN_ARMY_H
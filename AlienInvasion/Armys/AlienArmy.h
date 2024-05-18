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
	Game* pGame;
	LinkedQueue<AlienSoldier*> Soldiers;
	Monester* Monesters[10000];
	DoublyEndedQueue<Drone*> Drones;

	ArrayStack<Unit*> ArenaList;

	int Count_Monesters = 0;
	/// if needed
	//int Count_Soliders = 0;
	//int Count_Drones = 0;
	

public:
	AlienArmy(Game *game):pGame(game) {
		for (int i = 0; i < 1000; i++)
			Monesters[i] = NULL;
	}
	AlienSoldier* GetSoldier();
	Monester* GetMonester();
	Monester* GetMonesterTofight();
	Drone* GetdroneFront();
	Drone* GetdroneBack();

	void AddSoldier(AlienSoldier* soldiers);
	void AddMonester(Monester* M);
	void AddDrone(Drone* D);

	int GetSoldiersCount() const;
	int GetMonstersCount() const;
	int GetDroneCount() const;
	int GetAlienCount();
	void Attack();

	void RestoreAliveUnits();

	void Print() const;
	void PrintArenaList() const { ArenaList.print(); };
};

#endif // !ALIEN_ARMY_H
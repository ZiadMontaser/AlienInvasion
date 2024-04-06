#pragma once
#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"
#include "../DataStructures/PriorityQueue.h"

#include "../Units/EarthSoldier.h"
#include "../Units/EarthGunnery.h"
#include "../Units/EarthTank.h"


class EarthArmy
{
private:
	LinkedQueue<EarthSoldier*> Soldiers;
	ArrayStack<EarthTank*> Tanks;
	PriorityQueue<EarthGunnery*> Gunnery;

	ArrayStack<Unit*> ArenaList;

	int Cap_Soliders = 0;
	/// if needed
	//int Cap_Tanks = 0;     
	//int Cap_Gunnery = 0;


    

public:
	void Attack();

	void AddSoldier(EarthSoldier* Him);
	void AddTank(EarthTank* T);
	void AddGunnery(EarthGunnery* G);

	EarthSoldier* GetSolider();
	EarthTank* GetTank();
	EarthGunnery* GetGunnery();

	EarthSoldier* GetSoldier();


	void RestoreAliveUnitsFromArena();
};
#endif // !EARTH_ARMY_H
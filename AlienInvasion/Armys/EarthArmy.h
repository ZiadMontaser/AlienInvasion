#pragma once
#ifndef EARTH_ARMY_H
#define EARTH_ARMY_H

#include "../DataStructures/LinkedQueue.h"
#include "../DataStructures/ArrayStack.h"
#include "../DataStructures/PriorityQueue.h"

#include "../Units/EarthSoldier.h"
#include "../Units/EarthGunnery.h"
#include "../Units/EarthTank.h"
#include "../Units/HealUnit.h"

class EarthArmy
{
//public:
	Game* pGame;

	LinkedQueue<EarthSoldier*> Soldiers;
	ArrayStack<EarthTank*> Tanks;
	PriorityQueue<EarthGunnery*> Gunnery;
	ArrayStack<HealUnit*> healUnits;

	ArrayStack<Unit*> ArenaList;
	PriorityQueue<EarthSoldier*> soldierUnitMaintenanceList;
	LinkedQueue<EarthTank*> tankUnitMaintenanceList;


	bool isLowSoldiersMode = false;
    

public:
	EarthArmy(Game* game):pGame(game){}

	void Attack();

	void AddSoldier(EarthSoldier* Him);
	void AddTank(EarthTank* T);
	void AddGunnery(EarthGunnery* G);
	void AddHealUnit(HealUnit* G);

	void MoveUnitToUML(Unit* unit);

	EarthSoldier* GetSoldier();
	EarthTank* GetTank();
	EarthGunnery* GetGunnery();
	Unit* SelectUnitFromUML();

	int GetSoldiersCount() const;
	int IsLowSoldiersMode() const;

	void RestoreAliveUnits();
	void Print() const;
	void PrintArenaList() const { ArenaList.print(); };
	//void KillHealUnit(HealUnit*);
};
#endif // !EARTH_ARMY_H
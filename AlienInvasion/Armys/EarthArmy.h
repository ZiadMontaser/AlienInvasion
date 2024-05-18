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
#include "../Units/EarthSaverUnit.h"


class EarthArmy
{
//public:
	Game* pGame;

	LinkedQueue<EarthSoldier*> Soldiers;
	ArrayStack<EarthTank*> Tanks;
	PriorityQueue<EarthGunnery*> Gunnery;
	ArrayStack<HealUnit*> healUnits;
	LinkedQueue<EarthSaverUnit*> AlliedArmy;

	ArrayStack<Unit*> ArenaList;
	PriorityQueue<EarthSoldier*> soldierUnitMaintenanceList;
	LinkedQueue<EarthTank*> tankUnitMaintenanceList;

	bool isLowSoldiersMode = false;
	int InfectedSoldiersCount = 0;
	int InjuredInfectedSoldiersCount = 0;
	bool Emergency = false;
	int healedcount = 0;

	int totalInfectedLifeTime = 0;

public:
	EarthArmy(Game* game):pGame(game){}

	void Attack();

	void AddSoldier(EarthSoldier* Him);
	void AddTank(EarthTank* T);
	void AddGunnery(EarthGunnery* G);
	void AddHealUnit(HealUnit* G);
	void AddSaverUnit(EarthSaverUnit* Sv);

	void MoveUnitToUML(Unit* unit);
	int GetInfectedCount();
	void SetEmergency(bool);
	bool EmergencyState();
	void infectionspread();

	EarthSoldier* GetSoldier();
	EarthTank* GetTank();
	EarthGunnery* GetGunnery();
	EarthSaverUnit* GetSaverUnit();
	void RemoveReinforcement();
    void RemoveHealUnit();
	Unit* SelectUnitFromUML();

	int GetTotalUnitsCount() const;

	int GetSoldiersCount() const;
	int GetTankCount() const;
	int GetGunneryCount() const;
	int GetHealUnitsCount() const;
	int GetSoldierCountinUML() const;
	int GetTankCountinUML() const;
	int GetHealedCount() const;
	int GetLifeTimeInfectedUnits()const;
	double GetInfectionPercentage()const;
	int IsLowSoldiersMode() const;

	void ReportInfectedUnit(Unit* unit);
	void ReportTreatedUnit(Unit* unit);
	void RestoreAliveUnits();
	void Print() const;
	void PrintArenaList() const { ArenaList.print(); };
	//void KillHealUnit(HealUnit*);
};
#endif // !EARTH_ARMY_H
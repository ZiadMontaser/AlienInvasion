#include "HealUnit.h"
#include "../Game.h"
#include "EarthSoldier.h"
#include "EarthTank.h"


void HealUnit::Attack() {
    bool heals = false;
    LinkedQueue<Unit*> TempHealList;
   // LinkedQueue <Unit*> ALLHealedList;
    for (int i = 0; i < attackCapacity; i++)
    {
        Unit* ToHeal = pGame->GetEarthArmy()->SelectUnitFromUML();
        
        EarthTank* tank = dynamic_cast<EarthTank*>(ToHeal);
        EarthSoldier* soldier = dynamic_cast<EarthSoldier*>(ToHeal);

        if (tank) {
            if (pGame->GetTimeStamp() - tank->GetTimeStartHeal() < 10) {
                heals = true;
                ToHeal->Heal(attackPower, health);
                TempHealList.enqueue(ToHeal);
            }
            else {
                pGame->ReportDeadUnit(ToHeal);
            }
        }
        if  (soldier) {
            if (pGame->GetTimeStamp() - soldier->GetTimestartHeal() < 10)
            {
                heals = true; 
                if (ToHeal->IsInfected()) {
                    ToHeal->TreatInfection();
                    pGame->GetEarthArmy()->ReportTreatedUnit(ToHeal);
                }
                else {
                    ToHeal->Heal(attackPower, health);
                }

                TempHealList.enqueue(ToHeal);
            }
            else {
                pGame->ReportDeadUnit(ToHeal);
            }
        }

    }


    if (heals) {
        if (pGame->GetUIMode() == UIMode::Interactive) {
            cout << "EHU " << GetID() << " Heals💊 ";
            TempHealList.print();
        }


        Unit* Return;
        while (TempHealList.dequeue(Return)) {

            if (Return->GetHealth() < 0.2 * Return->GetMaxHealth()) {

                pGame->GetEarthArmy()->MoveUnitToUML(Return);
            }
            else {

                EarthTank* T = dynamic_cast<EarthTank*> (Return);
                EarthSoldier* S = dynamic_cast <EarthSoldier*> (Return);

                if (S) {
                    S->ResetHealTime();
                }
                else if (T)
                    T->ResetHealTime();

            }
        }

        pGame->GetEarthArmy()->RemoveHealUnit();
        this->KILL();

    }
}

void HealUnit::KILL()
{
    pGame->ReportDeadUnit(this);
}

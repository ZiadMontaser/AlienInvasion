#include "HealUnit.h"
#include "../Game.h"
#include "EarthSoldier.h"
#include "EarthTank.h"


void HealUnit::Attack() {

    LinkedQueue<Unit*> TempHealList;
   // LinkedQueue <Unit*> ALLHealedList;
    for (int i = 0; i < attackCapacity; i++)
    {
        Unit* ToHeal = pGame->GetEarthArmy()->SelectUnitFromUML();
        ToHeal->Heal(attackPower, health);
        TempHealList.enqueue(ToHeal);

    }
    if (pGame->GetUIMode() == UIMode::Interactive) {
        cout << "EHU " << GetID() << " Heals ";
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
                pGame->GetEarthArmy()->AddSoldier(S);
            }
            else if (T)
                pGame->GetEarthArmy()->AddTank(T);

        }
    }

   

    this->KILL();
}

void HealUnit::KILL()
{
    pGame->ReportDeadUnit(this);
}

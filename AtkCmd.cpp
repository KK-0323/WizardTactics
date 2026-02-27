#include "AtkCmd.h"
#include "Engine\\GameObject.h"

void AtkCmd::Execute(GameObject* pActor, GameObject* pTarget)
{
	int damage = pActor->CalculateDamage(10, pTarget);
	pTarget->ApplyDamage(damage);
}

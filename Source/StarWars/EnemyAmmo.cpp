// Copyright Max Botvinev, 2021


#include "EnemyAmmo.h"

#include "GameController.h"

void AEnemyAmmo::DestroyAmmo()
{
	FDamageEvent Event;
	AGameController::GetInstance()->TakeDamage(DamageAmount, Event, nullptr, this);
	Destroy();
}

// Copyright Max Botvinev, 2021

#include "EnemyUnitAI.h"

AEnemyUnitAI::AEnemyUnitAI()
{
	State = Undefined;
}

void AEnemyUnitAI::BeginMovement()
{
	TargetLocation = FVector::ZeroVector;
	MoveToLocation(TargetLocation);
}

void AEnemyUnitAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(State < Atack)
	{
		const auto AssignedPawn = GetPawn();

		if(AssignedPawn)
		{
			if (FVector::Dist(AssignedPawn->GetActorLocation(), TargetLocation) < FireDistance)
			{
				StopMovement();

				State = Atack;
			}
			else
			{
				State = Move;
			}
		}
	}
}

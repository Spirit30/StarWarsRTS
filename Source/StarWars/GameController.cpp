// Copyright Max Botvinev, 2021

#include "GameController.h"
#include "EnemyUnit.h"
#include "EnemyUnitAI.h"

AGameController::AGameController()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AGameController::BeginPlay()
{
	Super::BeginPlay();
	
	NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	
	SpawnUnits();
}

void AGameController::SpawnUnits() const
{
	int32 CurrentEnemyToSpawn = EnemiesInWave;
	
	while(CurrentEnemyToSpawn > 0)
	{
		--CurrentEnemyToSpawn;
	
		TrySpawnUnit();
	}
}

void AGameController::TrySpawnUnit() const
{
	FNavLocation RefRandomSpawnLocation; 
	if(NavigationSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, SpawnRadius, RefRandomSpawnLocation))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		const auto EnemyUnit = GetWorld()->SpawnActor<AEnemyUnit>(EnemyBlueprintClass, RefRandomSpawnLocation.Location, FRotator::ZeroRotator, SpawnParameters);

		const auto EnemyUnitAI = GetWorld()->SpawnActor<AEnemyUnitAI>(EnemyAIClass, RefRandomSpawnLocation.Location, FRotator::ZeroRotator, SpawnParameters);
		EnemyUnitAI->Possess(EnemyUnit);
		EnemyUnitAI->BeginMovement();
	}
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


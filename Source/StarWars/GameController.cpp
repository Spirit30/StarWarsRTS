// Copyright Max Botvinev, 2021

#include "GameController.h"
#include "EnemyUnit.h"
#include "EnemyUnitAI.h"
#include "Kismet/GameplayStatics.h"

AGameController* AGameController::Instance = nullptr;

AGameController::AGameController()
{
	PrimaryActorTick.bCanEverTick = true;

	Instance = this;

	CargoHP = 100;
}

AGameController* AGameController::GetInstance()
{
	return Instance;
}

int32 AGameController::GetEnemyUnitsCount() const
{
	return  EnemyUnitsCount;
}

void AGameController::OnDestroyUnit()
{
	--EnemyUnitsCount;

	if(EnemyUnitsCount <= 0)
	{
		HUD->OnGameOver(true);
	}
}

void AGameController::BeginPlay()
{
	Super::BeginPlay();
	
	NavigationSystem = UNavigationSystemV1::GetCurrent(GetWorld());
	HUD = Cast<AGameHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
	
	SpawnUnits();
}

void AGameController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AGameController::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	CargoHP -= DamageAmount;
	
	if(!IsGameOver)
	{
		HUD->SetCargoHP(CargoHP);

		if(CargoHP <= 0)
		{
			IsGameOver = true;
			HUD->OnGameOver(false);
			SpawnCargoFires();
		}
	}
	
	return  DamageAmount;
}

bool AGameController::GetIsGameOver() const
{
	return IsGameOver;
}

void AGameController::SpawnUnits()
{
	for(int i = 0; i < EnemiesInWave; ++i)
	{
		TrySpawnUnit();
	}
}

void AGameController::TrySpawnUnit()
{
	FNavLocation RefRandomSpawnLocation;
	const auto SpawnOrigin = FMath::VRand().GetUnsafeNormal() * SpawnAxisLength;
	
	if(NavigationSystem->GetRandomPointInNavigableRadius(SpawnOrigin, SpawnRadius, RefRandomSpawnLocation))
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		const auto EnemyUnit = GetWorld()->SpawnActor<AEnemyUnit>(EnemyBlueprintClass, RefRandomSpawnLocation.Location, FRotator::ZeroRotator, SpawnParameters);

		const auto EnemyUnitAI = GetWorld()->SpawnActor<AEnemyUnitAI>(EnemyAIClass, RefRandomSpawnLocation.Location, FRotator::ZeroRotator, SpawnParameters);
		EnemyUnitAI->Possess(EnemyUnit);
		EnemyUnitAI->BeginMovement();
		++EnemyUnitsCount;
	}
}

void AGameController::SpawnCargoFires()
{
	for(int i = 0; i < FireLocations.Num(); ++i)
	{
		UGameplayStatics ::SpawnEmitterAtLocation(
         GetWorld(),
         Fire,
         FireLocations[i],
         FRotator::ZeroRotator,
         FVector::OneVector * FireScale);
	}
}


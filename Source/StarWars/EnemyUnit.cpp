// Copyright Max Botvinev, 2021

#include "EnemyUnit.h"

#include "EnemyAmmo.h"
#include "EnemyUnitAI.h"
#include "GameUtils.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyUnit::AEnemyUnit()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AEnemyUnit::SetHighlighted(bool Flag) const
{
	HighlightComponent->SetHiddenInGame(!Flag);
}

void AEnemyUnit::BeginPlay()
{
	Super::BeginPlay();

	HighlightComponent = Cast<UStaticMeshComponent>(GameUtils::GetComponentByName(this, UStaticMeshComponent::StaticClass(), HighlightComponentName));

	SetHighlighted(false);
}

void AEnemyUnit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AIController = GetController();

	if(AIController)
	{
		const auto EnemyAI = Cast<AEnemyUnitAI>(AIController);
		
		if(EnemyAI->State == AEnemyUnitAI::EnemyAIState::Atack)
		{
			TryShoot(DeltaTime);
		}
	}
}

void AEnemyUnit::TryShoot(float DeltaTime)
{
	if(ShootTimer <= 0)
	{
		ShootTimer += ShootInterval;

		Shoot();
	}
	else
	{
		ShootTimer -= DeltaTime;
	}
}

void AEnemyUnit::Shoot() const
{
	const auto SpawnLocation = GetActorLocation();
	const auto SpawnRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), FVector::ZeroVector);
	const auto EnemyAmmo = GetWorld()->SpawnActor<AEnemyAmmo>(EnemyAmmoClass, SpawnLocation, SpawnRotation);
	EnemyAmmo->SetTarget(FVector::ZeroVector);
}

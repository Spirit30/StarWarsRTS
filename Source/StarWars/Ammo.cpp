// Copyright Max Botvinev, 2021

#include "Ammo.h"

#include "Kismet/GameplayStatics.h"

AAmmo::AAmmo()
{
	PrimaryActorTick.bCanEverTick = true;

}

void AAmmo::SetTarget(FVector TargetLocationParam)
{
	TargetLocation = TargetLocationParam;
}

void AAmmo::BeginPlay()
{
	Super::BeginPlay();

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(Sound), FVector::ZeroVector);
}

void AAmmo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(FVector::Distance(GetActorLocation(), TargetLocation) < DestroyDistance)
	{
		DestroyAmmo();
	}
}

void AAmmo::DestroyAmmo()
{
	Destroy();
}
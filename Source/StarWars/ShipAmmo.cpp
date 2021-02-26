// Copyright Max Botvinev, 2021


#include "ShipAmmo.h"
#include "Kismet/GameplayStatics.h"

void AShipAmmo::SetTargetActor(AActor* TargetActor)
{
	TargetEnemy = Cast<AEnemyUnit>(TargetActor);
	SetTarget(TargetEnemy->GetActorLocation());
}

void AShipAmmo::DestroyAmmo()
{
	for(int i = 0; i < Explosions.Num(); ++i)
	{
		const auto Explosion = Explosions[i];
		
		UGameplayStatics ::SpawnEmitterAtLocation(
			GetWorld(),
			Explosion,
			GetActorLocation(),
			FRotator::ZeroRotator,
			FVector(FMath::RandRange(MinExplosionScale, MaxExplosionScale)));
	}

	UGameplayStatics::PlaySoundAtLocation(GetWorld(), Cast<USoundBase>(ExplosionSound), FVector::ZeroVector);
	
	TargetEnemy->Terminate();
	Destroy();
}

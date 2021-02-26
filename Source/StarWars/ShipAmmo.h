// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "Ammo.h"
#include "EnemyUnit.h"

#include "ShipAmmo.generated.h"

/**
 * 
 */
UCLASS()
class STARWARS_API AShipAmmo : public AAmmo
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<UParticleSystem*> Explosions;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MinExplosionScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MaxExplosionScale;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* ExplosionSound;
	
	void SetTargetActor(AActor* TargetActor);

	protected:

	virtual void DestroyAmmo() override;

	private:

	AEnemyUnit* TargetEnemy;
};

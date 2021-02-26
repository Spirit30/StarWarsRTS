// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "Ammo.h"
#include "EnemyAmmo.generated.h"

UCLASS()
class STARWARS_API AEnemyAmmo : public AAmmo
{
	GENERATED_BODY()

	public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageAmount;
	
	virtual void DestroyAmmo() override;
};

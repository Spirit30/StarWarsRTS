// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ammo.generated.h"

UCLASS()
class STARWARS_API AAmmo : public AActor
{
	GENERATED_BODY()
	
public:	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USoundWave* Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DestroyDistance;
	
	AAmmo();
	void SetTarget(FVector TargetLocationParam);
	virtual void Tick(float DeltaTime) override;
	
protected:

	virtual void BeginPlay() override;
	virtual void DestroyAmmo();

private:

	FVector TargetLocation;
};

// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NavigationSystem.h"
#include "GameController.generated.h"

UCLASS()
class STARWARS_API AGameController : public AActor
{
	GENERATED_BODY()
	
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<APawn> EnemyBlueprintClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AController> EnemyAIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemiesInWave;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;
	
	AGameController();
	virtual void Tick(float DeltaTime) override;

protected:

	virtual void BeginPlay() override;

private:
	
	//UClass* EnemyBlueprintClass;
	UNavigationSystemV1* NavigationSystem;

	void SpawnUnits() const;
	void TrySpawnUnit() const;
};

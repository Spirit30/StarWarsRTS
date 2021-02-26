// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameHUD.h"
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
	UParticleSystem* Fire;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 EnemiesInWave;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnAxisLength;  
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnRadius;    

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float FireScale;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FVector> FireLocations;
	
	AGameController();
	static AGameController* GetInstance();
	int32 GetEnemyUnitsCount() const;
	void OnDestroyUnit();
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;
	bool GetIsGameOver() const;

protected:

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;	

private:

	static AGameController* Instance;
	UNavigationSystemV1* NavigationSystem;
	AGameHUD * HUD;
	int32 EnemyUnitsCount;
	float CargoHP;
	bool IsGameOver;

	void SpawnUnits();
	void TrySpawnUnit();
	void SpawnCargoFires();
};

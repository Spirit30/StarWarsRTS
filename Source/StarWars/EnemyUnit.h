// Copyright Max Botvinev, 2021
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "EnemyUnit.generated.h"

UCLASS()
class STARWARS_API AEnemyUnit : public APawn
{
	GENERATED_BODY()

	public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> EnemyAmmoClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float ShootInterval;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString HighlightComponentName;
	
	AEnemyUnit();
	void SetHighlighted(bool Flag) const;

	protected:
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	private:

	UStaticMeshComponent* HighlightComponent;
	
	float ShootTimer;
	
	void TryShoot(float DeltaTime);
	void Shoot() const;
};

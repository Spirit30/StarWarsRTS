// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyUnitAI.generated.h"

UCLASS()
class STARWARS_API AEnemyUnitAI : public AAIController
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float FireDistance;

	AEnemyUnitAI();
	void BeginMovement();
	virtual void Tick(float DeltaTime) override;

	enum EnemyAIState
	{
		Undefined,
		Move,
		Atack
	};

	EnemyAIState State;

private:

	FVector TargetLocation;
};

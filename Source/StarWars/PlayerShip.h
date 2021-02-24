// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"


#include "EnemyUnit.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "GameHUD.h"
#include "PlayerShip.generated.h"

UCLASS()
class STARWARS_API APlayerShip : public APawn
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString GunsMeshComponentName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> GunSocketNames;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ShipNavigationTargetTag;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString EnemyTargetTag;
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Altitude;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoveSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float AltitudeSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float RotationSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float UpdateMinDistance;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DotProductToShoot;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ShipAmmoClass;
	
	APlayerShip();
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void OnLeftMouseButton();
	void TryShootAll();
	void ShootAll() const;
	void Shoot(FVector SpawnStartLocation) const;

private:

	//References
	APlayerController* PlayerController;
	UCameraComponent* CameraComponent;
	UStaticMeshComponent* GunMeshComponent;
	AGameHUD* GameHUD;

	//Data
	FVector InitialCameraLocationOffset;
	FRotator InitialCameraRotation;

	//Reference Variables
	AEnemyUnit* TargetEnemy;
	
	//Variables
	FHitResult RefHitResult;
	FVector TargetLocation;
	float TargetDistance;
	FVector CurrentLocation;

	void UpdateAimScreenLocation() const;
	void UpdateLocationSmooth(float DeltaTime);
	void UpdateAltitude(float DeltaTime);
	void ApplyLocation();
	void UpdateRotationSmooth(float DeltaTime);
	void UpdateCamera() const;
};
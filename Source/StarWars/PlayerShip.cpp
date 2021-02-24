// Copyright Max Botvinev, 2021

#include "PlayerShip.h"

#include "DrawDebugHelpers.h"
#include "GameUtils.h"
#include "ShipAmmo.h"
#include "Engine/EngineTypes.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

APlayerShip::APlayerShip()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerShip::BeginPlay()
{
	Super::BeginPlay();

	CameraComponent = Cast<UCameraComponent>(GetComponentByClass(UCameraComponent::StaticClass()));
	GameHUD = Cast<AGameHUD>(PlayerController->GetHUD());

	const auto InitialLocation = GetActorLocation();
	const auto InitialCameraLocation = CameraComponent->GetComponentLocation();
	InitialCameraLocationOffset = InitialCameraLocation - InitialLocation;
	InitialCameraRotation = UKismetMathLibrary::FindLookAtRotation(InitialCameraLocation, InitialLocation);

	GunMeshComponent = Cast<UStaticMeshComponent>(GameUtils::GetComponentByName(this, UStaticMesh::StaticClass(), GunsMeshComponentName));

	CurrentLocation = FVector::UpVector * 1000;
}

void APlayerShip::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateAimScreenLocation();

	UpdateAltitude(DeltaTime);

	UpdateRotationSmooth(DeltaTime);

	TargetDistance = FVector::Dist(GetActorLocation(), TargetLocation);

	if (TargetDistance > UpdateMinDistance)
	{
		UpdateLocationSmooth(DeltaTime);
	}

	UpdateCamera();

	ApplyLocation();

	TryShootAll();
}

void APlayerShip::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	PlayerInputComponent->BindKey(EKeys::LeftMouseButton, IE_Pressed, this, &APlayerShip::OnLeftMouseButton);
}

void APlayerShip::UpdateAimScreenLocation() const
{
	float LocationX;
	float LocationY;
	if (PlayerController->GetMousePosition(LocationX, LocationY))
	{
		GameHUD->SetAimLocationPoint(LocationX, LocationY);
	}
}

void APlayerShip::UpdateLocationSmooth(float DeltaTime)
{
	const auto FromLocation = GetActorLocation();
	const auto NextLocation = FMath::Lerp(FromLocation, TargetLocation, DeltaTime * MoveSpeed / TargetDistance);

	CurrentLocation.X = NextLocation.X;
	CurrentLocation.Y = NextLocation.Y;
}

void APlayerShip::UpdateAltitude(float DeltaTime)
{
	const FVector Location = GetActorLocation();
	const float LENGTH = 10000;
	const FVector DownPoint = Location + GetActorForwardVector() * LENGTH + FVector::DownVector * LENGTH;
	FHitResult OutHitResult;

	DrawDebugLine(GetWorld(), Location, DownPoint, FColor::Green);

	if (GetWorld()->LineTraceSingleByChannel(OutHitResult, Location, DownPoint, ECC_Visibility))
	{
		const float CurrentAltitude = FMath::Lerp(CurrentLocation.Z, OutHitResult.Location.Z + Altitude, DeltaTime * AltitudeSpeed / OutHitResult.Distance);
		TargetLocation.Z = CurrentAltitude;
		CurrentLocation.Z = CurrentAltitude;

		DrawDebugSphere(GetWorld(), OutHitResult.Location, 10, 1, FColor::Green);
	}
}

void APlayerShip::ApplyLocation()
{
	SetActorLocation(CurrentLocation);
}

void APlayerShip::UpdateRotationSmooth(float DeltaTime)
{
	const auto FromRotation = GetActorRotation();
	const auto LookRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), TargetLocation);
	const auto NextRotation = FMath::Lerp(FromRotation, LookRotation, DeltaTime * RotationSpeed);

	SetActorRotation(NextRotation);
}

void APlayerShip::UpdateCamera() const
{
	CameraComponent->SetWorldLocation(GetActorLocation() + InitialCameraLocationOffset);
	CameraComponent->SetWorldRotation(InitialCameraRotation);
}

void APlayerShip::OnLeftMouseButton()
{
	PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, RefHitResult);

	if (RefHitResult.IsValidBlockingHit())
	{
		TargetLocation.X = RefHitResult.Location.X;
		TargetLocation.Y = RefHitResult.Location.Y;

		if(RefHitResult.Actor->ActorHasTag(FName(EnemyTargetTag)))
		{
			if(TargetEnemy)
			{
				TargetEnemy->SetHighlighted(false);
			}

			TargetEnemy = Cast<AEnemyUnit>(RefHitResult.Actor.Get());
			TargetEnemy->SetHighlighted(true);
		}
	}
}

void APlayerShip::TryShootAll()
{
	if(TargetEnemy)
	{
		auto TargetDirection = TargetEnemy->GetActorLocation() - GetActorLocation();
		auto ShipDirection = GetActorForwardVector();

		//Convert to flat space.
		TargetDirection = FVector(TargetDirection.X, TargetDirection.Y, 0);
		ShipDirection = FVector(ShipDirection.X, ShipDirection.Y, 0);
		
		const auto DotProduct = FVector::DotProduct(ShipDirection, TargetDirection.GetUnsafeNormal());
		
		if(DotProduct  > DotProductToShoot)
		{
			ShootAll();
		
			TargetEnemy = nullptr;
		}
	}
}

void APlayerShip::ShootAll() const
{
	for (int32 i = 0; i < GunSocketNames.Num(); ++i)
	{
		const auto GunSocketName = GunSocketNames[i];
		const auto ShootStartLocation = GunMeshComponent->GetSocketLocation(GunSocketName);
		Shoot(ShootStartLocation);
	}
}

void APlayerShip::Shoot(FVector SpawnStartLocation) const
{
	const auto SpawnTargetLocation = TargetEnemy->GetActorLocation();
	const auto SpawnRotation = UKismetMathLibrary::FindLookAtRotation(SpawnStartLocation, SpawnTargetLocation);
	const auto ShipAmmo = GetWorld()->SpawnActor<AShipAmmo>(ShipAmmoClass, SpawnStartLocation, SpawnRotation);
	ShipAmmo->SetTargetActor(TargetEnemy);
}

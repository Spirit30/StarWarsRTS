// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GameHUD.generated.h"

/**
 * 
 */
UCLASS()
class STARWARS_API AGameHUD : public AHUD
{
	GENERATED_BODY()

private:

	float AimLocationX;
	float AimLocationY;
	
protected:

	virtual void DrawHUD() override;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture* AimTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Scale;

	void SetAimLocationPoint(const float aimLocationX, const float aimLocationY);
};

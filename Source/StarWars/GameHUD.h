// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "GameHUD.generated.h"

UCLASS()
class STARWARS_API AGameHUD : public AHUD
{
	GENERATED_BODY()
	public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture* AimTexture;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float Scale;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<UUserWidget> HUDWidgetClass;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName UnitsCountTextName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName MissionCompleteTextName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName GameOverTextName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ResultOverlayImageName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName RestartButtonName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CargoHPBarName;
	
	void SetAimLocationPoint(const float AimLocationXParam, const float AimLocationYParam);
	void SetUnitsCount(int32 UnitsCount) const;
	void SetCargoHP(float HP) const;
	void OnGameOver(bool IsWin) const;

	UFUNCTION()
	void OnRestartButtonClick();

	protected:

	virtual void BeginPlay() override;
	virtual void DrawHUD() override;

	private:

	UUserWidget* HUDWidget;
	UTextBlock* UnitsCountTextBox;
	UProgressBar* CargoHPBar;
	UTextBlock* MissionCompleteTextBox;
	UTextBlock* GameOverTextBox;
	UImage* ResultOverlayImage;
	UButton* RestartButton;
	
	float AimLocationX;
	float AimLocationY;
};

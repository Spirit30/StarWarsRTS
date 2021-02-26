// Copyright Max Botvinev, 2021

#include "GameHUD.h" 

#include "GameController.h"
#include "Kismet/GameplayStatics.h"

void AGameHUD::SetAimLocationPoint(const float AimLocationXParam, const float AimLocationYParam)
{
	AimLocationX = AimLocationXParam;
	AimLocationY = AimLocationYParam;
}

void AGameHUD::SetUnitsCount(int32 UnitsCount) const
{
	if(UnitsCountTextBox)
	{
		const auto TextString = FString::Printf(TEXT("ENEMY UNITS: %d"), UnitsCount);
		const auto Text = FText::FromString(TextString);
		UnitsCountTextBox->SetText(Text);
	}
}

void AGameHUD::SetCargoHP(float HP) const
{
	CargoHPBar->SetPercent(HP / 100);
}

void AGameHUD::OnGameOver(bool IsWin) const
{
	if(IsWin)
	{
		MissionCompleteTextBox->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		GameOverTextBox->SetVisibility(ESlateVisibility::Visible);
	}
	
	ResultOverlayImage->SetVisibility(ESlateVisibility::Visible);
	RestartButton->SetVisibility(ESlateVisibility::Visible);
}

void AGameHUD::OnRestartButtonClick()
{
	UGameplayStatics::OpenLevel(this, FName(GetWorld()->GetName()), false);
}

void AGameHUD::BeginPlay()
{
	HUDWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
	HUDWidget->AddToViewport();

	UnitsCountTextBox = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(UnitsCountTextName));
	MissionCompleteTextBox = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(MissionCompleteTextName));
	GameOverTextBox = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(GameOverTextName));
	ResultOverlayImage = Cast<UImage>(HUDWidget->GetWidgetFromName(ResultOverlayImageName));
	RestartButton = Cast<UButton>(HUDWidget->GetWidgetFromName(RestartButtonName));
	CargoHPBar = Cast<UProgressBar>(HUDWidget->GetWidgetFromName(CargoHPBarName));

	MissionCompleteTextBox->SetVisibility(ESlateVisibility::Collapsed);
	GameOverTextBox->SetVisibility(ESlateVisibility::Collapsed);
	ResultOverlayImage->SetVisibility(ESlateVisibility::Collapsed);
	RestartButton->SetVisibility(ESlateVisibility::Collapsed);
	
	RestartButton->OnClicked.AddDynamic(this, &AGameHUD::OnRestartButtonClick);
}

void AGameHUD::DrawHUD()
{
	const float Half = 0.5f;
	const float TextureCenterOffsetX = AimTexture->GetSurfaceWidth() * Half * Scale;
	const float TextureCenterOffsetY = AimTexture->GetSurfaceHeight() * Half * Scale;
	DrawTextureSimple(AimTexture, AimLocationX - TextureCenterOffsetX, AimLocationY - TextureCenterOffsetY, Scale, false);

	SetUnitsCount(AGameController::GetInstance()->GetEnemyUnitsCount());
}
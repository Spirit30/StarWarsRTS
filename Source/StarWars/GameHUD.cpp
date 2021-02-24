// Copyright Max Botvinev, 2021

#include "GameHUD.h"

void AGameHUD::DrawHUD()
{
	const float Half = 0.5f;
	const float TextureCenterOffsetX = AimTexture->GetSurfaceWidth() * Half * Scale;
	const float TextureCenterOffsetY = AimTexture->GetSurfaceHeight() * Half * Scale;
	DrawTextureSimple(AimTexture, AimLocationX - TextureCenterOffsetX, AimLocationY - TextureCenterOffsetY, Scale, false);
}

void AGameHUD::SetAimLocationPoint(const float aimLocationX, const float aimLocationY)
{
	AimLocationX = aimLocationX;
	AimLocationY = aimLocationY;
}
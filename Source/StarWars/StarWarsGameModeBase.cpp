// Copyright Epic Games, Inc. All Rights Reserved.


#include "StarWarsGameModeBase.h"

#include "GameFramework/HUD.h"

AStarWarsGameModeBase::AStarWarsGameModeBase()
{
	const auto PLAYER_PAWN_BP_LOCATION = TEXT("/Game/Blueprints/BP_PlayerShip");
	static ConstructorHelpers::FClassFinder<APawn> BPPlayerPawnClass(PLAYER_PAWN_BP_LOCATION);

	if (BPPlayerPawnClass.Class != nullptr)
	{
		DefaultPawnClass = BPPlayerPawnClass.Class;
	}

	const auto GAME_HUD_BP_LOCATION = TEXT("/Game/Blueprints/BP_GameHUD");
	static ConstructorHelpers::FClassFinder<AHUD> BPGameHUDClass(GAME_HUD_BP_LOCATION);

	if (BPGameHUDClass.Class != nullptr)
	{
		HUDClass = BPGameHUDClass.Class;
	}
}
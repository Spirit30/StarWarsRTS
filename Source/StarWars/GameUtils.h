// Copyright Max Botvinev, 2021

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

/**
 * 
 */
class STARWARS_API GameUtils
{
public:

	static TArray<UActorComponent*> GetComponentsByName(AActor* Actor, TSubclassOf<UActorComponent> ComponentClass, FString Name);
	static UActorComponent* GetComponentByName(AActor* Actor, TSubclassOf<UActorComponent> ComponentClass, FString Name);
};
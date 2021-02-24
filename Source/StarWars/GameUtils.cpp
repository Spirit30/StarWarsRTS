// Copyright Max Botvinev, 2021

#include "GameUtils.h"

TArray<UActorComponent*> GameUtils::GetComponentsByName(AActor* Actor, TSubclassOf<UActorComponent> ComponentClass, FString Name)
{
	TArray<UActorComponent*> result;

	auto components = Actor->GetComponents();

	for (auto component : components)
	{
		if (component->GetName() == Name)
		{
			result.Add(component);
		}
	}

	return result;
}

UActorComponent* GameUtils::GetComponentByName(AActor* Actor, TSubclassOf<UActorComponent> ComponentClass, FString Name)
{
	TArray<UActorComponent*> components = GetComponentsByName(Actor, ComponentClass, Name);

	return components.Num() > 0 ? components[0] : nullptr;
}
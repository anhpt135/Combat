// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayAbilitySystem/Attributes/BasicAttributeSet.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	Health = 100.f;
	MaxHealth = 100.f;
	Mana = 50.f;
	MaxMana = 50.f;
}

void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
}

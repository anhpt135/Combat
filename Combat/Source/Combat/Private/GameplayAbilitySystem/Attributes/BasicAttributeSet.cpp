// Fill out your copyright notice in the Description page of Project Settings.

#include "GameplayAbilitySystem/Attributes/BasicAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemComponent.h"
#include "GameplayTagContainer.h"

UBasicAttributeSet::UBasicAttributeSet()
{
	// Giá trị khởi tạo mặc định cho các thuộc tính
	Health = 100.f;
	MaxHealth = 100.f;
	Mana = 100.f;
	MaxMana = 100.f;
}

void UBasicAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);

	// Ràng buộc giá trị Máu không vượt qua Máu tối đa và không nhỏ hơn 0 trước khi áp dụng thay đổi
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxHealth());
	}
	// Ràng buộc giá trị Mana không vượt qua Mana tối đa và không nhỏ hơn 0 trước khi áp dụng thay đổi
	else if (Attribute == GetManaAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.0f, GetMaxMana());
	}
}

void UBasicAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	// Xử lý sau khi một Gameplay Effect đã thay đổi Máu
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(GetHealth());

		// Xử lý logic khi nhân vật hết Máu (Chết)
		if (GetHealth() <= 0.f)
		{
			if(UAbilitySystemComponent* ASC = GetOwningAbilitySystemComponent())
			{
				// Thêm Tag State.Dead để báo hiệu nhân vật đã chết
				ASC->AddLooseGameplayTag(FGameplayTag::RequestGameplayTag(FName("State.Dead")));
			}
		}
	}
	// Xử lý sau khi một Gameplay Effect đã thay đổi Mana
	else if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(GetMana());
	}
}

// Cấu hình đồng bộ hóa các thuộc tính qua mạng (Replication)
void UBasicAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	// Đồng bộ các thuộc tính cho tất cả mọi người (Always)
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UBasicAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);
}
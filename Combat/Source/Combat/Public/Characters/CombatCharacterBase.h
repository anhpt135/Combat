// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "Interfaces/CleanupAfterDeathInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class UInputAction;
class UAbilitySystemComponent;
class UBasicAttributeSet;
class UGameplayEffect;

// Enum định nghĩa các Input ID cho Gameplay Ability System
UENUM(BlueprintType)
enum class EMyAbilityInputID : uint8
{	None,
	Confirm,
	Cancel,
	Death,
	Dash,
	BiteAttack,
	ClawAttack,
};

UCLASS()
class COMBAT_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface, public ICleanupAfterDeathInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacterBase();
	
	// IAbilitySystemInterface implementation (Kế thừa để dùng Gameplay Ability System)
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	// ICleanupAfterDeathInterface implementation
	virtual void CleanupAfterDeath_Implementation() override;
	
	// Thành phần Ability System chính của nhân vật
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	// Bộ thuộc tính cơ bản (Máu, Mana, v.v.)
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	UBasicAttributeSet* BasicAttributeSet;
	
	// Các InputAction để điều khiển nhân vật
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Attributes|Input")
	TObjectPtr<UInputAction> DashInput;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Attributes|Input")
	TObjectPtr<UInputAction> BiteAttackInput;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Attributes|Input")
	TObjectPtr<UInputAction> ClawAttackInput;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Khởi tạo thông tin cho Ability System khi nhân vật được Controller điều khiển (Server)
	virtual void PossessedBy(AController* NewController) override;
	
	// Khởi tạo thông tin cho Ability System trên Client
	virtual void OnRep_PlayerState() override;

	// Hiệu ứng Gameplay hồi Mana
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> ManaRegenEffect;
	
	void HamCallback_Dash_Started();
	void HamCallback_Bite_Started();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};

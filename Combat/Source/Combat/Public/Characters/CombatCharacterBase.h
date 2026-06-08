// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CombatCharacterBase.generated.h"

class UInputAction;
class UAbilitySystemComponent;
class UBasicAttributeSet;
class UGameplayEffect;

UENUM(BlueprintType)
enum class EMyAbilityInputID : uint8
{	None,
	Confirm,
	Cancel,
	BiteAttack,
	ClawAttack,
};

UCLASS()
class COMBAT_API ACombatCharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACombatCharacterBase();
	
	// IAbilitySystemInterface implementation
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Abilities")
	UAbilitySystemComponent* AbilitySystemComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Attributes")
	UBasicAttributeSet* BasicAttributeSet;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Attributes|Input")
	TObjectPtr<UInputAction> BiteAttackInput;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, Category = "Attributes|Input")
	TObjectPtr<UInputAction> ClawAttackInput;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Abilities")
	TSubclassOf<UGameplayEffect> ManaRegenEffect;
	
	void HamCallback_Bite_Started();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/CombatCharacterBase.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameplayAbilitySystem/Attributes/BasicAttributeSet.h"
#include "GameplayEffect.h"

// Sets default values
ACombatCharacterBase::ACombatCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(35.f, 96.0f);
	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; 
	GetCharacterMovement()->RotationRate = FRotator(0.f, 500.f, 0.f); 
	
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.f;
	
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	BasicAttributeSet = CreateDefaultSubobject<UBasicAttributeSet>(TEXT("BasicAttributeSet"));

}

UAbilitySystemComponent* ACombatCharacterBase::GetAbilitySystemComponent() const
{	return AbilitySystemComponent;
}

// Called when the game starts or when spawned
void ACombatCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACombatCharacterBase::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (ManaRegenEffect)
	{
		FGameplayEffectContextHandle Context = AbilitySystemComponent->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(ManaRegenEffect, 1, Context);
		if (SpecHandle.IsValid())
		{
			AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
}

void ACombatCharacterBase::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}

// Called every frame
void ACombatCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ACombatCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	UEnhancedInputComponent* EIC = Cast<UEnhancedInputComponent>(PlayerInputComponent);
	
	if (DashInput)
	{
		EIC->BindAction(DashInput, ETriggerEvent::Started, this, &ACombatCharacterBase::HamCallback_Dash_Started);
		//EIC->BindAction(BiteAttackInput, ETriggerEvent::Completed, this, &HamCallback_Bite_Completed);
	}
	
	if (BiteAttackInput)
	{
		EIC->BindAction(BiteAttackInput, ETriggerEvent::Started, this, &ACombatCharacterBase::HamCallback_Bite_Started);
		//EIC->BindAction(BiteAttackInput, ETriggerEvent::Completed, this, &HamCallback_Bite_Completed);
	}
	
	if (ClawAttackInput)
	{
		//EIC->BindAction(ClawAttackInput, ETriggerEvent::Started, this, &HamCallback_Claw_Started);
		//EIC->BindAction(ClawAttackInput, ETriggerEvent::Completed, this, &HamCallback_Claw_Completed);
	}
	
}

void ACombatCharacterBase::HamCallback_Dash_Started()
{	
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EMyAbilityInputID::Dash));
}

void ACombatCharacterBase::HamCallback_Bite_Started()
{
	AbilitySystemComponent->AbilityLocalInputPressed(static_cast<int32>(EMyAbilityInputID::BiteAttack));
}

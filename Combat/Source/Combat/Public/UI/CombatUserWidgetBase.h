// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "CombatUserWidgetBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FLoaiEventNguoiChoiTatHuongDan);
/**
 * 
 */
UCLASS()
class COMBAT_API UCombatUserWidgetBase : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;
	
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> NutBamDongUI;	
	
	UPROPERTY(BlueprintAssignable, Category = "UICuaem")
	FLoaiEventNguoiChoiTatHuongDan OnTatUIDismiss;

private:
	UFUNCTION()
	void DepTiemUIThoi();
};

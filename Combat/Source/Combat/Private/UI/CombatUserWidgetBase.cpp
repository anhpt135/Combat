// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/CombatUserWidgetBase.h"

void UCombatUserWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();
	
	UE_LOG(LogTemp, Warning, TEXT("UI cua em da duoc tao"));
	if (NutBamDongUI)
	{
		NutBamDongUI->OnClicked.AddDynamic(this, &UCombatUserWidgetBase::DepTiemUIThoi);
	}
	
	SetIsFocusable(true);
	SetKeyboardFocus();
	
}

FReply UCombatUserWidgetBase::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("EM NHAN DUOC NUT BAM ROI NHA"));
	DepTiemUIThoi();
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

FReply UCombatUserWidgetBase::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("EM NHAN DUOC CHUOT BAM ROI NHA"));
	DepTiemUIThoi();
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UCombatUserWidgetBase::DepTiemUIThoi()
{
	UE_LOG(LogTemp, Warning, TEXT("UI cua em da duoc dong"));
	RemoveFromParent();
	OnTatHDDuocRoiDo.Broadcast();
}

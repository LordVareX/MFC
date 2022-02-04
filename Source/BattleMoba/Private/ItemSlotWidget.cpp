// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"
#include "Engine.h"

void UItemSlotWidget::NativeConstruct()
{
}

void UItemSlotWidget::NativeOnInitialized()
{
}

FReply UItemSlotWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	FReply reply = Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton/* && IsPressed == false*/)
	{
		//IsPressed = true;
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Slot name: %s"), *ItemID.ToString()));
		return reply;
	}
	return reply;
}

//FReply UItemSlotWidget::NativeOnMouseButtonUp(const FGeometry & InGeometry, const FPointerEvent & InMouseEvent)
//{
//	FReply reply = Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
//	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton && IsPressed == true)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Blue, FString::Printf(TEXT("Released")));
//		IsPressed = false;
//		return reply;
//	}
//	return reply;
//}

//void UItemSlotWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation)
//{
//	Super::NativeOnDragDetected(InGeometry, InMouseEvent, [&]OutOperation);
//}

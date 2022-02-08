// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Border.h"
#include "ItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class BATTLEMOBA_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(meta = (BindWidgetOptional))
		UBorder* IconBorder;

protected:

	bool IsPressed = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
		FName ItemID;

protected:

	virtual void NativeConstruct() override;

	void NativeOnInitialized() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	/*virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;*/

	//virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
};

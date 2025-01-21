// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Custom Includes
#include "Components/TextBlock.h"


#include "CoreMinimal.h"
#include "WidgetBRBase.h"
#include "PointsDisplayWidgetBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API UPointsDisplayWidgetBR : public UWidgetBRBase
{
	GENERATED_BODY()
public:
	UFUNCTION()
	void OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue);


	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget));
	UTextBlock* ValueText = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget));
	UTextBlock* PointsText = nullptr;

	virtual void NativeOnInitialized() override;

#if WITH_EDITOR
	virtual void OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs) override;
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

private:
	int CurrentPoints = 0;
	FText ConvertPointsToText(int32 Points);

	void UpdateWidget();

	

	

};

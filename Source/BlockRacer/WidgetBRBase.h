// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBRBase.generated.h"

/**
 * 
 */
UCLASS(abstract)
class BLOCKRACER_API UWidgetBRBase : public UUserWidget
{
public:
#if WITH_EDITOR
	virtual const FText GetPaletteCategory() override;
#endif

	
	GENERATED_BODY()
	
};

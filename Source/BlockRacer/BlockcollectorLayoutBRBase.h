// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "WidgetBRBase.h"
#include "BlockcollectorLayoutBRBase.generated.h"


class UPointsDisplayWidgetBR;
/**
 * 
 */
UCLASS(Abstract)
class BLOCKRACER_API UBlockcollectorLayoutBRBase : public UWidgetBRBase
{
	GENERATED_BODY()
public:	
	UPROPERTY(BlueprintReadOnly, Category = "Constituent Controls", meta = (BindWidget))
	UPointsDisplayWidgetBR* PointsDisplay = nullptr;
};

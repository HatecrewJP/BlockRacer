// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom
#include "BlockcollectorLayoutBRBase.h"
#include "CarBR.h"

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HudBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API AHudBR : public AHUD
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UBlockcollectorLayoutBRBase> BlockCollectorLayoutClass = nullptr;


	
	
	void UpdateWidget();
	
protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override; 
private:
	UBlockcollectorLayoutBRBase* BlockCollectorLayout = nullptr;
	ACar* PlayerPawn = nullptr;

};

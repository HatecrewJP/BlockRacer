// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectableBlockBaseBR.generated.h"

UCLASS()
class BLOCKRACER_API ACollectableBlockBaseBR : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectableBlockBaseBR();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	int GetBlockValue();


	void SetBlockValue(int NewBlockValue);

private:
	int BlockValue = 10;
	const int DefaultBlockValue = BlockValue;
};

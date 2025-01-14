// Fill out your copyright notice in the Description page of Project Settings.


#include "CollectableBlockBaseBR.h"

// Sets default values
ACollectableBlockBaseBR::ACollectableBlockBaseBR()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ACollectableBlockBaseBR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectableBlockBaseBR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int ACollectableBlockBaseBR::GetBlockValue()
{
	return BlockValue;
}

void ACollectableBlockBaseBR::SetBlockValue(int NewBlockValue)
{
	this->BlockValue = NewBlockValue;
}

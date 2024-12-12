// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultTestCharacterBR.h"

// Sets default values
ADefaultTestCharacterBR::ADefaultTestCharacterBR()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADefaultTestCharacterBR::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADefaultTestCharacterBR::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ADefaultTestCharacterBR::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


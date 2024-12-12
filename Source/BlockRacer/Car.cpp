// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"


// Sets default values
ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = true;

	if(CollisionBox) SetRootComponent(CollisionBox);
	
}

void ACar::Accelerate( )
{
	
	if(Speed < MAX_SPEED)
	{	
		Speed = Speed + Acceleration;
		Speed = FMath::Clamp(Speed,0,MAX_SPEED);
	}
}



void ACar::Break( )
{
	if(Speed > 0)
	{
		uint16 BreakingDeceleration = BreakingMultiplier * Deceleration;
		if(Speed > BreakingDeceleration)
		{
			Speed = Speed - BreakingDeceleration;
		}
		else
		{
			Speed = 0;
		}
		Speed = FMath::Clamp(Speed,0,MAX_SPEED);
	}
}

void ACar::Move()
{
	if(Speed>0)
	{
		FVector CurrentLocation = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		FVector NewLocation = CurrentLocation + ForwardVector * Speed;
		SetActorLocation(NewLocation);
	}
}

// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ACar::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("%u"),Speed);
	Super::Tick(DeltaTime);
	if(Speed > 0)
	{
		Speed = Speed - Deceleration;
		Speed = FMath::Clamp(Speed,0,MAX_SPEED);
		Move();
	}
	




}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



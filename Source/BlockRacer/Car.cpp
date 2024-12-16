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

void ACar::Move(float DeltaTime)
{
	if(Speed>0)
	
	{
		FVector CurrentLocation = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		
		//Convert Speed into from m/s into cm/s
		uint16 SpeedMS = Speed * 1000;

		FVector NewLocation = CurrentLocation + ForwardVector * SpeedMS * DeltaTime;
		SetActorLocation(NewLocation);
	}
}



void ACar::Turn(TurnDirection Direction)
{

	if(Direction != 1 && Direction != -1)
	{
		UE_LOG(LogTemp,Error,TEXT("Invalid Turn Direction %d"),Direction);
		return;
	}
	float RotationAngle = TurnAngle * Direction;
	AddControllerYawInput(RotationAngle);
}




// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ACar::Tick(float DeltaTime)
{
	//UE_LOG(LogTemp, Warning, TEXT("%u"),Speed);
	Super::Tick(DeltaTime);
	if(Speed > 0)
	{
		Speed = Speed - Deceleration;
		Speed = FMath::Clamp(Speed,0,MAX_SPEED);
		Move(DeltaTime);
		
	}
	//UE_LOG(LogTemp,Display,TEXT("%s"),*GetActorLocation().ToString());




}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



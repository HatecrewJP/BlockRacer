// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Misc/App.h"

// Sets default values
ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = true;

	if(CollisionBox) SetRootComponent(CollisionBox);
	
}

void ACar::Accelerate(int8 Direction)
{
	
	if(Speed < MAX_SPEED_FOREWARD && Speed > MAX_SPEED_BACKWARD)
	{	
		Speed = Speed + Acceleration * Direction;
		Speed = FMath::Clamp(Speed,MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD);
	}
}



void ACar::Break( )
{
	if(Speed > 0)
	{
		uint16 BreakingDeceleration = BreakingMultiplier * Deceleration;
		Speed = Speed - BreakingDeceleration;
		Speed = FMath::Clamp(Speed,MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD);
	}

}
void ACar::Steering(int8 Direction)
{
	if(Direction != 1 && Direction != -1)
	{
		UE_LOG(LogTemp,Error,TEXT("Invalid Turn Direction %d"),Direction);
		return;
	}
	float DeltaTime = FApp::GetDeltaTime();

	CurrentSteeringAngle = FMath::FInterpTo<float,float,float,float>(CurrentSteeringAngle,MaxSteeringAngle,DeltaTime,4.0f) * Direction;
}
void ACar::Move(float DeltaTime)
{
	if(Speed>MAX_SPEED_BACKWARD)
	
	{
		FVector CurrentLocation = GetActorLocation();
		FVector ForwardVector = GetActorForwardVector();
		
		//Convert Speed into from m/s into cm/s
		int32 SpeedMS = Speed * 1000;


		FVector NewLocation = CurrentLocation + ForwardVector * SpeedMS * DeltaTime;
		SetActorLocation(NewLocation);
	}
}



void ACar::Turn()
{
	float DeltaTime = FApp::GetDeltaTime();
	//UE_LOG(LogTemp,Log,TEXT("%f"),DeltaTime);
	FRotator NewRotation;
	float RotationAngle = CurrentSteeringAngle * Speed * SpeedToRotationFactor;
	//UE_LOG(LogTemp,Log,TEXT("%f"),RotationAngle);
	NewRotation.Yaw = RotationAngle;
	//UE_LOG(LogTemp,Log,TEXT("%s"),*NewRotation.ToString());

	AddActorWorldRotation(NewRotation);
	CurrentSteeringAngle = 0;
}




// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void ACar::Tick(float DeltaTime)
{
	UE_LOG(LogTemp, Warning, TEXT("%d"),Speed);
	Super::Tick(DeltaTime);
	if(Speed > 0)
	{
		Speed = Speed - Deceleration;
		Speed = FMath::Clamp(Speed,0,MAX_SPEED_FOREWARD);
		Move(DeltaTime);
		Turn();
	}
	else if(Speed >= MAX_SPEED_BACKWARD && Speed < 0)
	{
		Speed = Speed + Deceleration;
		Speed = FMath::Clamp(Speed,MAX_SPEED_BACKWARD,0);
		Move(DeltaTime);
		Turn();
	}
	//UE_LOG(LogTemp,Display,TEXT("%s"),*GetActorLocation().ToString());




}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}



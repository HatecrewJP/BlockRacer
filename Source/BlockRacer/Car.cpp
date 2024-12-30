// Fill out your copyright notice in the Description page of Project Settings.


#include "Car.h"
#include "Misc/App.h"

// Sets default values
ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACar::Accelerate(int8 Direction)
{
	
	if(CurrentSpeed <= MAX_SPEED_FOREWARD && CurrentSpeed >= MAX_SPEED_BACKWARD)
	{	
		float DirectedMaxSpeed;
		if(Direction ==  1) DirectedMaxSpeed = MAX_SPEED_FOREWARD;
		else 
		if(Direction == -1) DirectedMaxSpeed = MAX_SPEED_BACKWARD;
		else 
		if(Direction ==  0) DirectedMaxSpeed = 0;
		else
		{
			UE_LOG(LogTemp,Error,TEXT("Invalid Move Direction: %d. Couldn't initialize \"DirectedMaxSpeed\""),Direction);
			return;
		}
		float DeltaTime = FApp::GetDeltaTime();

		/*
			FInterpTo acts as a movement acceleration function.
		  	If Direction ==  0, then the CurrentSpeed converges towards 0
		  	If Direction ==  1, then the CurrentSpeed converges towards MaxSpeedForeward
			If Direction == -1, then the CurrentSpeed converges towards MaxSpeedBackward
		*/
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed,DirectedMaxSpeed,DeltaTime,4.0f);
		
	}
}

void ACar::Break()
{

	if(CurrentSpeed > 0)
	{
		float BreakingDeceleration = BreakingMultiplier * Deceleration;
		CurrentSpeed -= BreakingDeceleration;
	}
	if(CurrentSpeed < 0)
	{
		float BreakingDeceleration = BreakingMultiplier * Deceleration;
		CurrentSpeed += BreakingDeceleration;
	}
	CurrentSpeed = FMath::Clamp(CurrentSpeed,MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD);
}

void ACar::Move(float DeltaTime)
{
	if(CurrentSpeed >= MAX_SPEED_BACKWARD)
	{
		
		FVector ForwardVector = GetActorForwardVector();
		FVector DeltaLocation = ForwardVector * CurrentSpeed;
		
		AddActorWorldOffset(DeltaLocation);
		//UE_LOG(LogTemp,Display,TEXT("Delta Location: %s"),*DeltaLocation.ToString());
		//UE_LOG(LogTemp,Log,TEXT("Speed: %f \n"),CurrentSpeed);
	}
}

void ACar::Steering(int8 Direction)
{
	if(Direction != 1 && Direction != -1 && Direction != 0)
	{
		UE_LOG(LogTemp,Error,TEXT("Invalid Turn Direction %d"),Direction);
		return;
	}

	float DeltaTime = FApp::GetDeltaTime();
	float DirectedMaxSteeringAngle = Direction * MaxSteeringAngle;

	/*
		FInterpTo acts as a movement acceleration function.
		If Direction ==  0, then the CurrentSpeed approaches  0
		If Direction ==  1, then the CurrentSpeed approaches  MaxSteeringAngle
		If Direction == -1, then the CurrentSpeed approaches -MaxSteeringAngle

	*/
	CurrentSteeringAngle = FMath::FInterpTo(CurrentSteeringAngle,DirectedMaxSteeringAngle,DeltaTime,4.0f);
	
}

void ACar::Turn()
{
	
	float SpeedToRotationFactor = CalculateLinearSpeedToRotationFactor(CurrentSpeed);


	float DeltaTime = FApp::GetDeltaTime();
	FRotator NewRotation = FRotator::ZeroRotator;
	float RotationAngle = CurrentSteeringAngle * CurrentSpeed * SpeedToRotationFactor;
	NewRotation.Yaw = RotationAngle;
	AddActorWorldRotation(NewRotation);
	//UE_LOG(LogTemp,Display,TEXT("Rotation: %s"),*NewRotation.ToString());
}

float ACar::CalculateLinearSpeedToRotationFactor(float Speed)
{
	/*
		Calculates "SpeedToRotationFactor".
		The faster the car gets, the less it should depend on the current speed.
		Therefore the SpeedToRotationFactor gets lower when the car is faster.
		For simplicity reasons this function is a linear function mx+n and the SpeedToRotationFactor is calculated based on the MAX_SPEED_FOREWARD.
	*/
	

	float n = MinFactor;
	float m = (MaxFactor / MAX_SPEED_FOREWARD - MinFactor) / MAX_SPEED_FOREWARD ;

	return m * Speed + n;


}


#pragma region DefaultFunctions
// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Accelerate(MovementDirection);
	Move(DeltaTime);
	Steering(SteeringDirection);
	Turn();
	//UE_LOG(LogTemp,Log,TEXT("MovementDirection: %d \n"),MovementDirection);
	//UE_LOG(LogTemp,Log,TEXT("SteeringDirection: %d \n"),SteeringDirection);
}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

#pragma endregion

#pragma region Getter
float ACar::GetCurrentSpeed()
{
    return this->CurrentSpeed;
}

float ACar::GetCurrentSteeringAngle()
{
    return this->CurrentSteeringAngle;
}
#pragma endregion

#pragma region Setter
void ACar::SetMovementDirection(float Direction)
{
	this->MovementDirection = Direction;
}

void ACar::SetSteeringDirection(float Direction)
{
	this->SteeringDirection = Direction;
}
#pragma endregion

// Fill out your copyright notice in the Description page of Project Settings.

#include "CarBR.h"
#include "Misc/App.h"


UCarAnimInstanceBR* ACar::GetCarAnimInstance()
{
	USceneComponent* CarRootComponent = GetRootComponent();
	checkf(CarRootComponent,TEXT("No Root Component found"))
	TArray<USceneComponent*> CarComponents;
	CarRootComponent->GetChildrenComponents(true,CarComponents);
	for(USceneComponent* CurrentComponent : CarComponents)
	{
		if(CurrentComponent->IsA(USkeletalMeshComponent::StaticClass()))
		{
			UAnimInstance* AnimInstance = Cast<USkeletalMeshComponent>(CurrentComponent)->GetAnimInstance();
			if(AnimInstance)
			{
				if(AnimInstance->IsA(UCarAnimInstanceBR::StaticClass()))
				{
					return Cast<UCarAnimInstanceBR>(AnimInstance);
				}
			}
			
		}
	}
	return nullptr;
	
}

// Sets default values
ACar::ACar()
{
	PrimaryActorTick.bCanEverTick = true;
	

	
}
#pragma region Car Movement
void ACar::MoveCar()
{
	
	Accelerate(MovementDirection);
	Move();
	Steer(SteeringDirection);
	Turn();
}

void ACar::Accelerate(int8 Direction)
{
	
	if(CurrentSpeed <= MAX_SPEED_FOREWARD && CurrentSpeed >= MAX_SPEED_BACKWARD)
	{	
		/*
			Direction ==  1: Car is accelerating forewards
			Direction ==  0; Car is not accelerating
			Direction == -1: Car is accelerating backwards
		*/
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
		CurrentSpeed = FMath::FInterpTo(CurrentSpeed,DirectedMaxSpeed,DeltaTime,1.0f);

		/*
			When Direction == 0 and the CurrentSpeed is in the Intervall [-FInterpSkipAngle,FInterpSkipAngle], the movement is not noticable, but the FInterpTo function takes a lot of time to reach 0.
			To skip this waiting time, CurrentSpeed is set to 0 when CurrentSpeed is in The Intervall [-FInterpSkipAngle,FInterpSkipAngle].
		*/
		float InterpToSkipAngle = 0.2;

		if(CurrentSpeed < InterpToSkipAngle && CurrentSpeed > -InterpToSkipAngle && Direction == 0)
		{
			CurrentSpeed = 0;
		}
		
	}
	checkf(CurrentSpeed >= MAX_SPEED_BACKWARD && CurrentSpeed <= MAX_SPEED_FOREWARD, TEXT("CurrentSpeed is not in the Interval [MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD]."));
}

void ACar::Break()
{

	if(CurrentSpeed > 0)
	{
		float BreakingDeceleration = BreakingMultiplier * CarDeceleration;
		CurrentSpeed -= BreakingDeceleration;
	}
	if(CurrentSpeed < 0)
	{
		float BreakingDeceleration = BreakingMultiplier * CarDeceleration;
		CurrentSpeed += BreakingDeceleration;
	}
	checkf(CurrentSpeed >= MAX_SPEED_BACKWARD && CurrentSpeed <= MAX_SPEED_FOREWARD, TEXT("CurrentSpeed is not in the Interval [MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD]."));
	
}

void ACar::Move()
{
	if(CurrentSpeed >= MAX_SPEED_BACKWARD)
	{

		FVector ForwardVector = GetActorForwardVector();
		FVector DeltaLocation = ForwardVector * CurrentSpeed;
		FVector NewLocation = GetActorLocation() + DeltaLocation;
		
		//GravityOffset is the distance that the car moves towards the ground
		float GravityOffset = CalculateGravityOffset(NewLocation);
		DeltaLocation += FVector(0,0, -GravityOffset);
		
		
		
		this->AddActorWorldOffset(DeltaLocation);
		
	

		

		//UE_LOG(LogTemp,Display,TEXT("CollisionBoxExtent: %s"  ),*CollisionBoxExtent  .ToString());
		//UE_LOG(LogTemp,Display,TEXT("Sweep Start: %s"),*SweepStart.ToString());
		//UE_LOG(LogTemp,Display,TEXT("Sweep End: %s"  ),*SweepEnd  .ToString());
		//UE_LOG(LogTemp,Log,TEXT("GravityOffset: %f"),GravityOffset);
		//UE_LOG(LogTemp,Display,TEXT("Is Hit: %f"),float(IsHit));
		//UE_LOG(LogTemp,Display,TEXT("Delta Location: %s"),*DeltaLocation.ToString());
		//UE_LOG(LogTemp,Log,TEXT("Speed: %f \n"),CurrentSpeed);
	}
	checkf(CurrentSpeed >= MAX_SPEED_BACKWARD && CurrentSpeed <= MAX_SPEED_FOREWARD, TEXT("CurrentSpeed is not in the Interval [MAX_SPEED_BACKWARD,MAX_SPEED_FOREWARD]."));
}

void ACar::Steer(int8 Direction)
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

	/*
		When Direction == 0 and the CurrentSteeringAngle is in the Intervall [-FInterpSkipAngle,FInterpSkipAngle], the movement is almost not noticable, but the FInterpTo function takes a lot of time to reach 0.
		To skip this waiting time, CurrentSteerinAngle is set to 0 when CurrentSteeringAngle is in The Intervall [-FInterpSkipAngle,FInterpSkipAngle].
	*/
	
	float InterpToSkipAngle = 0.02f;
	if(CurrentSteeringAngle < InterpToSkipAngle && CurrentSteeringAngle > -InterpToSkipAngle)// && Direction == 0)
	{
		
		CurrentSteeringAngle = 0;
	}

	checkf(CurrentSteeringAngle >= -MaxSteeringAngle && CurrentSteeringAngle <= MaxSteeringAngle, TEXT("CurrentSteeringAngle is not in the Interval [-MaxSteeringAngle,MaxSteeringAngle]."));
}

void ACar::Turn()
{
	/*
		The RotationAngle depends on the CurrentSpeed.
		When CurrentSpeed increases, the RotationAngle would also increase.
		The desired behaviour is the opposite: At high speeds the car is supposed to steer less than at lower speed.
		To Compensate for this, a SpeedToRotationFactor is calculated based on the CurrentSpeed.
	*/
	float SpeedToRotationFactor = CalculatePseudoLinearSpeedToRotationFactor(CurrentSpeed);
	float DeltaTime = FApp::GetDeltaTime();
	FRotator NewRotation = FRotator::ZeroRotator;
	float RotationAngle = CurrentSteeringAngle * CurrentSpeed * SpeedToRotationFactor;
	NewRotation.Yaw = RotationAngle;
	AddActorWorldRotation(NewRotation);
	//UE_LOG(LogTemp,Display,TEXT("Rotation: %s"),*NewRotation.ToString());


}
#pragma endregion

#pragma region Collsion

float ACar::CalculateDoubleLinearSpeedToRotationFactor(float Speed)
{
	/*
		Calculates "SpeedToRotationFactor".
		The faster the car gets, the less it should depend on the current speed.
		Therefore the SpeedToRotationFactor gets lower when the car is faster.
		To make the car rotate more at lower speeds, two linear functions determine the SpeedToRotationFactor.
		

		
	*/
	float SpeedThresholdToChangeFunction = MAX_SPEED_FOREWARD * 0.2;
	float ThresholdSpeedFactor = (LowSpeedfactor - HighSpeedFactor) * 0.5;
	if(Speed < SpeedThresholdToChangeFunction)
	{
		float n = LowSpeedfactor;
		float m = (LowSpeedfactor / SpeedThresholdToChangeFunction - ThresholdSpeedFactor) / SpeedThresholdToChangeFunction ;
		return m * Speed + n;
	}

	float n = ThresholdSpeedFactor;
	float m = (ThresholdSpeedFactor / MAX_SPEED_FOREWARD - HighSpeedFactor) / MAX_SPEED_FOREWARD ;
	return m * Speed + n;
	

}

float ACar::CalculatePseudoLinearSpeedToRotationFactor(float Speed)
{
	/*
		Calculates "SpeedToRotationFactor".
		The faster the car gets, the less it should depend on the current speed.
		Therefore the SpeedToRotationFactor gets lower when the car is faster.
		For simplicity reasons this function is a pseudo linear function mx+n and the SpeedToRotationFactor is calculated based on the MAX_SPEED_FOREWARD.
		This function tries to compensate different MAX_SPEED_FOREWARD values.
	*/
	float PseudoLinearTweakValue = 0.8;
	float n = HighSpeedFactor;
	float m = (LowSpeedfactor / MAX_SPEED_FOREWARD - HighSpeedFactor) / MAX_SPEED_FOREWARD;
	return m * PseudoLinearTweakValue * Speed + n;
}
float ACar::CalculateTrueLinearSpeedToRotationFactor(float Speed)
{
	/*
		Calculates "SpeedToRotationFactor".
		The faster the car gets, the less it should depend on the current speed.
		Therefore the SpeedToRotationFactor gets lower when the car is faster.
		For simplicity reasons this function is a linear function mx+n and the SpeedToRotationFactor is calculated based on the MAX_SPEED_FOREWARD.
	*/

	float n = LowSpeedfactor;
	float m = (HighSpeedFactor - LowSpeedfactor) / MAX_SPEED_FOREWARD;
	return m * Speed + n;

}

FCollisionShape ACar::GetCollisionBoxWithScale(FVector ScaleVector)
{
	FVector BoxOrigin;
	FVector BoxExtent;
	GetActorBounds(true,BoxOrigin,BoxExtent);

	FVector CollisionBoxExtent = BoxExtent;
	//Add 0.1 to avoid making a Box with one Dimension being 0
	CollisionBoxExtent.X *= ScaleVector.X + 0.1;
	CollisionBoxExtent.Y *= ScaleVector.Y + 0.1;
	CollisionBoxExtent.Z = ScaleVector.Z + 0.1;
	return FCollisionShape::MakeBox(CollisionBoxExtent);
}
FCollisionShape ACar::GetCollisionBox()
{
	FVector BoxOrigin;
	FVector BoxExtent;
	GetActorBounds(true,BoxOrigin,BoxExtent);

	FVector CollisionBoxExtent = BoxExtent;
	//Add 0.1 to avoid making a Box with one Dimension being 0
	CollisionBoxExtent.Z = 0.2;
	return FCollisionShape::MakeBox(CollisionBoxExtent);
}

float ACar::CalculateGravityOffset(FVector Location)
{
	const UWorld* CurrentWorld = GetWorld();
	checkf(CurrentWorld,TEXT("Trying to move the car without an existing world"));

	
	//SweepSingleByChannel parameter declaration
	FVector 			ActorLocation 			= GetActorLocation();
	FVector 			SweepStart 				= ActorLocation - FVector(0,0,-1);
	FVector 			SweepEnd 				= ActorLocation + FVector(0,0,-6);
	ECollisionChannel 	GravityCollisionChannel = ECC_GameTraceChannel1;
	FCollisionShape 	CarGravityCollisionBox 	= GetCollisionBox();
	FHitResult 			HitResult;
	
	bool  IsHit 			= CurrentWorld -> SweepSingleByChannel(HitResult,SweepStart,SweepEnd,FQuat::Identity,GravityCollisionChannel,CarGravityCollisionBox);
	float NewGravityOffset 	= CarGravityConstant;
	if(IsHit)
	{	
		float DistanceToGround = ActorLocation.Z - HitResult.ImpactPoint.Z;
		if(DistanceToGround < CarGravityConstant )
		{
			NewGravityOffset = DistanceToGround;
		}
	}
	//DrawDebugBox(CurrentWorld,Location,CarGravityCollisionBox.GetExtent(),FColor::Red,false,1,0,1);
	return NewGravityOffset;
}



#pragma endregion

#pragma region Points
void ACar::AddPoints(int PointsToAdd)
{
	UpdatePoints(PointsToAdd);
}

void ACar::UpdatePoints(int NewPoints)
{
	int OldPoints = this->CurrentPoints;
	this->CurrentPoints += NewPoints;

	CurrentPoints = FMath::Clamp(CurrentPoints,0,MAX_int32);

	if(OldPoints != CurrentPoints)
	{
		OnPointsChanged.Broadcast(OldPoints,CurrentPoints,MAX_int32);
	}
	

}
void ACar::BroadcastCurrentStats()
{
	OnPointsChanged.Broadcast(CurrentPoints,CurrentPoints,MAX_int32);
}
#pragma endregion

#pragma region DefaultFunctions
// Called when the game starts or when spawned
void ACar::BeginPlay()
{
	Super::BeginPlay();
	
	
	CarAnimInstance = GetCarAnimInstance();
	if(!CarAnimInstance)
	{
		UE_LOG(LogTemp,Error,TEXT("No CarAnimInstance found"))
		return;
	}
	
}

// Called every frame
void ACar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	MoveCar();
	if(CarAnimInstance)
	{
		CarAnimInstance->SetSteeringAngle(CurrentSteeringAngle);
		CarAnimInstance->SetSpeed(CurrentSpeed);
	}
	if(CurrentPoints >= WinCondition)
	{
		this-> SetIsNotActiveInGame();
	}
}

void ACar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

#pragma endregion

#pragma region Getter

bool ACar::GetIsActiveInGame()
{
	return this->IsActiveInGame;
}

float ACar::GetCurrentSpeed()
{
    return this->CurrentSpeed;
}

float ACar::GetCurrentSteeringAngle()
{
    return this->CurrentSteeringAngle;
}

int ACar::GetCurrentPoints()
{
	return this->CurrentPoints;
}
#pragma endregion

#pragma region Setter

void ACar::SetIsNotActiveInGame()
{
	this->IsActiveInGame = false;
}

void ACar::SetMovementDirection(float Direction)
{
	checkf(Direction == 1 || Direction == 0 || Direction == -1, TEXT("Trying to set an invalid MovementDirection. The allowed Direction Values are: 0, 1, -1"));
	this->MovementDirection = Direction;
}

void ACar::SetSteeringDirection(float Direction)
{
	checkf(Direction == 1 || Direction == 0 || Direction == -1, TEXT("Trying to set an invalid SteeringDirection. The allowed Direction Values are: 0, 1, -1"));
	this->SteeringDirection = Direction;
}
#pragma endregion




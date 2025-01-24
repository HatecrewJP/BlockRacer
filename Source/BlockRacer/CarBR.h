// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"
#include "CarAnimInstanceBR.h"

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CarBR.generated.h"





DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FIntStatUpdated,
                                               int32, OldValue,
                                               int32, NewValue,
                                               int32, MaxValue);


UCLASS()
class BLOCKRACER_API ACar : public APawn
{	GENERATED_BODY()
	
public:

	ACar();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveCar();

	UFUNCTION(BlueprintCallable)
	void AddPoints(int PointsToAdd);



#pragma region Car Movement
	//State modification Methods
	void Accelerate(int8 Direction);
	void Break();
	void Steer(int8 Direction);
#pragma endregion

#pragma region Setter
	void SetMovementDirection(float Direction);
	void SetSteeringDirection(float Direction);
#pragma endregion

#pragma region Getter
	UFUNCTION(BlueprintCallable)
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable)
	float GetCurrentSteeringAngle();

	UFUNCTION(BlueprintCallable)
	int GetCurrentPoints();
#pragma endregion
	
#pragma region Update
	UPROPERTY(BlueprintAssignable, Category = "Car|Points")
	FIntStatUpdated OnPointsChanged;

	UFUNCTION(BlueprintCallable, Category = "Car|Points")
	void UpdatePoints(int NewPoints);
	UFUNCTION()
	void BroadcastCurrentStats();

#pragma endregion

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:
	
	UCarAnimInstanceBR* GetCarAnimInstance();

#pragma region Collision
	FCollisionShape GetCollisionBoxWithScale(FVector ScaleVector = FVector(1,1,1));
	FCollisionShape GetCollisionBox();
	float CalculateGravityOffset(FVector Location);
	bool CheckForCollisionInMovementDirection(int Direction);
#pragma endregion

#pragma region Car Movement
	void Move();
	void Turn();
	float CalculateLinearSpeedToRotationFactor(float Speed);
#pragma endregion





#pragma region Car Properties
	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MAX_SPEED_FOREWARD = 240;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MAX_SPEED_BACKWARD = -30;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float CarDeceleration = 1;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float BreakingMultiplier = 1.2;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MaxSteeringAngle = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement" )
	float MaxFactor = 0.02 ;
	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MinFactor = 0.001;

	UPROPERTY(EditAnywhere, Category = "Car Properties| Movement")
	float CarGravityConstant = 6;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Details")
	float CarBottomToGroundOffset = 20;


	UPROPERTY(EditAnywhere, Category = "Car Properties|Animation")
	UCarAnimInstanceBR* CarAnimInstance = nullptr;

	

	USceneComponent* CollisionBox = nullptr;


#pragma endregion
	

#pragma region Car State

	int8 MovementDirection = 0;
	int8 SteeringDirection = 0;

	float CurrentSpeed = 0;
	float CurrentSteeringAngle = 0;

	int CurrentPoints = 0;

#pragma endregion
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
  
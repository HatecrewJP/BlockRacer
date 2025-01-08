// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CarBR.generated.h"




UCLASS()
class BLOCKRACER_API ACar : public APawn
{
	GENERATED_BODY()
	
public:

	ACar();
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void MoveCar();

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
#pragma endregion
	


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:


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
	float Deceleration = 1;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float BreakingMultiplier = 1.2;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MaxSteeringAngle = 20.0f;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement" )
	float MaxFactor = 0.02 ;
	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MinFactor = 0.001;

#pragma endregion
	

#pragma region Car State

	int8 MovementDirection = 0;
	int8 SteeringDirection = 0;

	float CurrentSpeed = 0;
	float CurrentSteeringAngle = 0;

#pragma endregion
	
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
  
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Car.generated.h"




UCLASS()
class BLOCKRACER_API ACar : public ACharacter
{
	GENERATED_BODY()
	
public:

	ACar();

	virtual void Tick(float DeltaTime) override;
	void Accelerate(int8 Direction);
	void Break();
	void Steering(int8 Direction);
	
	UFUNCTION(BlueprintCallable)
	float GetCurrentSpeed();

	UFUNCTION(BlueprintCallable)
	float GetCurrentSteeringAngle();

	void SetMovementDirection(float Direction);
	void SetSteeringDirection(float Direction);


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float DeltaTime);

private:

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MAX_SPEED_FOREWARD = 240;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MAX_SPEED_BACKWARD = -30;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float Deceleration = 2;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float BreakingMultiplier = 0.5;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MaxSteeringAngle = 20.0f;

	
	UPROPERTY(EditAnywhere)
	float MaxFactor = 0.02 ;
	UPROPERTY(EditAnywhere)
	float MinFactor = 0.001;
	
	int8 MovementDirection = 0;
	int8 SteeringDirection = 0;

	float CurrentSpeed = 0;
	float CurrentSteeringAngle = 0;

	float CalculateLinearSpeedToRotationFactor(float Speed);

	void Turn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
  
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
	
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move(float DeltaTime);

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CollisionBox = nullptr;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	uint8 MAX_SPEED_FOREWARD = 80;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	int8 MAX_SPEED_BACKWARD = -30;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	uint8 Acceleration = 3;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	uint8 Deceleration = 1;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	uint8 BreakingMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float MaxSteeringAngle = 40;

	UPROPERTY(EditAnywhere, Category = "Car Properties|Movement")
	float SpeedToRotationFactor = 0.005f;
	
	int16 Speed = 0;
	float CurrentSteeringAngle = 0;

	void Turn();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
  
// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/SphereComponent.h"


#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Car.generated.h"

<<<<<<< HEAD
typedef int8 TurnDirection;


=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204
UCLASS()
class BLOCKRACER_API ACar : public ACharacter
{
	GENERATED_BODY()
	
public:

	ACar();

	virtual void Tick(float DeltaTime) override;
	void Accelerate();
	void Break();
<<<<<<< HEAD
	void Turn(TurnDirection Direction);
=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
<<<<<<< HEAD
	void Move(float DeltaTime);
=======
	void Move();
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CollisionBox = nullptr;

	UPROPERTY(EditAnywhere)
<<<<<<< HEAD
	uint8 MAX_SPEED = 60;
=======
	uint8 MAX_SPEED = 240;
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204

	UPROPERTY(EditAnywhere)
	uint8 Acceleration = 4;

	UPROPERTY(EditAnywhere)
	uint8 Deceleration = 1;

	UPROPERTY(EditAnywhere)
	uint8 BreakingMultiplier = 10;

<<<<<<< HEAD
	UPROPERTY(EditAnywhere)
	float TurnAngle = 1;

=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204
	
	int16 Speed = 0;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
  
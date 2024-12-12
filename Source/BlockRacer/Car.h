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
	void Accelerate();
	void Break();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	void Move();

private:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USphereComponent> CollisionBox = nullptr;

	UPROPERTY(EditAnywhere)
	uint8 MAX_SPEED = 240;

	UPROPERTY(EditAnywhere)
	uint8 Acceleration = 4;

	UPROPERTY(EditAnywhere)
	uint8 Deceleration = 1;

	UPROPERTY(EditAnywhere)
	uint8 BreakingMultiplier = 10;

	
	int16 Speed = 0;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	
};
  
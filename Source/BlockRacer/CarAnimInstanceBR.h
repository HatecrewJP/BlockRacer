// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CarAnimInstanceBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API UCarAnimInstanceBR : public UAnimInstance
{
	GENERATED_BODY()
public:
	void SetSpeed(float NewSpeed);
	void SetSteeringAngle(float NewSteeringAngle);

	UFUNCTION(BlueprintCallable)
	float fGetSpeed();
	UFUNCTION(BlueprintCallable)
	float fGetSteeringAngle();
	UFUNCTION(BlueprintCallable)
	float fGetTireRadius();
	UFUNCTION(BlueprintCallable)
	float fGetFrontRotAngle();
	UFUNCTION(BlueprintCallable)
	float fGetRearRotAngle();
	



protected:
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float Speed = 0;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float SteeringAngle = 0;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float TireRadius = 51;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float FrontRotAngle = 0;
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	float RearRotAngle = 0;

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;




};

// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Custom Includes
#include "InputAction.h"
#include "Car.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

//Default Includes
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DrivingPlayerControllerBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API ADrivingPlayerControllerBR : public APlayerController
{
	GENERATED_BODY()

#pragma region InputAction
public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input| Character Movement")
	UInputAction* Accelerate = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input| Character Movement")
	UInputAction* Break = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input| Character Movement")
	UInputAction* TurnLeft = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input| Character Movement")
	UInputAction* TurnRight = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Input| Character Movement")
	UInputMappingContext* InputMappingContext = nullptr;



#pragma endregion

protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

#pragma region Handle
	void HandleAccelerate();
	void HandleBreak();
	void HandleTurnLeft();
	void HandleTurnRight();
#pragma endregion

private:

	UEnhancedInputComponent* EnhancedInputComponent = nullptr;

	//reference to the Players Car
	ACar* 				PlayerCar 		 = nullptr;
	APlayerController* 	PlayerController = nullptr;
	
};

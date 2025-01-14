// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
//Custom Includes
#include "InputAction.h"
#include "CarBR.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MenuHudBR.h"


#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MenuPlayerControllerBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API AMenuPlayerControllerBR : public APlayerController
{
	GENERATED_BODY()
public:	
#pragma region InputAction
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Mapping Context")
	UInputMappingContext* MenuWithCursorInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Mapping Context")
	UInputMappingContext* MenuWithoutCursorInputMappingContext = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuMouseAction = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuClose = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuMoveDown = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuMoveUp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuMoveLeft = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuMoveRight = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|Input Action")
	UInputAction* MenuSelect = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Menu Input|HUD")
	AMenuHudBR* Menu = nullptr;
#pragma endregion

#pragma region HandleFunctions
	void HandleMenuMouseAction(const FInputActionValue& InputActionValue);
	void HandleMenuClose();
	void HandleMenuMoveDown();
	void HandleMenuMoveUp();
	void HandleMenuMoveLeft();
	void HandleMenuMoveRight();
	void HandleMenuSelect();

#pragma endregion


protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

private:
	UInputMappingContext* CurrentMenuInputMappingContext = nullptr;
	UEnhancedInputComponent* EnhancedInputComponent = nullptr;
	bool MouseEnabled = false;

	
};

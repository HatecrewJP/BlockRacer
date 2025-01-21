// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MenuHudBR.generated.h"

/**
 * 
 */
UCLASS()
class BLOCKRACER_API AMenuHudBR : public AHUD
{
	GENERATED_BODY()

#pragma region MenuInterActions
public:
	void SetCursorPosition(FVector2D NewCursorPosition);
	void CloseMenu();
	void MoveDown();
	void MoveUp();
	void MoveLeft();
	void MoveRight();
	void Select();

#pragma endregion
};

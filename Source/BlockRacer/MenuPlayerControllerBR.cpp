// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuPlayerControllerBR.h"

#pragma region HandleFunctions
void AMenuPlayerControllerBR::HandleMenuMouseAction(const FInputActionValue &InputActionValue)
{
    if(!MouseEnabled)
    {

        CurrentMenuInputMappingContext = MenuWithCursorInputMappingContext;
        MouseEnabled = true;
        return;
    }

    checkf(CurrentMenuInputMappingContext == MenuWithoutCursorInputMappingContext && MouseEnabled,TEXT("When MouseEnabled, the active Mapping input must be the Menu with mouse cursor "));
    FVector2D CursorPosition = InputActionValue.Get<FVector2D>();
    if(Menu) Menu -> SetCursorPosition(CursorPosition);

}

void AMenuPlayerControllerBR::HandleMenuClose()
{
    if(Menu) Menu -> CloseMenu();
}

void AMenuPlayerControllerBR::HandleMenuMoveDown()
{
    if(Menu) Menu -> MoveDown(); 
}

void AMenuPlayerControllerBR::HandleMenuMoveUp()
{
    if(Menu) Menu -> MoveUp();
}

void AMenuPlayerControllerBR::HandleMenuMoveLeft()
{
    if(Menu) Menu -> MoveLeft();
}

void AMenuPlayerControllerBR::HandleMenuMoveRight()
{
    if(Menu) Menu -> MoveRight();
}

void AMenuPlayerControllerBR::HandleMenuSelect()
{
    if(Menu) Menu -> Select();
}


void AMenuPlayerControllerBR::OnPossess(APawn *aPawn)
{
    Super::OnPossess(aPawn);
    

    EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    checkf(EnhancedInputComponent,TEXT("Unable to get reference to EnhancedInputComponent"));

    UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(EnhancedInputLocalPlayerSubsystem, TEXT("Unable to get reference to EnhancedLocalPlayerSubsystem"));

    checkf(MenuWithCursorInputMappingContext, TEXT("MenuPlayerController: No InputMappingContext with mouse cursor found."));
    checkf(MenuWithoutCursorInputMappingContext, TEXT("MenuPlayerController: No InputMappingContext without mouse cursor found."));

    CurrentMenuInputMappingContext = MenuWithoutCursorInputMappingContext;

    EnhancedInputLocalPlayerSubsystem -> ClearAllMappings();
    EnhancedInputLocalPlayerSubsystem -> AddMappingContext(CurrentMenuInputMappingContext,0);

    if(MenuMouseAction) EnhancedInputComponent -> BindAction(MenuMouseAction,   ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuMouseAction);
    if(MenuClose)       EnhancedInputComponent -> BindAction(MenuClose,         ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuClose);
    if(MenuMoveDown)    EnhancedInputComponent -> BindAction(MenuMoveDown,      ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuMoveDown);
    if(MenuMoveUp)      EnhancedInputComponent -> BindAction(MenuMoveUp,        ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuMoveUp);
    if(MenuMoveLeft)    EnhancedInputComponent -> BindAction(MenuMoveLeft,      ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuMoveLeft);
    if(MenuMoveRight)   EnhancedInputComponent -> BindAction(MenuMoveRight,     ETriggerEvent::Triggered,this,&AMenuPlayerControllerBR::HandleMenuMoveRight);

    
}

void AMenuPlayerControllerBR::OnUnPossess()
{
    EnhancedInputComponent -> ClearActionBindings();
    UE_LOG(LogTemp,Display,TEXT("Possesed"));
    Super::OnUnPossess();
}

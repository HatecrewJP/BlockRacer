// Fill out your copyright notice in the Description page of Project Settings.


#include "DrivingPlayerControllerBR.h"


#define MoveDirectionForeward 1
#define MoveDirectionBackward -1

void ADrivingPlayerControllerBR::OnPossess(APawn *aPawn)
{
    Super::OnPossess(aPawn);
    PlayerCar = Cast<ACar>(aPawn);
    checkf(PlayerCar, TEXT("ADrivingControllerBR derived classes should only posess ACar derived pawns"));

    EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
    checkf(EnhancedInputComponent,TEXT("Unable to get reference to EnhancedInputComponent"));

    UEnhancedInputLocalPlayerSubsystem* EnhancedLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
    checkf(EnhancedLocalPlayerSubsystem, TEXT("Unable to get reference to EnhancedLocalPlayerSubsystem"));

    checkf(InputMappingContext,TEXT("No InputMappingContext found"));

    EnhancedLocalPlayerSubsystem->ClearAllMappings();
    EnhancedLocalPlayerSubsystem->AddMappingContext(InputMappingContext,0);

    if(Move)     EnhancedInputComponent->BindAction(Move,     ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleMove);
    if(Break)    EnhancedInputComponent->BindAction(Break,    ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleBreak);
    if(Steering) EnhancedInputComponent->BindAction(Steering, ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleSteering);
    


}

void ADrivingPlayerControllerBR::OnUnPossess()
{
    EnhancedInputComponent->ClearActionBindings();
    Super::OnUnPossess();

}

void ADrivingPlayerControllerBR::HandleMove(const FInputActionValue& InputActionValue)
{
    float Direction = InputActionValue.Get<float>();
    if(PlayerCar) PlayerCar->Accelerate(Direction);
}

void ADrivingPlayerControllerBR::HandleBreak()
{
   if(PlayerCar) PlayerCar->Break();
}

void ADrivingPlayerControllerBR::HandleSteering(const FInputActionValue& InputActionValue)
{
    float Direction = InputActionValue.Get<float>();
    if(PlayerCar) PlayerCar->Steering(Direction);

}


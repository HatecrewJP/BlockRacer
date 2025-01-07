// Fill out your copyright notice in the Description page of Project Settings.


#include "DrivingPlayerControllerBR.h"





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

    if(Move)     EnhancedInputComponent->BindAction(Move,     ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleMoveStarted);
    if(Move)     EnhancedInputComponent->BindAction(Move,     ETriggerEvent::Completed,this,&ADrivingPlayerControllerBR::HandleMoveCompleted);

    if(Break)    EnhancedInputComponent->BindAction(Break,    ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleBreak);

    if(Steering) EnhancedInputComponent->BindAction(Steering, ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleSteeringStarted);
    if(Steering) EnhancedInputComponent->BindAction(Steering, ETriggerEvent::Completed,this,&ADrivingPlayerControllerBR::HandleSteeringCompleted);
    


}

void ADrivingPlayerControllerBR::OnUnPossess()
{
    EnhancedInputComponent->ClearActionBindings();
    Super::OnUnPossess();

}

void ADrivingPlayerControllerBR::HandleMoveStarted(const FInputActionValue& InputActionValue)
{
    float Direction = InputActionValue.Get<float>();
    //UE_LOG(LogTemp,Log,TEXT("HandleMove Input: %f"),Direction);
    if(PlayerCar) PlayerCar -> SetMovementDirection(Direction);
}
void ADrivingPlayerControllerBR::HandleMoveCompleted(const FInputActionValue& InputActionValue)
{
    //UE_LOG(LogTemp,Log,TEXT("Move Complete"));
    if(PlayerCar) PlayerCar -> SetMovementDirection(0);

}

void ADrivingPlayerControllerBR::HandleBreak()
{
   if(PlayerCar) PlayerCar->Break();
}

void ADrivingPlayerControllerBR::HandleSteeringStarted(const FInputActionValue& InputActionValue)
{
    float Direction = InputActionValue.Get<float>();
    if(PlayerCar) PlayerCar->SetSteeringDirection(Direction);
}
void ADrivingPlayerControllerBR::HandleSteeringCompleted(const FInputActionValue& InputActionValue)
{
    if(PlayerCar) PlayerCar->SetSteeringDirection(0);
}

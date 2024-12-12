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

    if(Accelerate) EnhancedInputComponent->BindAction(Accelerate,ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleAccelerate);
    if(Break) EnhancedInputComponent->BindAction(Break,ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleBreak);

}

void ADrivingPlayerControllerBR::OnUnPossess()
{
    EnhancedInputComponent->ClearActionBindings();

}

void ADrivingPlayerControllerBR::HandleAccelerate()
{
    if(PlayerCar) PlayerCar->Accelerate();
}

void ADrivingPlayerControllerBR::HandleBreak()
{
   if(PlayerCar) PlayerCar->Break();
   Super::OnUnPossess();
   
}

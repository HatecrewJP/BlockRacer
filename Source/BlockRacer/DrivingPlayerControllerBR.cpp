// Fill out your copyright notice in the Description page of Project Settings.


#include "DrivingPlayerControllerBR.h"

<<<<<<< HEAD
#define TurnDirectionRight 1
#define TurnDirectionLeft -1

=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204
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
<<<<<<< HEAD
    if(TurnLeft) 
    {
        EnhancedInputComponent->BindAction(TurnLeft,ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleTurnLeft);
        UE_LOG(LogTemp,Log,TEXT("Turn Left bound"));
    }
    if(TurnRight)
    {
        EnhancedInputComponent->BindAction(TurnRight,ETriggerEvent::Triggered,this,&ADrivingPlayerControllerBR::HandleTurnRight);
       
    }
=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204

}

void ADrivingPlayerControllerBR::OnUnPossess()
{
    EnhancedInputComponent->ClearActionBindings();
<<<<<<< HEAD
    Super::OnUnPossess();
=======
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204

}

void ADrivingPlayerControllerBR::HandleAccelerate()
{
    if(PlayerCar) PlayerCar->Accelerate();
}

void ADrivingPlayerControllerBR::HandleBreak()
{
   if(PlayerCar) PlayerCar->Break();
<<<<<<< HEAD
}

void ADrivingPlayerControllerBR::HandleTurnLeft()
{
    if(PlayerCar) PlayerCar->Turn(TurnDirectionLeft);

}
void ADrivingPlayerControllerBR::HandleTurnRight()
{
    if(PlayerCar)
    {
        PlayerCar->Turn(TurnDirectionRight);
        
    }
}

=======
   Super::OnUnPossess();
   
}
>>>>>>> 1d42278a63653ced52e317a376d317e4ec96d204

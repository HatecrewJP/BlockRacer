// Fill out your copyright notice in the Description page of Project Settings.



#include "HudBR.h"

#include "PointsDisplayWidgetBR.h"

void AHudBR::BeginPlay()
{
    UWorld* CurrentWorld = GetWorld();
    checkf(CurrentWorld,TEXT("Can't reference World"));

    checkf(BlockCollectorLayoutClass,TEXT("Can't reference PointsDisplayWidget Class"));
  

    BlockCollectorLayout = CreateWidget<UBlockcollectorLayoutBRBase>(CurrentWorld,BlockCollectorLayoutClass);
    BlockCollectorLayout -> AddToViewport();

    if(APlayerController* PlayerController = GetOwningPlayerController())
    {
        PlayerPawn = Cast<ACar>(PlayerController->GetPawn());
    }
    checkf(PlayerPawn,TEXT("Unable to reference Player Pawn"));

    PlayerPawn->OnPointsChanged.AddDynamic(BlockCollectorLayout->PointsDisplay, &UPointsDisplayWidgetBR::OnIntStatUpdated);
    UpdateWidget();
    
}

void AHudBR::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if(PlayerPawn) PlayerPawn->OnPointsChanged.Clear();

    Super::EndPlay(EndPlayReason);
}

void AHudBR::UpdateWidget()
{
    PlayerPawn->BroadcastCurrentStats();
}
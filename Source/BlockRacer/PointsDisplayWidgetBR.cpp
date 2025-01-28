// Fill out your copyright notice in the Description page of Project Settings.


#include "PointsDisplayWidgetBR.h"

void UPointsDisplayWidgetBR::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    UpdateWidget();
}


void UPointsDisplayWidgetBR::OnIntStatUpdated(int32 OldValue, int32 NewValue, int32 MaxValue)
{
    
    CurrentPoints = NewValue;
    UpdateWidget();
}

FText UPointsDisplayWidgetBR::ConvertPointsToText(int32 Points)
{
    FString PointsAsString = FString::FromInt(Points);
    return FText::FromString(PointsAsString);
}

void UPointsDisplayWidgetBR::UpdateWidget()
{ 
    
    if(!ValueText || !PointsText) return;
    FText Points = ConvertPointsToText(this->CurrentPoints);
    //UE_LOG(LogTemp,Display,TEXT("Points: %d"),CurrentPoints);
    ValueText->SetText(Points);

    /*
    uint8 NewRed    = FMath::Clamp(CurrentPoints / 255 * 3, 0, 255);
    uint8 NewGreen  = FMath::Clamp(CurrentPoints / 255 * 3, 0, 255);
    uint8 NewBlue   = FMath::Clamp(CurrentPoints / 255 * 3, 0, 255);
    uint8 NewAlpha  = 0xFF;


    FColor NewColor = FColor(NewRed,NewGreen,NewBlue,NewAlpha);
    
    PointsText -> SetColorAndOpacity(FSlateColor(NewColor));
    */
}
#if WITH_EDITOR
void UPointsDisplayWidgetBR::OnDesignerChanged(const FDesignerChangedEventArgs& EventArgs)
{
    Super::OnDesignerChanged(EventArgs);
    UpdateWidget();
}

void UPointsDisplayWidgetBR::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
    Super::PostEditChangeProperty(PropertyChangedEvent);
    UpdateWidget();
}
#endif
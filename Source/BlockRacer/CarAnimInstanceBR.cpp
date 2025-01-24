// Fill out your copyright notice in the Description page of Project Settings.
#include "Kismet/KismetMathLibrary.h"

#include "CarAnimInstanceBR.h"

void UCarAnimInstanceBR::NativeUpdateAnimation(float DeltaSeconds)
{
    if(TireRadius == 0) TireRadius = KINDA_SMALL_NUMBER;
    float AddRotAngleRad = Speed * -1000 / TireRadius * DeltaSeconds;
    float AddRotAngleDeg = UKismetMathLibrary::RadiansToDegrees(AddRotAngleRad);
    RearRotAngle  += AddRotAngleDeg;
    FrontRotAngle += AddRotAngleDeg;
    RearRotAngle  = UKismetMathLibrary::GenericPercent_FloatFloat(RearRotAngle,  360.f);
    FrontRotAngle = UKismetMathLibrary::GenericPercent_FloatFloat(FrontRotAngle, 360.f);
    
}

void UCarAnimInstanceBR::SetSteeringAngle(float NewSteeringAngle)
{
    this->SteeringAngle = NewSteeringAngle;
}
void UCarAnimInstanceBR::SetSpeed(float NewSpeed)
{
    this->Speed = NewSpeed;
}
float UCarAnimInstanceBR::fGetSpeed()
{
    return this->Speed;
}
float UCarAnimInstanceBR::fGetSteeringAngle()
{
    return this->SteeringAngle;
}
float UCarAnimInstanceBR::fGetTireRadius()
{
    return this-> TireRadius;
}
float UCarAnimInstanceBR::fGetFrontRotAngle()
{
    return this->FrontRotAngle;
}
float UCarAnimInstanceBR::fGetRearRotAngle()
{
    return this->RearRotAngle;
}

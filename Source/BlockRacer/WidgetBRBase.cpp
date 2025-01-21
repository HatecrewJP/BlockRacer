// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBRBase.h"

#if WITH_EDITOR
const FText UWidgetBRBase::GetPaletteCategory()
{
    return NSLOCTEXT("UMG", "CustomPaletteCategory", "BR");
}
#endif
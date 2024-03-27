#include "BlueprintLibraries/CoreExtAnimationMontageBlueprintLibrary.h"

float UCoreExtAnimationMontageBlueprintLibrary::GetCurveFloat( const UAnimMontage * montage, const FName & curve_name, const float position )
{
    if ( montage != nullptr )
    {
        return montage->EvaluateCurveData( curve_name, position );
    }

    return 0.0f;
}

#include "BlueprintLibraries/CoreExtAnimationMontageBlueprintLibrary.h"

float UCoreExtAnimationMontageBlueprintLibrary::GetCurveFloat( const UAnimMontage * montage, const FName & curve_name, const float position )
{
    if ( montage != nullptr )
    {
        FAnimExtractContext anim_extract_context;
        anim_extract_context.CurrentTime = position;
        return montage->EvaluateCurveData( curve_name, anim_extract_context );
    }

    return 0.0f;
}

#pragma once

#include <Animation/AnimMontage.h>
#include <CoreMinimal.h>
#include <UObject/NameTypes.h>

#include "CoreExtAnimationMontageBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtAnimationMontageBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable )
    static float GetCurveFloat( const UAnimMontage * montage, const FName & curve_name, const float position );
};

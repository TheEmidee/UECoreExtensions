#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtMathBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtMathBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure )
    static int GetWrappedIndex( const int index, const int size );
};

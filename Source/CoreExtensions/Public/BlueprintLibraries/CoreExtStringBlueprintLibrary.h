#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtStringBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtStringBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure, Category = "Text" )
    static void SplitTextByLines( TArray< FString > & array, const FString & text );
};

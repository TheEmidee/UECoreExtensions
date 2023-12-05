#pragma once

#include <CoreMinimal.h>
#include <GameplayTagContainer.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtGameplayTagBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtGameplayTagBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    /*
    Returns a tag without a given number of parents.
    For example, RemoveGameplayTagParents( "w.x.y.z", 2 ) will return "y.z"
     */
    UFUNCTION( BlueprintCallable )
    static FString RemoveGameplayTagParents( FGameplayTag tag, int number_parents_to_remove, bool tag_must_exist = true );
};

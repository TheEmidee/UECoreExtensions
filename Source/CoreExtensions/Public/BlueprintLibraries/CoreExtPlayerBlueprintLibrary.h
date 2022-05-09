#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtPlayerBlueprintLibrary.generated.h"

class APlayerState;
class APlayerController;

UCLASS()
class COREEXTENSIONS_API UCoreExtPlayerBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable )
    static APlayerState * GetPlayerStateFromObject( UObject * object );

    UFUNCTION( BlueprintCallable )
    static APlayerController * GetPlayerControllerFromObject( UObject * object );
};

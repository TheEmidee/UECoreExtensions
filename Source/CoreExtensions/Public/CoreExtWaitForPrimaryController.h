#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintAsyncActionBase.h>

#include "CoreExtWaitForPrimaryController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPrimaryControllerReadyDelegate, APlayerController *, primary_controller );

UCLASS()
class COREEXTENSIONS_API UCoreExtWaitForPrimaryController : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable, meta = ( WorldContext = "world_context_object", BlueprintInternalUseOnly = "true" ) )
    static UCoreExtWaitForPrimaryController * WaitForPrimaryController( UObject * world_context_object );

    void OnGameModePostLogin( AGameModeBase * game_mode_base, APlayerController * player_controller ) const;

    void Activate() override;
    void SetReadyToDestroy() override;

protected:
    UPROPERTY( BlueprintAssignable )
    FOnPrimaryControllerReadyDelegate OnPrimaryControllerDelegate;

private:
    void BroadCastPrimaryController( APlayerController * player_controller ) const;

    FDelegateHandle OnPrimaryControllerDelegateHandle;
};

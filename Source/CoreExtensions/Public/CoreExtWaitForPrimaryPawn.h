#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintAsyncActionBase.h>

#include "CoreExtWaitForPrimaryPawn.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam( FOnPrimaryControllerReadyDelegate, const APawn *, primary_pawn );

UCLASS()
class COREEXTENSIONS_API UCoreExtWaitForPrimaryPawn : public UBlueprintAsyncActionBase
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable, meta = ( WorldContext = "world_context_object", BlueprintInternalUseOnly = "true" ) )
    static UCoreExtWaitForPrimaryPawn * WaitForPrimaryPawn( UObject * world_context_object );

    void Activate() override;
    void SetReadyToDestroy() override;

protected:
    UPROPERTY( BlueprintAssignable )
    FOnPrimaryControllerReadyDelegate OnPrimaryPawnDelegate;

private:
    void Step1_ListenToPrimaryControllerExist( AGameModeBase * game_mode_base, APlayerController * player_controller );
    void Step2_TryToGetPawn( APlayerController * player_controller );
    UFUNCTION()
    void Step3_ListenToPrimaryPawnChanged( APawn * old_pawn, APawn * new_pawn );
    void Step4_BroadCastPrimaryPawn( const APawn * player_pawn );

    TWeakObjectPtr< UWorld > WorldPtr;

    FDelegateHandle OnPrimaryControllerDelegateHandle;
};

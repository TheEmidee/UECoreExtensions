#include "CoreExtWaitForPrimaryController.h"

#include "GameFramework/GameModeBase.h"

#include <Engine/GameInstance.h>

UCoreExtWaitForPrimaryController * UCoreExtWaitForPrimaryController::WaitForPrimaryController( UObject * world_context_object )
{
    UCoreExtWaitForPrimaryController * action = nullptr;

    if ( auto * world = GEngine->GetWorldFromContextObject( world_context_object, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        action = NewObject< ThisClass >();
        action->RegisterWithGameInstance( world );
    }
    return action;
}

void UCoreExtWaitForPrimaryController::Activate()
{
    Super::Activate();

    if ( auto * game_instance = GetWorld()->GetGameInstance() )
    {
        if ( auto * player_controller = game_instance->GetPrimaryPlayerController() )
        {
            BroadCastPrimaryController( player_controller );
        }
        else
        {
            OnPrimaryControllerDelegateHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject( this, &ThisClass::OnGameModePostLogin );
        }
    }
    else
    {
        SetReadyToDestroy();
    }
}

void UCoreExtWaitForPrimaryController::SetReadyToDestroy()
{
    Super::SetReadyToDestroy();
    FGameModeEvents::GameModePostLoginEvent.Remove( OnPrimaryControllerDelegateHandle );
}

void UCoreExtWaitForPrimaryController::OnGameModePostLogin( AGameModeBase * game_mode_base, APlayerController * player_controller ) const
{
    auto * game_instance = GetWorld()->GetGameInstance();

    if ( player_controller != game_instance->GetPrimaryPlayerController() )
    {
        return;
    }

    BroadCastPrimaryController( player_controller );
}

void UCoreExtWaitForPrimaryController::BroadCastPrimaryController( APlayerController * player_controller ) const
{
    OnPrimaryControllerDelegate.Broadcast( player_controller );
}
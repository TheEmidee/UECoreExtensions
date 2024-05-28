#include "CoreExtWaitForPrimaryPawn.h"

#include <Engine/GameInstance.h>
#include <GameFramework/GameModeBase.h>

UCoreExtWaitForPrimaryPawn * UCoreExtWaitForPrimaryPawn::WaitForPrimaryPawn( UObject * world_context_object )
{
    if ( auto * world = GEngine->GetWorldFromContextObject( world_context_object, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        auto * action = NewObject< ThisClass >();
        action->WorldPtr = world;
        action->RegisterWithGameInstance( world );

        return action;
    }
    return nullptr;
}

void UCoreExtWaitForPrimaryPawn::Activate()
{
    Super::Activate();

    if ( const auto * game_instance = WorldPtr.Get()->GetGameInstance() )
    {
        if ( auto * player_controller = game_instance->GetPrimaryPlayerController() )
        {
            Step2_TryToGetPawn( player_controller );
        }
        else
        {
            OnPrimaryControllerDelegateHandle = FGameModeEvents::GameModePostLoginEvent.AddUObject( this, &ThisClass::Step1_ListenToPrimaryControllerExist );
        }
    }
    else
    {
        SetReadyToDestroy();
    }
}

void UCoreExtWaitForPrimaryPawn::SetReadyToDestroy()
{
    Super::SetReadyToDestroy();

    FGameModeEvents::GameModePostLoginEvent.Remove( OnPrimaryControllerDelegateHandle );

    if ( PlayerController != nullptr )
    {
        PlayerController->OnPossessedPawnChanged.RemoveDynamic( this, &ThisClass::Step3_ListenToPrimaryPawnChanged );
    }
}

void UCoreExtWaitForPrimaryPawn::Step1_ListenToPrimaryControllerExist( AGameModeBase * game_mode_base, APlayerController * player_controller )
{
    const auto * game_instance = WorldPtr->GetGameInstance();

    if ( player_controller != game_instance->GetPrimaryPlayerController() )
    {
        return;
    }

    Step2_TryToGetPawn( player_controller );
}

void UCoreExtWaitForPrimaryPawn::Step2_TryToGetPawn( APlayerController * player_controller )
{
    if ( auto * pawn = player_controller->GetPawn() )
    {
        Step4_BroadCastPrimaryPawn( pawn );
    }
    else
    {
        PlayerController = player_controller;
        PlayerController->OnPossessedPawnChanged.AddDynamic( this, &ThisClass::Step3_ListenToPrimaryPawnChanged );
    }
}

void UCoreExtWaitForPrimaryPawn::Step3_ListenToPrimaryPawnChanged( APawn * old_pawn, APawn * new_pawn )
{
    Step4_BroadCastPrimaryPawn( new_pawn );
}

void UCoreExtWaitForPrimaryPawn::Step4_BroadCastPrimaryPawn( const APawn * player_pawn )
{
    OnPrimaryPawnDelegate.Broadcast( player_pawn );
    SetReadyToDestroy();
}
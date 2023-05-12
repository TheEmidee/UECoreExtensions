#include "BlueprintLibraries/CoreExtPlayerBlueprintLibrary.h"

#include <GameFramework/Pawn.h>
#include <GameFramework/PlayerController.h>
#include <GameFramework/PlayerState.h>

APlayerState * UCoreExtPlayerBlueprintLibrary::GetPlayerStateFromObject( UObject * object )
{
    if ( const auto * pc = Cast< APlayerController >( object ) )
    {
        return pc->PlayerState;
    }

    if ( auto * ps = Cast< APlayerState >( object ) )
    {
        return ps;
    }

    if ( const auto * pawn = Cast< APawn >( object ) )
    {
        if ( auto * ps = pawn->GetPlayerState() )
        {
            return ps;
        }
    }
    return nullptr;
}

APlayerController * UCoreExtPlayerBlueprintLibrary::GetPlayerControllerFromObject( UObject * object )
{
    if ( auto * pc = Cast< APlayerController >( object ) )
    {
        return pc;
    }

    if ( const auto * ps = Cast< APlayerState >( object ) )
    {
        return Cast< APlayerController >( ps->GetOwner() );
    }

    if ( const auto * pawn = Cast< APawn >( object ) )
    {
        return Cast< APlayerController >( pawn->GetController() );
    }

    return nullptr;
}
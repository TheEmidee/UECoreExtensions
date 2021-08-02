#include "BlueprintLibraries/CoreExtHelperBlueprintLibrary.h"

#include <Engine/Engine.h>
#include <Engine/World.h>
#include <EngineUtils.h>
#include <Kismet/GameplayStatics.h>

void UCoreExtHelperBlueprintLibrary::CreateObject( const TSubclassOf< UObject > class_of, UObject *& object )
{
    object = NewObject< UObject >( GetTransientPackage(), class_of );
}

void UCoreExtHelperBlueprintLibrary::OpenMap( const UObject * world_context, const TSoftObjectPtr< UWorld > & map_soft_object_ptr, const bool open_if_current /*= false*/ )
{
    if ( !open_if_current &&
         UGameplayStatics::GetCurrentLevelName( world_context, true ) == map_soft_object_ptr.GetAssetName() )
    {
        return;
    }

    UGameplayStatics::OpenLevel( world_context, FName( *map_soft_object_ptr.GetAssetName() ), true );
}

bool UCoreExtHelperBlueprintLibrary::BrowseMap( FWorldContext & world_context, const TSoftObjectPtr< UWorld > & map_soft_object_ptr, const bool open_if_current /* = false */ )
{
    const auto map_name = map_soft_object_ptr.GetAssetName();

    if ( !open_if_current &&
         UGameplayStatics::GetCurrentLevelName( world_context.World(), true ) == map_name )
    {
        return false;
    }

    const FURL url( *FString::Printf( TEXT( "%s" ), *map_name ) );

    if ( url.Valid )
    {
        FString error;
        const auto browse_return_value = GEngine->Browse( world_context, url, error );

        if ( browse_return_value != EBrowseReturnVal::Success )
        {
            UE_LOG( LogLoad, Fatal, TEXT( "%s" ), *FString::Printf( TEXT( "Failed to enter %s: %s. Please check the log for errors." ), *map_name, *error ) );
            return false;
        }
    }

    return true;
}

template < class T >
void UCoreExtHelperBlueprintLibrary::GetAllActorsOfClass( const UObject * world_context_object, TSubclassOf< AActor > actor_class, TArray< T * > & out_actors )
{
    out_actors.Reset();

    if ( actor_class )
    {
        if ( auto * world = GEngine->GetWorldFromContextObject( world_context_object, EGetWorldErrorMode::LogAndReturnNull ) )
        {
            for ( TActorIterator< T > it( world, actor_class ); it; ++it )
            {
                auto * actor = *it;
                out_actors.Add( actor );
            }
        }
    }
}

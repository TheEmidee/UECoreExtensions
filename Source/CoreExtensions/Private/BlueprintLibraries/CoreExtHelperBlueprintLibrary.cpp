#include "BlueprintLibraries/CoreExtHelperBlueprintLibrary.h"

#include <Components/PrimitiveComponent.h>
#include <Engine/World.h>
#include <GameFramework/GameModeBase.h>
#include <GameFramework/PlayerController.h>
#include <Kismet/GameplayStatics.h>
#include <UObject/Package.h>
#include <UnrealEngine.h>

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

UObject * UCoreExtHelperBlueprintLibrary::GetClassDefaultObject( const UClass * object_class )
{
    return object_class->GetDefaultObject();
}

void UCoreExtHelperBlueprintLibrary::RestartAllPlayers( const UObject * world_context_object )
{
    if ( auto * world = GEngine->GetWorldFromContextObject( world_context_object, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        if ( auto * gm = world->GetAuthGameMode() )
        {
            for ( TPlayerControllerIterator< APlayerController >::ServerAll iterator( world ); iterator; ++iterator )
            {
                if ( auto * player_controller = *iterator )
                {
                    gm->RestartPlayer( player_controller );
                }
            }
        }
    }
}

AActor * UCoreExtHelperBlueprintLibrary::GetControllerStartSpot( const AController * controller )
{
    if ( controller == nullptr )
    {
        return nullptr;
    }

    return controller->StartSpot.Get();
}

void UCoreExtHelperBlueprintLibrary::ParseOptionsFromString( TMap< FString, FString > & options_map, FString options )
{
    FString pair, pair_key, pair_value;

    // Start from the first ?
    int char_position;
    if ( options.FindChar( '?', char_position ) )
    {
        options.MidInline( char_position );
    }

    // Remove everything after an ' '
    if ( options.FindChar( ' ', char_position ) )
    {
        options.MidInline( 0, char_position );
    }

    // Do the parsing
    while ( UGameplayStatics::GrabOption( options, pair ) )
    {
        UGameplayStatics::GetKeyValue( pair, pair_key, pair_value );

        options_map.Emplace( pair_key, pair_value );
    }
}

FString UCoreExtHelperBlueprintLibrary::GetGameModeOptions( const UObject * world_context_object )
{
    FString result;

    if ( const auto * world = world_context_object->GetWorld() )
    {
        if ( const auto * gm = world->GetAuthGameMode() )
        {
            result = gm->OptionsString;
        }
    }

    return result;
}

bool UCoreExtHelperBlueprintLibrary::ModifyAsset( UObject * object )
{
#if WITH_EDITOR
    if ( object == nullptr )
    {
        return false;
    }

    return object->Modify( true );
#else
    return false;
#endif
}

FVector UCoreExtHelperBlueprintLibrary::GetRuntimeVectorCurveValue( UPARAM( ref ) FRuntimeVectorCurve & curve, float in_time )
{
    return curve.GetValue( in_time );
}

void UCoreExtHelperBlueprintLibrary::SetEditorOnly( AActor * actor, bool editor_only )
{
    actor->bIsEditorOnlyActor = editor_only;
}

void UCoreExtHelperBlueprintLibrary::SetActorComponentOwner( UActorComponent * component, AActor * new_owner_actor )
{
    if ( component != nullptr && new_owner_actor != nullptr )
    {
        const auto new_name = MakeUniqueObjectName( new_owner_actor, component->GetClass(), *component->GetName() );
        component->Rename( *new_name.ToString(), new_owner_actor );
    }
}

bool UCoreExtHelperBlueprintLibrary::FindTeleportSpot( const UObject * world_context_object, const AActor * Actor, FVector & Location, FRotator & Rotation )
{
    if ( auto * world = world_context_object->GetWorld() )
    {
        return world->FindTeleportSpot( Actor, Location, Rotation );
    }

    return false;
}

bool UCoreExtHelperBlueprintLibrary::TryTeleportToTeleportSpot( const UObject * world_context_object, AActor * Actor, FVector & Location, FRotator & Rotation )
{
    if ( auto * world = world_context_object->GetWorld() )
    {
        if ( world->FindTeleportSpot( Actor, Location, Rotation ) )
        {
            Actor->SetActorLocationAndRotation( Location, Rotation, false, nullptr, ETeleportType::TeleportPhysics );
            return true;
        }
    }

    return false;
}

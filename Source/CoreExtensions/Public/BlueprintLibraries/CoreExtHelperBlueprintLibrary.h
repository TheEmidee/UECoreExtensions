#pragma once

#include <CoreMinimal.h>
#include <Curves/CurveVector.h>
#include <Engine/Engine.h>
#include <EngineUtils.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <UObject/SoftObjectPtr.h>

#include "CoreExtHelperBlueprintLibrary.generated.h"
struct FWorldContext;
class UWorld;
class UObject;

UCLASS()
class COREEXTENSIONS_API UCoreExtHelperBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure, Category = "Helpers", Meta = ( DisplayName = "Create Object", DeterminesOutputType = "Class", DynamicOutputParam = "Object" ) )
    static void CreateObject( TSubclassOf< UObject > class_of, UObject *& object );

    UFUNCTION( BlueprintCallable, Category = "Maps" )
    static void OpenMap( const UObject * world_context, const TSoftObjectPtr< UWorld > & map_soft_object_ptr, bool open_if_current = false );

    static bool BrowseMap( FWorldContext & world_context, const TSoftObjectPtr< UWorld > & map_soft_object_ptr, bool open_if_current = false );

    template < typename _ACTOR_CLASS_ >
    static _ACTOR_CLASS_ * GetActorOfClass( const UObject * world_context );

    template < typename _ACTOR_CLASS_ >
    static void GetAllActorsOfClass( const UObject * world_context, TArray< _ACTOR_CLASS_ * > & out_actors );

    UFUNCTION( BlueprintPure, Category = "Utilities", meta = ( DeterminesOutputType = "object_class" ) )
    static UObject * GetClassDefaultObject( const UClass * object_class );

    UFUNCTION( BlueprintCallable, Category = "GameMode", meta = ( WorldContext = "world_context_object" ) )
    static void RestartAllPlayers( const UObject * world_context_object );

    UFUNCTION( BlueprintPure, Category = "GameMode" )
    static AActor * GetControllerStartSpot( const AController * controller );

    UFUNCTION( BlueprintPure )
    static void ParseOptionsFromString( TMap< FString, FString > & options_map, FString options );

    UFUNCTION( BlueprintPure, meta = ( WorldContext = "world_context_object" ) )
    static FString GetGameModeOptions( const UObject * world_context_object );

    UFUNCTION( BlueprintCallable )
    static bool ModifyAsset( UObject * object );

    UFUNCTION( BlueprintPure )
    static FVector GetRuntimeVectorCurveValue( UPARAM( ref ) FRuntimeVectorCurve & curve, float in_time );

    UFUNCTION( BlueprintCallable )
    static void SetEditorOnly( AActor * actor, bool editor_only = true );

    UFUNCTION( BlueprintCallable, meta = ( ToolTip = "Change primitive component owner without changing attachment tree" ) )
    static void SetActorComponentOwner( UActorComponent * component, AActor * new_owner_actor );

    UFUNCTION( BlueprintCallable, meta = ( WorldContext = "world_context_object" ) )
    static bool FindTeleportSpot( const UObject * world_context_object, const AActor * Actor, UPARAM( ref ) FVector & Location, UPARAM( ref ) FRotator & Rotation );

    UFUNCTION( BlueprintCallable, meta = ( WorldContext = "world_context_object" ) )
    static bool TryTeleportToTeleportSpot( const UObject * world_context_object, AActor * Actor, UPARAM( ref ) FVector & Location, UPARAM( ref ) FRotator & Rotation );
};

template < typename _ACTOR_CLASS_ >
_ACTOR_CLASS_ * UCoreExtHelperBlueprintLibrary::GetActorOfClass( const UObject * world_context )
{
    QUICK_SCOPE_CYCLE_COUNTER( UCoreExtHelperBlueprintLibrary_GetActorOfClass );

    if ( auto * world = GEngine->GetWorldFromContextObject( world_context, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        for ( TActorIterator< _ACTOR_CLASS_ > actor_iterator( world, _ACTOR_CLASS_::StaticClass() ); actor_iterator; ++actor_iterator )
        {
            auto * actor = *actor_iterator;
            return actor;
        }
    }

    return nullptr;
}

template < typename _ACTOR_CLASS_ >
void UCoreExtHelperBlueprintLibrary::GetAllActorsOfClass( const UObject * world_context, TArray< _ACTOR_CLASS_ * > & out_actors )
{
    QUICK_SCOPE_CYCLE_COUNTER( UCoreExtHelperBlueprintLibrary_GetAllActorsOfClass );
    out_actors.Reset();

    if ( auto * world = GEngine->GetWorldFromContextObject( world_context, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        for ( TActorIterator< _ACTOR_CLASS_ > actor_iterator( world, _ACTOR_CLASS_::StaticClass() ); actor_iterator; ++actor_iterator )
        {
            auto * actor = *actor_iterator;
            out_actors.Add( actor );
        }
    }
}

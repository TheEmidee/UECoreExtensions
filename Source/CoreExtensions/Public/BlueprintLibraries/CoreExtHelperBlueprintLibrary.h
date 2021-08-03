#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>
#include <EngineUtils.h>
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

    template < typename _ACTOR_CLASS_ >
    static _ACTOR_CLASS_ * GetActorOfClass( const UObject * world_context );

    static bool BrowseMap( FWorldContext & world_context, const TSoftObjectPtr< UWorld > & map_soft_object_ptr, bool open_if_current = false );
};

template < typename _ACTOR_CLASS_ >
_ACTOR_CLASS_ * UCoreExtHelperBlueprintLibrary::GetActorOfClass( const UObject * world_context )
{
    QUICK_SCOPE_CYCLE_COUNTER( UCoreExtHelperBlueprintLibrary_GetActorOfClass );

    if ( UWorld * World = GEngine->GetWorldFromContextObject( world_context, EGetWorldErrorMode::LogAndReturnNull ) )
    {
        for ( TActorIterator< _ACTOR_CLASS_ > actor_iterator( World, _ACTOR_CLASS_::StaticClass() ); actor_iterator; ++actor_iterator )
        {
            _ACTOR_CLASS_ * actor = *actor_iterator;
            return actor;
        }
    }

    return nullptr;
}

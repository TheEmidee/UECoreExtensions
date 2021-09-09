#include "BlueprintLibraries/CoreExtHelperBlueprintLibrary.h"

#include "Kismet/KismetMathLibrary.h"

#include <Engine/World.h>
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

ECoreExtHitLocation UCoreExtHelperBlueprintLibrary::GetHitLocationOnActor( const FVector impact_point, AActor * actor )
{
    if ( actor == nullptr )
    {
        return ECoreExtHitLocation::None;
    }

    const auto actor_location = actor->GetActorLocation();
    const auto actor_forward = actor->GetActorForwardVector();

    auto actor_to_impact = impact_point - actor_location;
    actor_to_impact.Normalize();

    auto impact_direction = actor_to_impact - actor_forward;
    impact_direction = UKismetMathLibrary::ProjectVectorOnToPlane( impact_direction, actor_forward );

    impact_direction = UKismetMathLibrary::InverseTransformDirection( actor->GetActorTransform(), impact_direction );

    if ( FMath::Abs( impact_direction.Y ) > FMath::Abs( impact_direction.Z ) )
    {
        return impact_direction.Y > 0.0f ? ECoreExtHitLocation::Right : ECoreExtHitLocation::Left;
    }

    return impact_direction.Z > 0.0f ? ECoreExtHitLocation::Top : ECoreExtHitLocation::Bottom;
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

#pragma once

#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtLevelStreamingBlueprintLibrary.generated.h"

class ULevelStreamingDynamic;

USTRUCT( BlueprintType )
struct COREEXTENSIONS_API FCoreExtLoadLevelStreamingParameters
{
    GENERATED_BODY()

    FCoreExtLoadLevelStreamingParameters() :
        Location( FVector::ZeroVector ),
        Rotation( FRotator::ZeroRotator ),
        ShouldBeLoaded( true ),
        IsStatic( true ),
        IsLocked( true ),
        ShouldBeVisible( true ),
        ShouldBlockOnLoad( false ),
        ShouldBlockOnUnload( false ),
        IsInitiallyLoaded( true ),
        IsInitiallyVisible( true )
    {
    }

    UPROPERTY( BlueprintReadWrite )
    FVector Location;

    UPROPERTY( BlueprintReadWrite )
    FRotator Rotation;

    UPROPERTY( BlueprintReadWrite )
    uint8 ShouldBeLoaded : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 IsStatic : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 IsLocked : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 ShouldBeVisible : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 ShouldBlockOnLoad : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 ShouldBlockOnUnload : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 IsInitiallyLoaded : 1;

    UPROPERTY( BlueprintReadWrite )
    uint8 IsInitiallyVisible : 1;
};

UCLASS()
class COREEXTENSIONS_API UCoreExtLevelStreamingBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION()
    static ULevelStreamingDynamic * LoadLevelInstance( bool & success, const UObject * world_context, const FString & level_name, const FCoreExtLoadLevelStreamingParameters & parameters );

    UFUNCTION()
    static ULevelStreamingDynamic * LoadLevelInstanceBySoftObjectPtr( bool & success, const UObject * world_context, const TSoftObjectPtr< UWorld > level, const FCoreExtLoadLevelStreamingParameters & parameters );

    UFUNCTION()
    static void UnloadLevelInstance( ULevelStreaming * streaming_level_to_unload, bool should_block_on_unload );

private:
    static ULevelStreamingDynamic * LoadLevelInstance_Internal( bool & success, UWorld * world, const FString & long_package_name, const FCoreExtLoadLevelStreamingParameters & parameters );

    static int UniqueLevelInstanceId;
};

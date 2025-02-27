#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtTextureStreamingBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtTextureStreamingBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

    /**
     * Let the content streaming system know that there is a viewpoint other than a possessed camera that should be taken
     * into account when deciding what to stream in. This can be useful when you're using a scene capture component,
     * which if it's capturing a scene that isn't close to a player, can result in blurry textures.
     * cf : https://www.stevestreeting.com/2024/07/24/fixing-blurry-textures-in-ue-capture-components/
     */
    UFUNCTION( BlueprintCallable, Category = "TextureStreaming" )
    static void AddViewOriginToStreaming( const FVector & view_origin, float screen_width, float fov, float boost_factor = 1.0f, bool override_location = false, float duration = 0.0f, AActor * actor_to_boost = nullptr );
};

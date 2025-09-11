#include "BlueprintLibraries/CoreExtTextureStreamingBlueprintLibrary.h"

#include "ContentStreaming.h"

void UCoreExtTextureStreamingBlueprintLibrary::AddViewOriginToStreaming( const FVector & view_origin, float screen_width, float fov, float boost_factor, bool override_location, float duration, AActor * actor_to_boost )
{
    IStreamingManager::Get().AddViewInformation( view_origin, screen_width, screen_width / FMath::Tan( FMath::DegreesToRadians( fov * 0.5f ) ), boost_factor, override_location, duration, actor_to_boost );
}
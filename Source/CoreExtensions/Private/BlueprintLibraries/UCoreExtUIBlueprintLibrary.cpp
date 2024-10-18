#include "BlueprintLibraries/UCoreExtUIBlueprintLibrary.h"

#include <Components/ListView.h>
#include <Engine/AssetManager.h>
#include <Engine/Texture2D.h>
#include <Kismet/GameplayStatics.h>

UUserWidget * UUCoreExtUIBlueprintLibrary::GetWidgetFromListViewItem( UListView * list_view, UObject * item )
{
    return list_view->GetEntryWidgetFromItem( item );
}

UWidget * UUCoreExtUIBlueprintLibrary::GetFocusedWidget( const UObject * world_context_object, const TArray< UWidget * > & widgets )
{
    auto * player_controller = UGameplayStatics::GetPlayerController( world_context_object->GetWorld(), 0 );
    for ( const auto & widget : widgets )
    {
        if ( widget->HasUserFocus( player_controller ) )
        {
            return widget;
        }
    }

    return nullptr;
}

UTexture2D * UUCoreExtUIBlueprintLibrary::ConvertSoftReferenceToTexture( TSoftObjectPtr< UTexture2D > soft_texture )
{
    UAssetManager::GetStreamableManager().RequestSyncLoad( soft_texture.ToSoftObjectPath() );

    return Cast< UTexture2D >( soft_texture.Get() );
}

UTexture2D * UUCoreExtUIBlueprintLibrary::SelectTextureFromSoftReferences( TSoftObjectPtr< UTexture2D > pick_true_texture, TSoftObjectPtr< UTexture2D > pick_false_texture, bool condition )
{
    return ConvertSoftReferenceToTexture( condition ? pick_true_texture : pick_false_texture );
}

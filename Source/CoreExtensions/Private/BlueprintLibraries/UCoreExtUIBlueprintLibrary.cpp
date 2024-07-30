#include "BlueprintLibraries/UCoreExtUIBlueprintLibrary.h"

#include <Components/ListView.h>
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

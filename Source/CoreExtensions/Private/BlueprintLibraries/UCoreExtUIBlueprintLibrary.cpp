#include "BlueprintLibraries/UCoreExtUIBlueprintLibrary.h"

#include <Components/ListView.h>

UUserWidget * UUCoreExtUIBlueprintLibrary::GetWidgetFromListViewItem( UListView * list_view, UObject * item )
{
    return list_view->GetEntryWidgetFromItem( item );
}
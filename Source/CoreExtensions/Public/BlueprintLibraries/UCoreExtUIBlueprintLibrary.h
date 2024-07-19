﻿#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "UCoreExtUIBlueprintLibrary.generated.h"

class UListView;

UCLASS()
class COREEXTENSIONS_API UUCoreExtUIBlueprintLibrary : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintCallable )
    static UUserWidget * GetWidgetFromListViewItem( UListView * list_view, UObject * item );
};

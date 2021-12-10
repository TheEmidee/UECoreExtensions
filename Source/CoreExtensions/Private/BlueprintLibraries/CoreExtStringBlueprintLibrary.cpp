#include "BlueprintLibraries/CoreExtStringBlueprintLibrary.h"

void UCoreExtStringBlueprintLibrary::SplitTextByLines( TArray< FString > & array, const FString & text )
{
    text.ParseIntoArrayLines( array );
}
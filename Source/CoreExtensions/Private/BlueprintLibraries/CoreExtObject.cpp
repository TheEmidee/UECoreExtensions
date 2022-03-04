#include "BlueprintLibraries/CoreExtObject.h"

UWorld * UCoreExtObject::GetWorld() const
{
    if ( IsTemplate() )
    {
        return nullptr;
    }

    if ( const auto * outer = GetOuter() )
    {
        return outer->GetWorld();
    }

    return nullptr;
}

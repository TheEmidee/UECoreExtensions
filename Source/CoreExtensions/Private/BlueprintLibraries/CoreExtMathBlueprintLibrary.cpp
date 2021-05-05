#include "BlueprintLibraries/CoreExtMathBlueprintLibrary.h"

int UCoreExtMathBlueprintLibrary::GetWrappedIndex( const int index, const int size )
{
    return ( ( index % size ) + size ) % size;
}

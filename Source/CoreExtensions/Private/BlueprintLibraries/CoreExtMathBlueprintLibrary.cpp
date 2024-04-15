#include "BlueprintLibraries/CoreExtMathBlueprintLibrary.h"

int UCoreExtMathBlueprintLibrary::GetWrappedIndex( const int index, const int size )
{
    return ( ( index % size ) + size ) % size;
}

bool UCoreExtMathBlueprintLibrary::SegmentIntersection2D( FVector & out_intersection_point, const FVector & segment_start_a, const FVector & segment_end_a, const FVector & segment_start_b, const FVector & segment_end_b )
{
    return FMath::SegmentIntersection2D( segment_start_a, segment_end_a, segment_start_b, segment_end_b, out_intersection_point );
}

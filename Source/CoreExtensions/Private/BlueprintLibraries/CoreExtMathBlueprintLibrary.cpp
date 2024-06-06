#include "BlueprintLibraries/CoreExtMathBlueprintLibrary.h"

TArray< FVector2f > UCoreExtMathBlueprintLibrary::GetPointsOnRectangleEdge( const int height, const int width, const int point_spacing )
{
    TArray< FVector2f > result;

    float half_width = width / 2.0f;
    float half_height = height / 2.0f;
    int point_count = ceil(( height + width ) * 2.0f / point_spacing);

    result.Reserve( point_count );

    for ( int x = -half_width; x <= half_width; x += point_spacing )
    {
        result.Add( FVector2f( x, half_height ) );
        result.Add( FVector2f( x, -half_height ) );
    }

    for ( int y = -half_height + 1; y <= half_height - 1; y += point_spacing )
    {
        result.Add( FVector2f( half_width, y ) );
        result.Add( FVector2f( -half_width, y ) );
    }

    return result;
}

int UCoreExtMathBlueprintLibrary::GetWrappedIndex( const int index, const int size )
{
    return ( ( index % size ) + size ) % size;
}

bool UCoreExtMathBlueprintLibrary::SegmentIntersection2D( FVector & out_intersection_point, const FVector & segment_start_a, const FVector & segment_end_a, const FVector & segment_start_b, const FVector & segment_end_b )
{
    return FMath::SegmentIntersection2D( segment_start_a, segment_end_a, segment_start_b, segment_end_b, out_intersection_point );
}

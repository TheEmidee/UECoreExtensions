#include "BlueprintLibraries/CoreExtMathBlueprintLibrary.h"

void UCoreExtMathBlueprintLibrary::GetPointsOnRectangleEdges( TArray< FVector2D > & out_point_table, const float height, const float width, const float point_spacing )
{
    float half_width = width / 2.0f;
    float half_height = height / 2.0f;
    int point_count = ceil( ( height + width ) * 2.0f / point_spacing );

    out_point_table.Reserve( point_count );

    for ( int x = -half_width; x <= half_width; x += point_spacing )
    {
        out_point_table.Add( FVector2D( x, half_height ) );
        out_point_table.Add( FVector2D( x, -half_height ) );
    }

    for ( int y = -half_height + 1; y <= half_height - 1; y += point_spacing )
    {
        out_point_table.Add( FVector2D( half_width, y ) );
        out_point_table.Add( FVector2D( -half_width, y ) );
    }
}

int UCoreExtMathBlueprintLibrary::GetWrappedIndex( const int index, const int size )
{
    return ( ( index % size ) + size ) % size;
}

bool UCoreExtMathBlueprintLibrary::SegmentIntersection2D( FVector & out_intersection_point, const FVector & segment_start_a, const FVector & segment_end_a, const FVector & segment_start_b, const FVector & segment_end_b )
{
    return FMath::SegmentIntersection2D( segment_start_a, segment_end_a, segment_start_b, segment_end_b, out_intersection_point );
}

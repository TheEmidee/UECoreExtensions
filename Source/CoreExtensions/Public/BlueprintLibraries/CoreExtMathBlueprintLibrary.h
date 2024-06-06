#pragma once

#include <CoreMinimal.h>
#include <Kismet/BlueprintFunctionLibrary.h>

#include "CoreExtMathBlueprintLibrary.generated.h"

UCLASS()
class COREEXTENSIONS_API UCoreExtMathBlueprintLibrary final : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

public:
    UFUNCTION( BlueprintPure )
    static TArray< FVector2f > GetPointsOnRectangleEdge( const int height, const int width, const int point_spacing );

    UFUNCTION( BlueprintPure )
    static int GetWrappedIndex( const int index, const int size );

    UFUNCTION( BlueprintPure )
    static bool SegmentIntersection2D( FVector & out_intersection_point, const FVector & segment_start_a, const FVector & segment_end_a, const FVector & segment_start_b, const FVector & segment_end_b );
};

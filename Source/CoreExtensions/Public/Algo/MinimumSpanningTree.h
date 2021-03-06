#pragma once

#include "Math/Edge2D.h"

#include <CoreMinimal.h>

struct COREEXTENSIONS_API FMSTWeightedEdge2D
{
    FMSTWeightedEdge2D() = default;
    FMSTWeightedEdge2D( const FEdge2D & edge, const int weight );

    FEdge2D Edge;
    int Weight;
};

class COREEXTENSIONS_API FMinimumSpanningTree
{
public:
    void Generate( const TArray< FVector2D > & vertices, const TArray< FMSTWeightedEdge2D > & weighted_edges );

    TArray< FEdge2D > Result;
};
